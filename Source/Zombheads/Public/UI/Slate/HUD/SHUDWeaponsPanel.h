// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "Player/Inventory/IPlayerInventory.h"

/**
 * 
 */
class ZOMBHEADS_API SHUDWeaponsPanel: public SHorizontalBox
{
	SLATE_BEGIN_ARGS(SHUDWeaponsPanel) {}
	
	SLATE_ARGUMENT(TSharedPtr<IPlayerInventory>, PlayerInventoryArg);
	SLATE_ARGUMENT(FHUDWeaponsData, WeaponsDataArg);
	SLATE_ARGUMENT(FHUDVitalityData, VitalityDataArg);
	//SLATE_ARGUMENT(TWeakInterfacePtr<IVitalityComponent> , VitalityCompArg);

	SLATE_END_ARGS()
	
	SHUDWeaponsPanel();
	~SHUDWeaponsPanel();
	void Construct(const FArguments& inArgs);

private:
	TSharedPtr<SBox> WeaponIconContainer;
	TSharedPtr<SImage> WeaponIconImgPtr;

	TSharedPtr<SBox> WeaponAmmoContainer;
	TSharedPtr<STextBlock> WeaponAmmoText;
	
	TSharedPtr<IPlayerInventory> PlayerInventoryPtr;
	FHUDWeaponsData WeaponsDataPtr;
	FHUDVitalityData VitalityData;
	TArray<FHUDWeaponEntry> WeaponEntries;

	FDelegateHandle WeaponChangedHandle;
	FDelegateHandle InventoryItemUsedHandle;

	void OnPlayerWeaponChanged(const FString& WeaponID);
	void OnInventoryItemUsed(const IUsable& Usable);
};
