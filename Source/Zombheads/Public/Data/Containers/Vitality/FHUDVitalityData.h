// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "FHUDVitalityData.generated.h"

/**
 * 
 */

USTRUCT(Blueprintable, BlueprintType)
struct FHUDVitalityStatData
{
	GENERATED_USTRUCT_BODY()
private:
	UPROPERTY(EditDefaultsOnly , meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> IconTexture;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> BackgroundTexture;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> FillerTexture;

	TSharedPtr<FSlateBrush> IconTextureBrush;
	TSharedPtr<FSlateBrush> BackgroundTextureBrush;
	TSharedPtr<FSlateBrush> FillerTextureBrush;


public:
	TSharedPtr<FSlateBrush> GetIconTextureBrush();
	TSharedPtr<FSlateBrush> GetBackgroundTextureBrush();
	TSharedPtr<FSlateBrush> GetFillerTextureBrush();
	
};

USTRUCT(Blueprintable, BlueprintType)
struct FHUDVitalityData
{
	GENERATED_USTRUCT_BODY()
private:
	UPROPERTY(EditDefaultsOnly , meta = (AllowPrivateAccess = "true"))
	FHUDVitalityStatData StaminaData;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FHUDVitalityStatData HealthData;
	
public:
	FHUDVitalityData();
	~FHUDVitalityData();

	const FHUDVitalityStatData& GetStaminaData();
	const FHUDVitalityStatData& GetHealthData();
};