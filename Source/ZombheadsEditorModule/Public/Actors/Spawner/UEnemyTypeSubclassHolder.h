// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Zombheads/Public/Actors/Enemy/EnemyBase.h"
#include "UEnemyTypeSubclassHolder.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBHEADSEDITORMODULE_API UUEnemyTypeSubclassHolder : public UObject
{
	GENERATED_BODY()


public:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	void ValidateEnemyBlueprint();
	void ValidateEnemyCount();
	void ValidateInBetweenSpawnDelay();
	void ValidateDelayBeforeSpawning();
	
	UPROPERTY(EditAnywhere , Category="EnemyData")
	TSubclassOf<AEnemyBase> EnemyBPHolder;

	UPROPERTY(EditAnywhere , Category = "EnemyData")
	uint32 EnemyCount;

	UPROPERTY(EditAnywhere , Category = "EnemyData")
	uint32 InBetweenSpawnDelay;
	
	UPROPERTY(EditAnywhere , Category = "EnemyData")
	uint32 DelayBeforeSpawning;
};
