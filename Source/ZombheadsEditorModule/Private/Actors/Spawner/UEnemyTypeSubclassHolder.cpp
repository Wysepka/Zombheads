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
	}
}

void UUEnemyTypeSubclassHolder::ValidateEnemyBlueprint()
{
	if (EnemyBPHolder != nullptr)
	{
		auto s = 's';
		// Perform validation logic here, for example:
		//UE_LOG(LogTemp, Warning, TEXT("WidgetBlueprint has been changed to %s"), *WidgetBlueprint->GetName());
	}
}

void UUEnemyTypeSubclassHolder::ValidateEnemyCount()
{
	auto s = 's';
}

void UUEnemyTypeSubclassHolder::ValidateInBetweenSpawnDelay()
{
	auto s = 's';
}

void UUEnemyTypeSubclassHolder::ValidateDelayBeforeSpawning()
{
	auto s = 's';
}
