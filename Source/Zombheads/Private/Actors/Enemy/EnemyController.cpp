// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Actors/Enemy/EnemyController.h"

#include <string>

#include "GameFramework/FloatingPawnMovement.h"
#include "Navigation/CrowdManager.h"

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentEnemyState = IDLE;
	AttachToPawn(GetPawn());
	APawn* EnemyPawn = GetPawn();
	if(EnemyPawn != nullptr)
	{
		//Possess(EnemyPawn);
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

	//auto PathFollowComp = GetPathFollowingComponent();
	//AddComponentByClass(UCrowdFollowingComponent::StaticClass(), false, GetTransformComponent()->GetComponentTransform() , true);
	//SetupCrowdFollowCompNormal();
	SetupCrowdFollowCompOverriden();
	return;
}

void AEnemyController::SetupCrowdFollowCompOverriden()
{
	auto PathFollowComp = FindComponentByClass<UEnemyCrowdFollowingComponent>();
	if(PathFollowComp != nullptr)
	{
		SetPathFollowingComponent(PathFollowComp);
		CrowdFollowingComponentOverriden = Cast<UEnemyCrowdFollowingComponent>(PathFollowComp);
		if(PathFollowComp != nullptr)
		{
			CrowdFollowingComponentOverriden.Get()->Initialize();
			CrowdFollowingComponentOverriden.Get()->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
			CrowdFollowingComponentOverriden.Get()->SetCrowdSeparationWeight(400.f);
			CrowdFollowingComponentOverriden.Get()->SetCrowdSeparation(true );
			CrowdFollowingComponentOverriden.Get()->SetCrowdSimulationState(ECrowdSimulationState::Enabled);
			CrowdFollowingComponentOverriden.Get()->SetCrowdCollisionQueryRange(1000.f);
			CrowdFollowingComponentOverriden.Get()->SetAvoidanceGroup(1 , true);
			CrowdFollowingComponentOverriden.Get()->SetCrowdAnticipateTurns(true);
			CrowdFollowingComponentOverriden.Get()->UpdateCrowdAgentParams();
			//CrowdFollowingComponent->ApplyCrowdAgentPosition(GetTransformComponent()->GetComponentLocation());
			//CrowdFollowComp.
			auto CrowdManager = UCrowdManager::GetCurrent(GetWorld());
			//CrowdManager->RegisterAgent(CrowdFollowingComponent.Get());
			
			UE_LOG(LogTemp , Log , TEXT("Found CrowdFollowComp: %s") , *(CrowdFollowingComponent->StaticClass()->GetName()))
			GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Found CrowdFollowComp: %s") ,*CrowdFollowingComponentOverriden->StaticClass()->GetName()));
			GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("IsCrowdSimulationActive: %hhd") ,CrowdFollowingComponentOverriden->IsCrowdSimulationActive()));
			GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("IsCrowdSimulationEnabled: %hhd") ,CrowdFollowingComponentOverriden->IsCrowdSimulationEnabled()));
			GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Current Active Agents: %i") ,CrowdManager->GetNumNearbyAgents(CrowdFollowingComponentOverriden.Get())));
			return;
		}
		else
		{
			UE_LOG(LogTemp , Log , TEXT("Could not cast CrowdFollowComp, type is : %s") , *(PathFollowComp->GetName()))
			GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not cast CrowdFollowComp, type is : %s") ,*PathFollowComp->GetName()));
			return;
		}
	}
	else
	{
		UE_LOG(LogTemp , Log , TEXT("Could not get PathFollowComp on: %s") , *(this->GetName()))
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not get PathFollowComp on %s") ,*(this->GetName()) ));
		return;
	}
}

void AEnemyController::SetupCrowdFollowCompNormal()
{
	auto PathFollowComp = FindComponentByClass<UCrowdFollowingComponent>();
	if(PathFollowComp != nullptr)
	{
		SetPathFollowingComponent(PathFollowComp);
		CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(PathFollowComp);
		if(CrowdFollowingComponent != nullptr)
		{
			CrowdFollowingComponent.Get()->Initialize();
			CrowdFollowingComponent.Get()->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
			CrowdFollowingComponent.Get()->SetCrowdSeparationWeight(400.f);
			CrowdFollowingComponent.Get()->SetCrowdSeparation(true );
			CrowdFollowingComponent.Get()->SetCrowdSimulationState(ECrowdSimulationState::Enabled);
			CrowdFollowingComponent.Get()->SetCrowdCollisionQueryRange(1000.f);
			CrowdFollowingComponent.Get()->SetAvoidanceGroup(1 , true);
			CrowdFollowingComponent.Get()->UpdateCrowdAgentParams();
			//CrowdFollowingComponent->ApplyCrowdAgentPosition(GetTransformComponent()->GetComponentLocation());
			//CrowdFollowComp.
			auto CrowdManager = UCrowdManager::GetCurrent(GetWorld());
			//CrowdManager->RegisterAgent(CrowdFollowingComponent.Get());
			
			UE_LOG(LogTemp , Log , TEXT("Found CrowdFollowComp: %s") , *(CrowdFollowingComponent->StaticClass()->GetName()))
			GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Found CrowdFollowComp: %s") ,*CrowdFollowingComponent->StaticClass()->GetName()));
			GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("IsCrowdSimulationActive: %hhd") ,CrowdFollowingComponent->IsCrowdSimulationActive()));
			GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("IsCrowdSimulationEnabled: %hhd") ,CrowdFollowingComponent->IsCrowdSimulationEnabled()));
			GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Current Active Agents: %i") ,CrowdManager->GetNumNearbyAgents(CrowdFollowingComponent.Get())));
			return;
		}
		else
		{
			UE_LOG(LogTemp , Log , TEXT("Could not cast CrowdFollowComp, type is : %s") , *(PathFollowComp->GetName()))
			GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not cast CrowdFollowComp, type is : %s") ,*PathFollowComp->GetName()));
			return;
		}
	}
	else
	{
		UE_LOG(LogTemp , Log , TEXT("Could not get PathFollowComp on: %s") , *(this->GetName()))
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not get PathFollowComp on %s") ,*(this->GetName()) ));
		return;
	}
}

void AEnemyController::AssignTargetPivotCallback(USceneComponent* TargetPivotCallback)
{
	this->TargetPivot = TargetPivotCallback;
	//FTransform TargetTranform = Target->GetTransform();
	//MoveToTarget(TargetTranform);
}


void AEnemyController::Tick(float DeltaSeconds)
{
	if(IsDisabled)
	{
		StopMovement();
		return;
	}
	
	Super::Tick(DeltaSeconds);
	FTransform TargetTranform = Target->GetTransform();
	MoveToTarget(TargetTranform);
	RotateToTarget(TargetTranform ,DeltaSeconds);

	//auto CrowdManager = UCrowdManager::GetCurrent(GetWorld());
	//GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Current Active Agents: %i") ,CrowdManager->GetNumNearbyAgents(CrowdFollowingComponent.Get())));
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
		MoveToLocation(TargetPivot->GetComponentLocation() , StoppingDistance / 3);
		//CrowdFollowingComponent->ApplyCrowdAgentPosition(TargetPivot->GetComponentLocation());
		//CrowdFollowingComponent->ApplyCrowdAgentPosition(GetTransformComponent()->GetComponentLocation());
		//UCrowdManager::GetCurrent(GetWorld())->UpdateAgentParams(CrowdFollowingComponent.Get());
		//UCrowdManager::GetCurrent(GetWorld())->UpdateAgentState(CrowdFollowingComponent.Get());
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
	//return;
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
			} else
			{
				FRotator DesiredRotation = (TargetTransform.GetLocation() - ControlledPawn->GetActorLocation()).Rotation();
				DesiredRotation.Pitch = 0.0f;
				ControlledPawn->SetActorRotation(DesiredRotation);
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

AEnemyController::AEnemyController(const FObjectInitializer& ObjectInitializer)  : Super(ObjectInitializer.SetDefaultSubobjectClass<UEnemyCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyController::Disable()
{
	IsDisabled = true;
	CrowdFollowingComponentOverriden.Get()->Cleanup();
}

TSoftObjectPtr<APlayerPawn> AEnemyController::GetTargetPlayerPawn()
{
	return TargetPawn;
}


