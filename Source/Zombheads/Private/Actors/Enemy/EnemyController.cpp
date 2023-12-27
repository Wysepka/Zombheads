// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Actors/Enemy/EnemyController.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	CurrentEnemyState = IDLE;
	
	APawn* EnemyPawn = GetPawn();
	if(EnemyPawn != nullptr)
	{
		Possess(EnemyPawn);
	}
	Target = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPawn::StaticClass());
	if(Target == nullptr)
	{
		UE_LOG(LogTemp , Log , TEXT("Could not find Target of type %s") , *(APlayerPawn::StaticClass()->GetName()))
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not find target of type: %s") ,*(APlayerPawn::StaticClass()->GetName()) ));
		return;
	}

	TargetPawn = Cast<APlayerPawn>(Target);
	
	if(TargetPawn == nullptr)
	{
		UE_LOG(LogTemp , Log , TEXT("Could not cast PlayerPawn: %s") , *(APlayerPawn::StaticClass()->GetName()))
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not cast PlayerPawn: %s") ,*(APlayerPawn::StaticClass()->GetName()) ));
		return;
	}
	
	TargetPivot = TargetPawn->GetPlayerPivot();

	if(TargetPivot == nullptr)
	{
		TargetPawn->GetPlayerPivotInitializedDelegate()->AddUObject(this, &AEnemyController::AssignTargetPivotCallback);
		//UE_LOG(LogTemp , Log , TEXT("Could not find PlayerPivot on Obj: %s") , *(APlayerPawn::StaticClass()->GetName()))
		//GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not find PlayerPivot on Obj: %s") ,*(APlayerPawn::StaticClass()->GetName()) ));
	}
}

void AEnemyController::AssignTargetPivotCallback(USceneComponent* TargetPivotCallback)
{
	this->TargetPivot = TargetPivotCallback;
}


void AEnemyController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FTransform TargetTranform = Target->GetTransform();
	MoveToTarget(TargetTranform);
	RotateToTarget(TargetTranform ,DeltaSeconds);
}

void AEnemyController::MoveToTarget(const FTransform& TargetTransform)
{
	if(TargetPivot == nullptr)
	{
		return;
	}
	float DistToTarget = FVector::Distance(GetNavAgentLocation(),TargetTransform.GetLocation());
	if(DistToTarget > StoppingDistance)
	{
		if(CurrentEnemyState == IDLE || CurrentEnemyState == ATTACKING)
		{
			CurrentEnemyState = TOWARD_TARGET;
			if(OnStateChanged.IsBound())
			{
				OnStateChanged.Broadcast(FOnStateChangedData(CurrentEnemyState));
			}
		}

		//Vell we need to update MoveToLocation each frame cuz Pivot position might be changing
		FAIMoveRequest MoveRequest;
		MoveToLocation(TargetPivot->GetComponentLocation() , StoppingDistance);
	} else
	{
		if(CurrentEnemyState == TOWARD_TARGET || CurrentEnemyState == IDLE)
		{
			CurrentEnemyState = ATTACKING;
			if(OnStateChanged.IsBound())
			{
				OnStateChanged.Broadcast(FOnStateChangedData(CurrentEnemyState , TargetPawn));
			}
		}
	}
}

void AEnemyController::RotateToTarget(const FTransform& TargetTransform , const float DeltaTime) const
{
	APawn* ControlledPawn = GetPawn();
	if(ControlledPawn != nullptr)
	{
		//UCharacterMovementComponent* CharacterMovementComponent = ControlledPawn->FindComponentByClass<UCharacterMovementComponent>();
		UFloatingPawnMovement* FloatingPawnMovement = ControlledPawn->FindComponentByClass<UFloatingPawnMovement>();

		if(FloatingPawnMovement)
		{
			FVector Velocity = FloatingPawnMovement->Velocity;

			if (!Velocity.IsNearlyZero())
			{
				// Calculate the rotation that points in the direction of movement
				FRotator DesiredRotation = Velocity.Rotation();
				DesiredRotation.Pitch = 0.0f; // Optional: Zero out pitch rotation if you want to limit rotation to horizontal plane

				// Interpolate to the desired rotation smoothly
				FRotator NewRotation = FMath::RInterpTo(ControlledPawn->GetActorRotation(), DesiredRotation,DeltaTime , 2.f);

				// Set the new rotation for the enemy character
				ControlledPawn->SetActorRotation(NewRotation);
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f , FColor::Red , FString::Printf(TEXT("Could not find CharacterMovementComponent in enemy: %s") , *GetName()));
		}
	}
}


void AEnemyController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	
}

AEnemyController::AEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;
}


