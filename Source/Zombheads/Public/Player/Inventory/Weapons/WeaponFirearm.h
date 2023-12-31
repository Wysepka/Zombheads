// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "Player/Inventory/Weapons/WeaponBase.h"
#include "WeaponFirearm.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBHEADS_API AWeaponFirearm : public AWeaponBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere , Category = "Firearm")
	TSoftObjectPtr<USceneComponent> Muzzle;

	UPROPERTY(EditDefaultsOnly, Category = "Firearm")
	TSoftObjectPtr<USceneComponent> WeaponStartRaycast;

public:
	virtual void Use() override;

	UFUNCTION(BlueprintCallable, Category = "Firearm")
	void SetMuzzleSceneComponent(USceneComponent* value)
	{
		this->Muzzle = value;
	}

	UFUNCTION(BlueprintCallable, Category = "Firearm")
	void SetWeaponStartRaycastSceneComponent(USceneComponent* value)
	{
		this->WeaponStartRaycast = value;
	}

	virtual EItemType GetUsableType() const override {return EItemType::Firearm;}
	
};
