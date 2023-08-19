// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/PlayerPawn.h"
#include "EnemyController.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnReachedTarget);
UCLASS()
class ZOMBHEADS_API AEnemyController : public AAIController
{
	GENERATED_BODY()
private:
	AActor* Target;

	UPROPERTY(EditAnywhere , Category = "Settings")
	float StoppingDistance;
	
protected:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

public:
	FOnReachedTarget OnReachedTarget;
	AEnemyController();
};