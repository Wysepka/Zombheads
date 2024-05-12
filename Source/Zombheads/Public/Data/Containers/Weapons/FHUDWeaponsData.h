// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "Utility/DebugUtility.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "FHUDWeaponsData.generated.h"

/**
 * 
 */

USTRUCT(Blueprintable, BlueprintType)
struct FHUDWeaponEntry
{
	GENERATED_USTRUCT_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Weapons")
	FString WeaponID;

	UPROPERTY(EditAnywhere, Category = "Weapons")
	TObjectPtr<UTexture2D> IconTexture;

	UPROPERTY(EditAnywhere, Category = "Weapons")
	uint32 MaxAmmo;
	
	TSharedPtr<FSlateBrush> IconTextureBrush;

public:
	FString GetWeaponID()
	{
		return WeaponID;
	}

	TSharedPtr<FSlateBrush> GetIconTextureBrush();
}; 

USTRUCT(Blueprintable, BlueprintType)
struct FHUDWeaponsData
{
	GENERATED_USTRUCT_BODY()
private:
	UPROPERTY(EditDefaultsOnly , meta = (AllowPrivateAccess = "true"))
	TArray<FHUDWeaponEntry> WeaponData;

	FHUDWeaponEntry DummyEntry;
	
public:
	FHUDWeaponsData();
	~FHUDWeaponsData();

	const FHUDWeaponEntry& GetWeaponEntry(const FString& WeaponID);
	TArray<FHUDWeaponEntry> GetWeaponEntries();
};
