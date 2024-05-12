// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "UI/Slate/HUD/SHUDWeaponsPanel.h"

#include "Player/Inventory/Weapons/WeaponFirearm.h"

SHUDWeaponsPanel::SHUDWeaponsPanel()
{
}

SHUDWeaponsPanel::~SHUDWeaponsPanel()
{
	if(PlayerInventoryPtr.IsValid())
	{
		if(WeaponChangedHandle.IsValid())
		{
			PlayerInventoryPtr.Get()->GetWeaponChangedDelegate()->Remove(WeaponChangedHandle);
		}
		if(InventoryItemUsedHandle.IsValid())
		{
			PlayerInventoryPtr.Get()->GetInventoryItemUsedDelegate()->Remove(InventoryItemUsedHandle);
		}
	}
}

void SHUDWeaponsPanel::Construct(const FArguments& inArgs)
{
	PlayerInventoryPtr = inArgs._PlayerInventoryArg;
	WeaponsDataPtr = inArgs._WeaponsDataArg;
	VitalityData = inArgs._VitalityDataArg;

	WeaponEntries = WeaponsDataPtr.GetWeaponEntries();

	WeaponChangedHandle =  PlayerInventoryPtr.Get()->GetWeaponChangedDelegate()->AddRaw(this, &SHUDWeaponsPanel::OnPlayerWeaponChanged);
	InventoryItemUsedHandle = PlayerInventoryPtr.Get()->GetInventoryItemUsedDelegate()->AddRaw(this, &SHUDWeaponsPanel::OnInventoryItemUsed);
	
	
	WeaponIconContainer = SNew(SBox);
	WeaponIconImgPtr = SNew(SImage);

	
	//WeaponIconImgPtr
	SAssignNew(WeaponIconContainer , SBox)
	.WidthOverride(200.f)
	.HeightOverride(200.f)
	[
		SAssignNew(WeaponIconImgPtr , SImage)
	];
	
	FSlot* Slot1HZBase;
	FSlot* Slot2HZBase;

	AddSlot().Expose(Slot1HZBase);
	AddSlot().Expose(Slot2HZBase);

	Slot1HZBase->AttachWidget(WeaponIconContainer.ToSharedRef());
	
	SAssignNew(WeaponAmmoContainer , SBox)
	.HeightOverride(200.f)
	[
		SAssignNew(WeaponAmmoText , STextBlock)
	];
	
	Slot2HZBase->AttachWidget(WeaponAmmoContainer.ToSharedRef());
}

void SHUDWeaponsPanel::OnPlayerWeaponChanged(const FString& WeaponID)
{
	
	TSharedPtr<FSlateBrush> IconBrush;
	
	for (int i = 0; i < WeaponEntries.Num(); i++)
	{
		if(WeaponEntries[i].GetWeaponID() == WeaponID)
		{
			IconBrush = WeaponEntries[i].GetIconTextureBrush();
		}
	}
	
	if(IconBrush.IsValid())
	{
		WeaponIconImgPtr->SetImage(IconBrush.Get());
	}
	else
	{
		WeaponIconImgPtr->SetImage(nullptr);
		auto s = 's';
	}
	
	
	/*
	auto WeaponEntry = WeaponsDataPtr.GetWeaponEntry(WeaponID);
	auto WeaponIconBrush = WeaponEntry.GetIconTextureBrush();
	WeaponIconImgPtr.Get()->SetImage(WeaponIconBrush.Get());
	*/
}

void SHUDWeaponsPanel::OnInventoryItemUsed(const IUsable& Usable)
{
	
}
