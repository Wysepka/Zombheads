// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "Actors/Enemy/EnemyBase.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnPoint.h"
#include <future>

#include "IEnemySpawnerInfo.h"
#include "EnemySpawner.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnEveryWaveCleared)

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
class ZOMBHEADS_API AEnemySpawner : public AActor , public IIEnemySpawnerInfo
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditInstanceOnly , meta = (AllowPrivateAccess = "true"))
	TArray<FEnemySpawnData> SpawnerDatas;
	
	TArray<TWeakObjectPtr<AEnemySpawnPoint>> SpawnPoints;
	int CurrentWave;
	int MaxSpawnDataWaveIdx;
	int CurrentSpawnPoint;
	int SpawnedEnemies;
	bool IsOverSpawnData;

	int CurrentWaveEnemiesDied;

	void OnEnemyDied(TWeakObjectPtr<AEnemyBase> EnemyDied);
	FTimerHandle SpawnHandle;
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<FEnemySpawnData>& GetSpawnerDatas();
	FEnemySpawnData& GetSpawnData(int ID);
	bool DeleteSpawnData(int ID);

	void AddSpawnData();
	int GetSpawnDatasCount();
	void ClearSpawnerDatas();
	virtual void PostInitializeComponents() override;
	void SpawnWave();
	void StartSpawning();

	virtual int GetCurrentWave() override;
	virtual TSharedPtr<FOnEnemyDied> GetOnEnemyDiedDelegate() override;
	
	FOnEveryWaveCleared OnEveryWaveCleared;
	
	FActorSpawnParameters SpawnParams;

	TSharedPtr<FOnEnemyDied> OnEnemyDiedEvent;
	
};
