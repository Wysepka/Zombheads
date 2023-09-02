// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Actors/Enemy/EnemyController.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
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

	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(Target);
	if(PlayerPawn == nullptr)
	{
		UE_LOG(LogTemp , Log , TEXT("Could not cast PlayerPawn: %s") , *(APlayerPawn::StaticClass()->GetName()))
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not cast PlayerPawn: %s") ,*(APlayerPawn::StaticClass()->GetName()) ));
		return;
	}
	
	TargetPivot = PlayerPawn->GetPlayerPivot();

	if(TargetPivot == nullptr)
	{
		PlayerPawn->GetPlayerPivotInitializedDelegate()->AddUObject(this, &AEnemyController::AssignTargetPivotCallback);
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
	//FTransform TargetTranform = Target->GetTransform();
	float DistToTarget = FVector::Distance(GetNavAgentLocation(),TargetTransform.GetLocation());
	if(DistToTarget > StoppingDistance)
	{
		//if(!IsFollowingAPath())
		//{
			//MoveToActor(Target , StoppingDistance);
			FAIMoveRequest MoveRequest;
			//MoveToActor(Target , StoppingDistance);
			MoveToLocation(TargetPivot->GetComponentLocation() , StoppingDistance);
			//MoveToLocation(GetNavAgentLocation()  + FVector::ForwardVector * 1000.f);
		//}
	} else
	{
		if(OnReachedTarget.IsBound())
		{
			OnReachedTarget.Broadcast();
		}
	}
}

void AEnemyController::RotateToTarget(const FTransform& TargetTransform , const float DeltaTime) const
{
	/*
	FVector DirToTarget = TargetTransform.GetLocation() - GetNavAgentLocation();
	if(DirToTarget.Normalize())
	{
		//USceneComponent* RootComponent = GetRootComponent();
		RootComponent->SetWorldRotation(DirToTarget.Rotation());
		
	}
	else
	{
		UE_LOG(LogTemp , Warning , TEXT("Could not Normalize dir to Target for Agent: %s") , *GetName());
	}
	*/

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


