//Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated 
//documentation files(the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and 
//to permit persons to whom the Software is furnished to do so, subject to the following conditions
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/AssetManager.h"
#include "AssetRegistry/AssetRegistryModule.h"
//#include "Data/WeaponsPrimaryDataAsset.h"
#include "Delegates/IDelegateInstance.h"
#include "Engine/StreamableManager.h"
#include "AssetLoader.generated.h"

/**
 * 
 */
class UWeaponsPrimaryDataAsset;
class AAssetLoaderInitializer;
DECLARE_MULTICAST_DELEGATE_OneParam(FWeaponDataAssetLoadedDelegate , UWeaponsPrimaryDataAsset*);
DECLARE_DELEGATE(FStreamableDelegate);
class UDataAsset;
UCLASS(Blueprintable, BlueprintType)
class ZOMBHEADS_API UAssetLoader : public UObject
{
	GENERATED_BODY()
	friend class AAssetLoaderInitializer;
private:
	FStreamableDelegate AssetsLoadedDelegate;
	void LoadAssets(UAssetManager* AssetManager);
	void AssetsLoadedCallback(FPrimaryAssetId ID);
	UAssetManager* LastAssetManager;
	FWeaponDataAssetLoadedDelegate WeaponsCallbacks;

	UWeaponsPrimaryDataAsset* WeaponsData;
	bool WeaponsDataLoaded;

public:
	FWeaponDataAssetLoadedDelegate* GetWeaponDataDelegate();
	bool GetIfWeaponsDataInitialized() const;
	UWeaponsPrimaryDataAsset* GetWeaponsData() const;
};
