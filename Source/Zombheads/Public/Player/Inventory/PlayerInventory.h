//Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated 
//documentation files(the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and 
//to permit persons to whom the Software is furnished to do so, subject to the following conditions
#pragma once

#include "IPlayerInventory.h"
#include "Engine/AssetManager.h"
#include "Engine/World.h"
#include "Data/WeaponsPrimaryDataAsset.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "Utility/DebugUtility.h"
#include "Player/Inventory/Weapons/Usable.h"
#include "Components/SceneComponent.h"
#include "CoreMinimal.h"

/**
 * 
 */
DECLARE_DELEGATE(FStreamableDelegate);
class ZOMBHEADS_API PlayerInventory : public IPlayerInventory
{
private:
	TWeakObjectPtr<USceneComponent> ActiveContainer;
	TWeakObjectPtr<USceneComponent> DisabledContainer;

	FStreamableDelegate WeaponsLoadDelegate;
	int CurrentSlotEquiped = 0;
	UAssetManager* LastAssetManager;

	TWeakObjectPtr<AActor> Owner;
	UWorld* World;

	TMap<uint8 , IUsable*> WeaponCache;

	USoundWave* HolsterWeaponSound;
	USoundWave* UnHolsterWeaponSound;

	USkeletalMeshComponent* SkeletalMeshComp;
	FChangedSlotDelegate ChangedSlotDelegate;
	FInventoryItemUsedDelegate InventoryItemUsedDelegate;
	FOnWeaponChanged WeaponChangedDelegate;

public:
	PlayerInventory(const TWeakObjectPtr<USceneComponent>& ActiveContainer, const TWeakObjectPtr<USceneComponent>& DisabledContainer ,const TWeakObjectPtr<AActor>& Owner , UWorld* World);
	~PlayerInventory();

	virtual void Equip1Slot() override;
	void TryInvokeOnWeaponChangedDelegate();
	virtual void Equip2Slot() override;
	virtual void PreloadInventory(AAssetLoaderInitializer* AssetInitializer) override;
	virtual void GetWeaponsFromData(UWeaponsPrimaryDataAsset* WeaponsData) override;
	virtual void DeloadInventory() override;
	virtual void Use() override;
	virtual bool IsAiming() override;

	virtual FChangedSlotDelegate* GetChangedSlotDelegate() override;
	virtual FInventoryItemUsedDelegate* GetInventoryItemUsedDelegate() override;
	virtual FOnWeaponChanged* GetWeaponChangedDelegate() override;

	inline const static FString WeaponSocketRightID = FString("Socket_Weapon_Right");
};
