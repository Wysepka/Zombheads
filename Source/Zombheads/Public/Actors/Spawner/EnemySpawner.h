// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "Actors/Enemy/EnemyBase.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

USTRUCT(BlueprintType)
struct FEnemySpawnData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TSubclassOf<AEnemyBase> EnemyBP;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	int EnemyCount;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	float InBetweenSpawnDelay;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	float DelayBeforeSpawning;
	
	// Constructor
	FEnemySpawnData()
		: EnemyBP(nullptr),
		  EnemyCount(0),
		  InBetweenSpawnDelay(0),
		  DelayBeforeSpawning(0)
	{
	}
};

UCLASS()
class ZOMBHEADS_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditInstanceOnly , meta = (AllowPrivateAccess = "true"))
	TArray<FEnemySpawnData> SpawnerDatas;
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<FEnemySpawnData>& GetSpawnerDatas();
	FEnemySpawnData& GetSpawnData(int ID);
	bool DeleteSpawnData(int ID);

	void AddSpawnData();
	int GetSpawnDatasCount();

	void ClearSpawnerDatas();

};
