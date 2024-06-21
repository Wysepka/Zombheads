// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Data/Containers/Weapons/FHUDWeaponsData.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Utility/DebugUtility.h"

TSharedPtr<FSlateBrush> FHUDWeaponEntry::GetIconTextureBrush()
{
	if(IconTextureBrush.IsValid())
	{
		return IconTextureBrush;
	}
	IconTextureBrush = MakeShareable(new FSlateBrush(UWidgetBlueprintLibrary::MakeBrushFromTexture(IconTexture, 200 , 200)));
	return IconTextureBrush;
}


const FHUDWeaponEntry& FHUDWeaponsData::GetWeaponEntry(const FString& WeaponID)
{
	bool FoundEntry = false;
	for (size_t i = 0; i < WeaponData.Num(); i++)
	{
		if(WeaponData[i].GetWeaponID() == WeaponID)
		{
			return WeaponData[i];
		}
	}
	LOG_MISSING_DATA_ENTRY("Missing Weapon HUD Entry for ID: %s", *WeaponID);
	return DummyEntry;
}

TArray<FHUDWeaponEntry> FHUDWeaponsData::GetWeaponEntries()
{
	return WeaponData;
}

FHUDWeaponsData::FHUDWeaponsData()
{
}

FHUDWeaponsData::~FHUDWeaponsData()
{
}