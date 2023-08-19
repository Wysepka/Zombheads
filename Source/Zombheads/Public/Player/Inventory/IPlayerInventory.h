//Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated 
//documentation files(the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and 
//to permit persons to whom the Software is furnished to do so, subject to the following conditions
#pragma once

#include "Components/InputComponent.h"
#include "Engine/AssetManager.h"
#include "CoreMinimal.h"
#include "Data/AssetLoaderInitializer.h"

/**
 * 
 */
class ZOMBHEADS_API IPlayerInventory
{
private:
	//int CurrentSlotEquiped = 0;

public:
	IPlayerInventory();
	virtual ~IPlayerInventory();

	virtual void Equip1Slot();
	virtual void Equip2Slot();
	virtual void PreloadInventory(AAssetLoaderInitializer* AssetInitializer);
	virtual void GetWeaponsFromData(UWeaponsPrimaryDataAsset* WeaponsData);
	virtual void DeloadInventory();
	virtual void Use();

};
