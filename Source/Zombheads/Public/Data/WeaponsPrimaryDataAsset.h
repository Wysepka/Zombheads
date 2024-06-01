//Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated 
//documentation files(the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and 
//to permit persons to whom the Software is furnished to do so, subject to the following conditions
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/StaticMeshActor.h"
#include "Player/Inventory/Weapons/WeaponBase.h"
#include "WeaponsPrimaryDataAsset.generated.h"

/**
 * 
 */
class AWeaponBase;
USTRUCT(Blueprintable, BlueprintType)
struct FWeaponsData {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Weapons")
	FString WeaponID = "None";

	UPROPERTY(EditAnywhere, Category = "Weapons")
	TSubclassOf<class AWeaponBase> ActorBlueprint = nullptr;

	UPROPERTY(EditAnywhere,Category= "Weapons")
	uint8 SlotID = 1;

	UPROPERTY(EditAnywhere, Category= "Weapons")
	USoundWave* UseSound = nullptr;

	UPROPERTY(EditAnywhere , Category = "Weapons")
	float Damage = 0.0f;

	UPROPERTY(EditAnywhere , Category = "Weapons")
	int MaxAmmo = 0;
};

UCLASS()
class ZOMBHEADS_API UWeaponsPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
private:

	UPROPERTY(EditAnywhere, Category = "Weapons")
	TArray<FString> WeaponsIDActive;

	UPROPERTY(EditAnywhere, Category = "Weapons")
	TMap<FString, FWeaponsData> WeaponsDataMap;

	UPROPERTY(EditAnywhere , Category = "Weapons")
	USoundWave* WeaponHolsterSound;

	UPROPERTY(EditAnywhere , Category = "Weapons")
	USoundWave* WeaponUnHolsterSound;
	

public:

	//inline static FString DefinedAssetKey = "DA_Weapons";
	inline static FString DefinedAssetKey = "WeaponsPrimaryDataAsset";

	/*
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		FPrimaryAssetType PrimaryAssetType = FPrimaryAssetType(*DefinedAssetKey);
		FPrimaryAssetId PrimaryAssetId = FPrimaryAssetId(PrimaryAssetType , GetFName());

		//PrimaryAssetId.PrimaryAssetType = PrimaryAssetType;

		return PrimaryAssetId;
	}
	*/

	TArray<FString> GetActiveWeaponsIDs();
	TMap<FString, FWeaponsData> GetWeaponsDataMap();

	static FPrimaryAssetId DefinedAssetID()
	{
		FPrimaryAssetType PrimaryAssetType = FPrimaryAssetType(*DefinedAssetKey);
		FPrimaryAssetId PrimaryAssetId;

		PrimaryAssetId.PrimaryAssetType = PrimaryAssetType;

		return PrimaryAssetId;
	}
};