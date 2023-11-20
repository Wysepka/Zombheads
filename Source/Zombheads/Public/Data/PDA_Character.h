// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_Character.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBHEADS_API UPDA_Character : public UPrimaryDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere , Category = "Player" , meta=(AllowPrivateAccess = "true"))
	float PlayerWalkingSpeed = 1.f;

	UPROPERTY(EditAnywhere , Category = "Player" , meta=(AllowPrivateAccess = "true"))
	float PlayerRunningSpeed = 1.f;

	UPROPERTY(EditAnywhere , Category = "Player" , meta=(AllowPrivateAccess = "true"))
	float MaxHealth;

	UPROPERTY(EditAnywhere , Category = "Player" , meta=(AllowPrivateAccess = "true"))
	float MaxStamina;
	
	UPROPERTY(EditAnywhere , Category = "Player" , meta=(AllowPrivateAccess = "true"))
	float StaminaDepletePerSec;

	UPROPERTY(EditAnywhere , Category = "Player" , meta=(AllowPrivateAccess = "true"))
	float StaminaIncreasePerSec;
	
public:

	float GetPlayerWalkingSpeed() const;
	float GetPlayerRunningSpeed() const;
	float GetCharacterMaxHealth() const;
	float GetCharacterMaxStamina() const;
	float GetCharacterStaminaDepletePerSec() const;
	float GetCharacterStaminaIncreasePerSec() const;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		FPrimaryAssetType PrimaryAssetType = FPrimaryAssetType("Character");
		FPrimaryAssetId PrimaryAssetId;

		PrimaryAssetId.PrimaryAssetType = PrimaryAssetType;

		return PrimaryAssetId;
	}

	//UPDA_Character& operator=(const UPDA_Character& other);
};
