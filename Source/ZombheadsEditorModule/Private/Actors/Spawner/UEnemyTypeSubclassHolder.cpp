// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombheadsEditorModule/Public/Actors/Spawner/UEnemyTypeSubclassHolder.h"


void UUEnemyTypeSubclassHolder::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property != nullptr)
	{
		const FName PropertyName = PropertyChangedEvent.Property->GetFName();

		// Check if the property changed is "WidgetBlueprint"
		if (PropertyName == GET_MEMBER_NAME_CHECKED(UUEnemyTypeSubclassHolder, EnemyBPHolder))
		{
			// Validate or react to the change
			ValidateEnemyBlueprint();
		}
		if (PropertyName == GET_MEMBER_NAME_CHECKED(UUEnemyTypeSubclassHolder, EnemyCount))
		{
			ValidateEnemyCount();
		}
		if (PropertyName == GET_MEMBER_NAME_CHECKED(UUEnemyTypeSubclassHolder, InBetweenSpawnDelay))
		{
			ValidateInBetweenSpawnDelay();
		}
		if (PropertyName == GET_MEMBER_NAME_CHECKED(UUEnemyTypeSubclassHolder, DelayBeforeSpawning))
		{
			ValidateDelayBeforeSpawning();
		}

		if(EnemySpawnerPtr.IsValid())
		{
			EnemySpawnerPtr->PostEditChangeProperty(PropertyChangedEvent);
		}
	}
}

void UUEnemyTypeSubclassHolder::ValidateEnemyBlueprint()
{
	if (EnemyBPHolder != nullptr)
	{
		BindedData.Get()->EnemyBP = EnemyBPHolder;
	}
}

void UUEnemyTypeSubclassHolder::ValidateEnemyCount()
{
	BindedData.Get()->EnemyCount = EnemyCount;
}

void UUEnemyTypeSubclassHolder::ValidateInBetweenSpawnDelay()
{
	BindedData.Get()->InBetweenSpawnDelay = InBetweenSpawnDelay;
}

void UUEnemyTypeSubclassHolder::ValidateDelayBeforeSpawning()
{
	BindedData.Get()->DelayBeforeSpawning = DelayBeforeSpawning;
}

void UUEnemyTypeSubclassHolder::Init(TSharedPtr<FEnemySpawnData> Data , TStrongObjectPtr<AEnemySpawner> EnemySpawnerPtrOther)
{
	BindedData = Data;
	EnemySpawnerPtr = EnemySpawnerPtrOther;
}

void UUEnemyTypeSubclassHolder::Dispose()
{
	EnemySpawnerPtr.Reset();
}
