// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "..\..\..\..\Public\Data\Containers\Vitality\FHUDVitalityData.h"


TSharedPtr<FSlateBrush> FHUDVitalityStatData::GetIconTextureBrush()
{
	if(IconTextureBrush.IsValid())
	{
		return IconTextureBrush;
	}
	
	IconTextureBrush = MakeShareable(new FSlateBrush( UWidgetBlueprintLibrary::MakeBrushFromTexture(IconTexture , 0 , 0)));
	return IconTextureBrush;
}

TSharedPtr<FSlateBrush> FHUDVitalityStatData::GetBackgroundTextureBrush()
{
	if(BackgroundTextureBrush.IsValid())
	{
		return BackgroundTextureBrush;
	}
	BackgroundTextureBrush = MakeShareable(new FSlateBrush(UWidgetBlueprintLibrary::MakeBrushFromTexture(BackgroundTexture, 0 , 0)));
	return BackgroundTextureBrush;
}

TSharedPtr<FSlateBrush> FHUDVitalityStatData::GetFillerTextureBrush()
{
	if(FillerTextureBrush.IsValid())
	{
		return FillerTextureBrush;
	}
	FillerTextureBrush = MakeShareable(new FSlateBrush(UWidgetBlueprintLibrary::MakeBrushFromTexture(FillerTexture, 0 , 0)));
	return FillerTextureBrush;
}

FHUDVitalityData::FHUDVitalityData()
{
}

FHUDVitalityData::~FHUDVitalityData()
{
}

const FHUDVitalityStatData& FHUDVitalityData::GetStaminaData()
{
	return StaminaData;
}

const FHUDVitalityStatData& FHUDVitalityData::GetHealthData()
{
	return HealthData;
}
