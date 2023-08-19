// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Actors/Enemy/EnemyController.h"

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
	}
}

void AEnemyController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FTransform TargetTranform = Target->GetTransform();
	float DistToTarget = FVector::Distance(GetNavAgentLocation(),TargetTranform.GetLocation());
	if(DistToTarget > StoppingDistance)
	{
		if(!IsFollowingAPath())
		{
			//MoveToActor(Target , StoppingDistance);
			FAIMoveRequest MoveRequest;
			MoveToActor(Target , StoppingDistance);
			
			//MoveToLocation(GetNavAgentLocation()  + FVector::ForwardVector * 1000.f);
		}
	} else
	{
		if(OnReachedTarget.IsBound())
		{
			OnReachedTarget.Broadcast();
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


