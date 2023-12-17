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
//#include "AnimationsPrimaryDataAsset.h"
#include "PDA_Character.h"
#include "PDA_HUD.h"
#include "Callbacks/AssetLoaderObserver.h"
#include "Callbacks/IAssetLoaderObserverRaw.h"
#include "Delegates/IDelegateInstance.h"
#include "Engine/StreamableManager.h"
//#include "Player/PlayerCharacterWrapper.h"
//#include "Player/PlayerCharacterWrapper.h"
#include "AssetLoader.generated.h"

/**
 * 
 */
class UWeaponsPrimaryDataAsset;
class UAnimationsPrimaryDataAsset;
class AAssetLoaderInitializer;
class UPDA_Character;
DECLARE_MULTICAST_DELEGATE_OneParam(FWeaponDataAssetLoadedDelegate , UWeaponsPrimaryDataAsset*);
DECLARE_MULTICAST_DELEGATE_OneParam(FAnimationsDataAssetLoadedDelegate, UAnimationsPrimaryDataAsset*);
DECLARE_MULTICAST_DELEGATE_OneParam(FCharacterDataAssetLoadedDelegate, UPDA_Character*)
DECLARE_MULTICAST_DELEGATE_OneParam(FHUDDataAssetLoadedDelegate, UPDA_HUD*)
DECLARE_MULTICAST_DELEGATE_OneParam(FPrimaryDataLoadedDelegate , UPrimaryDataAsset*)
DECLARE_DELEGATE(FStreamableDelegate);
class UDataAsset;
UCLASS(Blueprintable, BlueprintType)
class ZOMBHEADS_API UAssetLoader : public UObject
{
	GENERATED_BODY()
	friend class AAssetLoaderInitializer;
private:
	FStreamableDelegate AssetsLoadedDelegate;
	
	void LoadWeaponsPrimaryDataAsset();
	void LoadAnimationsPrimaryDataAsset();
	void LoadCharacterPrimaryDataAsset();
	void LoadHUDPrimaryDataAsset();
	
	void LoadAssets(UAssetManager* AssetManager);
	void AssetsLoadedCallback(FPrimaryAssetId ID);
	UAssetManager* LastAssetManager;
	
	FWeaponDataAssetLoadedDelegate WeaponsCallbacks;
	FAnimationsDataAssetLoadedDelegate AnimationsCallbacks;
	FCharacterDataAssetLoadedDelegate CharacterCallbacks;
	FHUDDataAssetLoadedDelegate HUDCallbacks;
	FPrimaryDataLoadedDelegate DataLoadedDelegate;

	UWeaponsPrimaryDataAsset* WeaponsData;
	UAnimationsPrimaryDataAsset* AnimationsData;
	UPDA_Character* CharacterData;
	UPDA_HUD* HUDData;
	
	bool bWeaponsDataLoaded;
	bool bAnimationsDataLoaded;
	bool bCharacterDataLoaded;
	bool bHUDDataLoaded;
	
public:
	
	[[deprecated("Use GetPrimaryDataAsset or GetPrimaryDataAssetRaw")]]
	FWeaponDataAssetLoadedDelegate* GetWeaponDataDelegate();
	bool GetIfWeaponsDataInitialized() const;
	UWeaponsPrimaryDataAsset* GetWeaponsData() const;

	[[deprecated("Use GetPrimaryDataAsset or GetPrimaryDataAssetRaw")]]
	FAnimationsDataAssetLoadedDelegate* GetAnimationsDataDelegate();
	bool GetIfAnimationsDataInitialized() const;
	UAnimationsPrimaryDataAsset* GetAnimationsData() const;

	[[deprecated("Use GetPrimaryDataAsset or GetPrimaryDataAssetRaw")]]
	FCharacterDataAssetLoadedDelegate* GetCharacterDataDelegate();
	bool GetIfCharactersDataInitialized() const;
	UPDA_Character* GetCharacterData() const;

	bool GetIfHUDDataInitialized() const;
	UPDA_HUD* GetHUDData() const;

    template <typename T, typename = std::enable_if_t<std::is_base_of<UPrimaryDataAsset, T>::value>>
	TTuple<bool, FDelegateHandle> GetPrimaryDataAsset(const IAssetLoaderObserver& ObserverInstance ,UPrimaryDataAsset*& Data);

	template <typename T, typename = std::enable_if_t<std::is_base_of<UPrimaryDataAsset, T>::value>>
	TTuple<bool, FDelegateHandle> GetPrimaryDataAsset(IAssetLoaderObserver* ObserverInstance ,T*& Data);

	template <typename T, typename = std::enable_if_t<std::is_base_of<UPrimaryDataAsset, T>::value>>
	TTuple<bool, FDelegateHandle> GetPrimaryDataAssetRaw(const IAssetLoaderObserverRaw& ObserverInstance, T*& Data);

	template <typename T, typename = std::enable_if_t<std::is_base_of<UPrimaryDataAsset, T>::value>>
	void UnRegisterCallback(FDelegateHandle* Handle);
};

template <typename T, typename>
TTuple<bool , FDelegateHandle> UAssetLoader::GetPrimaryDataAsset(const IAssetLoaderObserver& ObserverInstance , UPrimaryDataAsset*& Data)
{
	if (TIsSame<T, UPDA_Character>::Value)
	{
		if(GetIfCharactersDataInitialized())
		{
			//Data = Cast<UPrimaryDataAsset>(GetCharacterData());
			Data = Cast<UPrimaryDataAsset>(GetCharacterData());
			//Data = GetCharacterData();

			return MakeTuple(true, FDelegateHandle());
		}
		
		return MakeTuple(false, DataLoadedDelegate.AddUObject(&ObserverInstance , &IAssetLoaderObserver::PrimaryDataAssetLoaded));
	}
	if(TIsSame<T , UAnimationsPrimaryDataAsset>::Value)
	{
		if(GetIfAnimationsDataInitialized())
		{
			Data = Cast<UPrimaryDataAsset>(GetAnimationsData());
			return MakeTuple(true, FDelegateHandle());
		}
		
		return MakeTuple(false, DataLoadedDelegate.AddUObject(&ObserverInstance , &IAssetLoaderObserver::PrimaryDataAssetLoaded));
	}
	if(TIsSame<T, UWeaponsPrimaryDataAsset>::Value)
	{
		if(GetIfWeaponsDataInitialized())
		{
			Data = Cast<UPrimaryDataAsset>(GetWeaponsData());
			return MakeTuple(true, FDelegateHandle());
		}
		return MakeTuple(false, DataLoadedDelegate.AddUObject(&ObserverInstance , &IAssetLoaderObserver::PrimaryDataAssetLoaded));
	}
	if(TIsSame<T , UPDA_Character>::Value)
	{
		if(GetIfHUDDataInitialized())
		{
			Data = Cast<UPDA_Character>(GetHUDData());
			return MakeTuple(true, FDelegateHandle());
		}
		return MakeTuple(false, DataLoadedDelegate.AddUObject(&ObserverInstance , &IAssetLoaderObserver::PrimaryDataAssetLoaded));
	}
	return MakeTuple(false, nullptr);
}


template <typename T, typename>
TTuple<bool, FDelegateHandle> UAssetLoader::GetPrimaryDataAsset(IAssetLoaderObserver* ObserverInstance, T*& Data)
{
	
	if (TIsSame<T, UPDA_Character>::Value)
	{
		if(GetIfCharactersDataInitialized())
		{
			//Data = Cast<UPrimaryDataAsset>(GetCharacterData());
			Data = reinterpret_cast <T*>(GetCharacterData());
			//Data = GetCharacterData();
			//Data = GetCharacterData();

			return MakeTuple(true, FDelegateHandle());
		}
		
		return MakeTuple(false, CharacterCallbacks.AddRaw(ObserverInstance , &IAssetLoaderObserver::PrimaryDataAssetLoaded));
	}
	if(TIsSame<T , UAnimationsPrimaryDataAsset>::Value)
	{
		if(GetIfAnimationsDataInitialized())
		{
			Data = reinterpret_cast<T*>(GetAnimationsData());
			//Data = GetAnimationsData();
			return MakeTuple(true, FDelegateHandle());
		}
		
		return MakeTuple(false, AnimationsCallbacks.AddRaw(ObserverInstance , &IAssetLoaderObserver::PrimaryDataAssetLoaded));
	}
	if(TIsSame<T, UWeaponsPrimaryDataAsset>::Value)
	{
		if(GetIfWeaponsDataInitialized())
		{
			Data = reinterpret_cast<T*>(GetWeaponsData());
			//Data = GetWeaponsData();
			return MakeTuple(true, FDelegateHandle());
		}
		return MakeTuple(false, WeaponsCallbacks.AddRaw(ObserverInstance , &IAssetLoaderObserver::PrimaryDataAssetLoaded));
	}
	if(TIsSame<T , UPDA_HUD>::Value)
	{
		if(GetIfHUDDataInitialized())
		{
			Data = reinterpret_cast<T*>(GetHUDData());
			return MakeTuple(true, FDelegateHandle());
		}
		return MakeTuple(false, HUDCallbacks.AddRaw(ObserverInstance , &IAssetLoaderObserver::PrimaryDataAssetLoaded));
	}
	
	return MakeTuple(false, FDelegateHandle());
}

template <typename T, typename>
TTuple<bool, FDelegateHandle> UAssetLoader::GetPrimaryDataAssetRaw(const IAssetLoaderObserverRaw& ObserverInstance, T*& Data)
{
	if (TIsSame<T, UPDA_Character>::Value)
	{
		if(GetIfCharactersDataInitialized())
		{
			Data = GetCharacterData();
			return MakeTuple(true, FDelegateHandle());
		}

		return MakeTuple(false, CharacterCallbacks.AddUObject(&ObserverInstance , &ObserverInstance.PrimaryDataAssetLoadedRaw));
	}
	if(TIsSame<T , UAnimationsPrimaryDataAsset>::Value)
	{
		if(GetIfAnimationsDataInitialized())
		{
			Data = GetAnimationsData();
			return MakeTuple(true, FDelegateHandle());
		}
		return MakeTuple(false,AnimationsCallbacks.AddUObject(&ObserverInstance , &ObserverInstance.PrimaryDataAssetLoadedRaw));
	}
	if(TIsSame<T, UWeaponsPrimaryDataAsset>::Value)
	{
		if(GetIfWeaponsDataInitialized())
		{
			Data = GetWeaponsData();
			return MakeTuple(true, FDelegateHandle());
		}
		return MakeTuple(false,	WeaponsCallbacks.AddUObject(&ObserverInstance ,  &ObserverInstance.PrimaryDataAssetLoadedRaw));
	}
	if(TIsSame<T , UPDA_Character>::Value)
	{
		if(GetIfHUDDataInitialized())
		{
			Data = reinterpret_cast<T*>(GetHUDData());
			return MakeTuple(true, FDelegateHandle());
		}
		return MakeTuple(false, HUDCallbacks.AddUObject(&ObserverInstance , &ObserverInstance::PrimaryDataAssetLoadedRaw));
	}
	return MakeTuple(false, FDelegateHandle());
}


template <typename T, typename>
void UAssetLoader::UnRegisterCallback(FDelegateHandle* Handle)
{
	if (TIsSame<T, UPDA_Character>::Value)
	{
		CharacterCallbacks.Remove(*Handle);
	}
	if(TIsSame<T , UAnimationsPrimaryDataAsset>::Value)
	{
		AnimationsCallbacks.Remove(*Handle);
	}
	if(TIsSame<T, UWeaponsPrimaryDataAsset>::Value)
	{
		WeaponsCallbacks.Remove(*Handle);
	}
}


