// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Actors/Spawner/EnemySpawner.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<FEnemySpawnData>& AEnemySpawner::GetSpawnerDatas()
{
	return SpawnerDatas;
}

FEnemySpawnData& AEnemySpawner::GetSpawnData(int ID)
{
	if(ID >= SpawnerDatas.Num() || ID < 0)
	{
		//TO DO Fix this ugly return :(
		UE_LOG(LogTemp , Log , TEXT("Trying to aquire SpawnerDatas ID: %d but SpawnerDatas Count is: %d") , ID , SpawnerDatas.Num());
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Trying to obtain ID: %d , which is greater than SpawnerDatas Count: %d") , ID , SpawnerDatas.Num()));
		return *new FEnemySpawnData();
	}

	return SpawnerDatas[ID];
}

bool AEnemySpawner::DeleteSpawnData(int ID)
{
	if(ID >= SpawnerDatas.Num() || ID < 0)
	{
		UE_LOG(LogTemp , Log , TEXT("Trying to aquire SpawnerDatas ID: %d but SpawnerDatas Count is: %d") , ID , SpawnerDatas.Num());
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Trying to obtain ID: %d , which is greater than SpawnerDatas Count: %d") , ID , SpawnerDatas.Num()));
		return false;
	}

	SpawnerDatas.RemoveAt(ID);
	return true;
}

void AEnemySpawner::AddSpawnData()
{
	SpawnerDatas.Add(FEnemySpawnData());
}

int AEnemySpawner::GetSpawnDatasCount()
{
	return SpawnerDatas.Num();
}

void AEnemySpawner::ClearSpawnerDatas()
{
	SpawnerDatas = TArray<FEnemySpawnData>();
}



