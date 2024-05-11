// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Zombheads/Public/Actors/Enemy/EnemyBase.h"
#include "Zombheads/Public/Actors/Spawner/EnemySpawner.h"
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

	void Init(TSharedPtr<FEnemySpawnData> Data , TStrongObjectPtr<AEnemySpawner> EnemySpawnerPtrOther);
	void Dispose();

	TSharedPtr<FEnemySpawnData> BindedData;
	TStrongObjectPtr<AEnemySpawner> EnemySpawnerPtr;

	UPROPERTY(VisibleAnywhere, Category="EnemyData")
	uint32 ID;
	
	UPROPERTY(EditAnywhere , Category="EnemyData")
	TSubclassOf<AEnemyBase> EnemyBPHolder;

	UPROPERTY(EditAnywhere , Category = "EnemyData")
	uint32 EnemyCount;

	UPROPERTY(EditAnywhere , Category = "EnemyData")
	float InBetweenSpawnDelay;
	
	UPROPERTY(EditAnywhere , Category = "EnemyData")
	float DelayBeforeSpawning;
};
