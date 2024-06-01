// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "Containers/Weapons/FHUDWeaponsData.h"
#include "Engine/DataAsset.h"
#include "Data/Containers/Vitality/FHUDVitalityData.h"
#include "PDA_HUD.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBHEADS_API UPDA_HUD : public UPrimaryDataAsset
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FHUDVitalityData VitalityData;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UImage* Image;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FHUDWeaponsData WeaponsData;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> BackgroundWaveTexture;


	TSharedPtr<FSlateBrush>  BackgroundWaveBrush;

public:
	const FHUDVitalityData& GetVitalityData();
	const FHUDWeaponsData& GetWeaponsData();
	TSharedPtr<const FSlateBrush> GetBackgroundWaveBrush();

	//inline static FString DefinedAssetKey = "DA_HUD";
	inline static FString DefinedAssetKey = "PDA_HUD";

	/*
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		FPrimaryAssetType PrimaryAssetType = FPrimaryAssetType(*DefinedAssetKey);
		FPrimaryAssetId PrimaryAssetId = FPrimaryAssetId(PrimaryAssetType , GetFName());

		//PrimaryAssetId.PrimaryAssetType = PrimaryAssetType;

		return PrimaryAssetId;
	}
	*/

	static FPrimaryAssetId DefinedAssetID()
	{
		FPrimaryAssetType PrimaryAssetType = FPrimaryAssetType(*DefinedAssetKey);
		FPrimaryAssetId PrimaryAssetId;

		PrimaryAssetId.PrimaryAssetType = PrimaryAssetType;

		return PrimaryAssetId;
	}
};
