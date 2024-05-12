//Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated 
//documentation files(the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and 
//to permit persons to whom the Software is furnished to do so, subject to the following conditions

#include "Player/Inventory/IPlayerInventory.h"

IPlayerInventory::IPlayerInventory()
{
	bIsValid = true;
}

IPlayerInventory::~IPlayerInventory()
{
}

void IPlayerInventory::Equip1Slot() {

}

void IPlayerInventory::Equip2Slot()
{
	
}

void IPlayerInventory::PreloadInventory(AAssetLoaderInitializer* AssetInitializer)
{
}

void IPlayerInventory::GetWeaponsFromData(UWeaponsPrimaryDataAsset* WeaponsData)
{
}

void IPlayerInventory::DeloadInventory()
{
	bIsValid = false;
}

void IPlayerInventory::Use()
{
}

bool IPlayerInventory::IsAiming()
{
	return false;
}

FChangedSlotDelegate* IPlayerInventory::GetChangedSlotDelegate()
{
	UE_LOG(LogTemp, Log, TEXT("Returning nullptr from GetChangedSlotDelegate"));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Returning nullptr from GetChangedSlotDelegate"));
	return nullptr;
}

FInventoryItemUsedDelegate* IPlayerInventory::GetInventoryItemUsedDelegate()
{
	UE_LOG(LogTemp, Log, TEXT("Returning nullptr from GetInventoryItemUsedDelegate"));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Returning nullptr from GetInventoryItemUsedDelegate"));
		
	return nullptr;
}

FOnWeaponChanged* IPlayerInventory::GetWeaponChangedDelegate()
{
	UE_LOG(LogTemp, Log, TEXT("Returning nullptr from GetWeaponChangedDelegate"));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Returning nullptr from GetWeaponChangedDelegate"));
		
	return nullptr;
}

bool IPlayerInventory::IsValid()
{
	return bIsValid;
}
