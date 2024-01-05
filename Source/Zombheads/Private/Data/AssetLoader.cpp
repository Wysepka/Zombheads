//Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated 
//documentation files(the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and 
//to permit persons to whom the Software is furnished to do so, subject to the following conditions

#include "Data/AssetLoader.h"
#include "Data/WeaponsPrimaryDataAsset.h"
#include "Data/AnimationsPrimaryDataAsset.h"
#include "Data/PDA_Character.h"

void UAssetLoader::LoadAssets(UAssetManager* AssetManager)
{
	
	if(!AssetManager->IsValid())
	{
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , TEXT("Asset Manager is not valid"));
		UE_LOG(LogTemp, Log, TEXT("AssetManager is not valid"));
		return;
	}
	LastAssetManager = AssetManager;
	//LastAssetManager.getprim
	LoadWeaponsPrimaryDataAsset();
	LoadAnimationsPrimaryDataAsset();
	LoadCharacterPrimaryDataAsset();
	LoadHUDPrimaryDataAsset();
}

void UAssetLoader::LoadWeaponsPrimaryDataAsset()
{
	FPrimaryAssetType PrimaryAssetType = FPrimaryAssetType(*UWeaponsPrimaryDataAsset::DefinedAssetKey);
	TArray<FPrimaryAssetId> WeaponIDList;
	LastAssetManager->GetPrimaryAssetIdList(PrimaryAssetType, WeaponIDList);

	for (const FPrimaryAssetId& WeaponId : WeaponIDList)
	{
		FPrimaryAssetId AssetID = WeaponId;
		// Get tag/value data for an unloaded weapon
		FAssetData AssetDataToParse;
		LastAssetManager->GetPrimaryAssetData(WeaponId, AssetDataToParse);
		TArray<FName> Bundles;
		AssetsLoadedDelegate.BindUObject(this, &UAssetLoader::AssetsLoadedCallback, WeaponId);
		LastAssetManager->LoadPrimaryAsset(WeaponId, Bundles, AssetsLoadedDelegate);

		//AssetDataToParse.
		UE_LOG(LogTemp, Log, TEXT("AssetData ClassName %s"), *AssetDataToParse.AssetClassPath.ToString());
	}
}

void UAssetLoader::LoadAnimationsPrimaryDataAsset()
{
	FPrimaryAssetType PrimaryAssetType = FPrimaryAssetType(*UAnimationsPrimaryDataAsset::DefinedAssetKey);
	TArray<FPrimaryAssetId> AnimationsIDList;
	LastAssetManager->GetPrimaryAssetIdList(PrimaryAssetType, AnimationsIDList);
	//LastAssetManager.getpri

	for (const FPrimaryAssetId& AnimationID : AnimationsIDList)
	{
		FPrimaryAssetId AssetID = AnimationID;
		FAssetData AssetDataToParse;
		LastAssetManager->GetPrimaryAssetData(AnimationID, AssetDataToParse);
		TArray<FName> Bundles;
		AssetsLoadedDelegate.BindUObject(this, &UAssetLoader::AssetsLoadedCallback, AnimationID);
		LastAssetManager->LoadPrimaryAsset(AnimationID, Bundles, AssetsLoadedDelegate);

		//AssetDataToParse.
		UE_LOG(LogTemp, Log, TEXT("AssetData ClassName %s"), *AssetDataToParse.AssetClassPath.ToString());
	}
}

void UAssetLoader::LoadCharacterPrimaryDataAsset()
{
	FPrimaryAssetType PrimaryAssetType = FPrimaryAssetType(*UPDA_Character::DefinedAssetKey);
	TArray<FPrimaryAssetId> IDList;
	LastAssetManager->GetPrimaryAssetIdList(PrimaryAssetType, IDList);

	for (const FPrimaryAssetId& ID : IDList)
	{
		FPrimaryAssetId AssetID = ID;
		FAssetData AssetDataToParse;
		LastAssetManager->GetPrimaryAssetData(ID, AssetDataToParse);
		TArray<FName> Bundles;
		AssetsLoadedDelegate.BindUObject(this, &UAssetLoader::AssetsLoadedCallback, ID);
		LastAssetManager->LoadPrimaryAsset(ID, Bundles, AssetsLoadedDelegate);

		//AssetDataToParse.
		UE_LOG(LogTemp, Log, TEXT("AssetData ClassName %s"), *AssetDataToParse.AssetClassPath.ToString());
	}
}

void UAssetLoader::LoadHUDPrimaryDataAsset()
{
	FPrimaryAssetType PrimaryAssetType = FPrimaryAssetType(*UPDA_HUD::DefinedAssetKey);
	TArray<FPrimaryAssetId> IDList;
	LastAssetManager->GetPrimaryAssetIdList(PrimaryAssetType, IDList);

	for (const FPrimaryAssetId& ID : IDList)
	{
		FPrimaryAssetId AssetID = ID;
		FAssetData AssetDataToParse;
		LastAssetManager->GetPrimaryAssetData(ID, AssetDataToParse);
		TArray<FName> Bundles;
		AssetsLoadedDelegate.BindUObject(this, &UAssetLoader::AssetsLoadedCallback, ID);
		LastAssetManager->LoadPrimaryAsset(ID, Bundles, AssetsLoadedDelegate);

		//AssetDataToParse.
		UE_LOG(LogTemp, Log, TEXT("AssetData ClassName %s"), *AssetDataToParse.AssetClassPath.ToString());
	}
}

void UAssetLoader::AssetsLoadedCallback(FPrimaryAssetId ID)
{
	if(ID.PrimaryAssetType == UWeaponsPrimaryDataAsset::DefinedAssetID().PrimaryAssetType)	
	{
		WeaponsData = LastAssetManager->GetPrimaryAssetObject<UWeaponsPrimaryDataAsset>(ID);
		if (WeaponsData == nullptr) {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("ERROR: Could not load WeaponsData"));
			return;
		}
		bWeaponsDataLoaded = true;
		if(WeaponsCallbacks.IsBound())
		{
			WeaponsCallbacks.Broadcast(WeaponsData);
		}
	} else if(ID.PrimaryAssetType == UAnimationsPrimaryDataAsset::DefinedAssetID().PrimaryAssetType)
	{
		AnimationsData = LastAssetManager->GetPrimaryAssetObject<UAnimationsPrimaryDataAsset>(ID);
		if (AnimationsData == nullptr) {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("ERROR: Could not load AnimationsData"));
			return;
		}
		bAnimationsDataLoaded = true;
		if(AnimationsCallbacks.IsBound())
		{
			AnimationsCallbacks.Broadcast(AnimationsData);
		}
	} else if(ID.PrimaryAssetType == UPDA_Character::DefinedAssetID().PrimaryAssetType)
	{
		CharacterData = LastAssetManager->GetPrimaryAssetObject<UPDA_Character>(ID);
		if (CharacterData == nullptr) {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("ERROR: Could not load CharacterData"));
			return;
		}
		bCharacterDataLoaded = true;
		if(CharacterCallbacks.IsBound())
		{
			CharacterCallbacks.Broadcast(CharacterData);
		}
	} else if(ID.PrimaryAssetType == UPDA_HUD::DefinedAssetID().PrimaryAssetType)
	{
		HUDData = LastAssetManager->GetPrimaryAssetObject<UPDA_HUD>(ID);
		if (HUDData == nullptr) {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("ERROR: Could not load HUDData"));
			return;
		}
		bHUDDataLoaded = true;
		if(HUDCallbacks.IsBound())
		{
			HUDCallbacks.Broadcast(HUDData);
		}
	}
}

FWeaponDataAssetLoadedDelegate* UAssetLoader::GetWeaponDataDelegate()
{
	return &WeaponsCallbacks;
}

bool UAssetLoader::GetIfWeaponsDataInitialized() const
{
	return bWeaponsDataLoaded;
}

UWeaponsPrimaryDataAsset* UAssetLoader::GetWeaponsData() const
{
	return WeaponsData;
}

FAnimationsDataAssetLoadedDelegate* UAssetLoader::GetAnimationsDataDelegate()
{
	return &AnimationsCallbacks;
}

bool UAssetLoader::GetIfAnimationsDataInitialized() const
{
	return bAnimationsDataLoaded;
}

UAnimationsPrimaryDataAsset* UAssetLoader::GetAnimationsData() const
{
	return AnimationsData;
}

FCharacterDataAssetLoadedDelegate* UAssetLoader::GetCharacterDataDelegate()
{
	return &CharacterCallbacks;
}

bool UAssetLoader::GetIfCharactersDataInitialized() const
{
	return bCharacterDataLoaded;
}

UPDA_Character* UAssetLoader::GetCharacterData() const
{
	return CharacterData;
}

bool UAssetLoader::GetIfHUDDataInitialized() const
{
	return bHUDDataLoaded;
}

UPDA_HUD* UAssetLoader::GetHUDData() const
{
	return HUDData;
}

