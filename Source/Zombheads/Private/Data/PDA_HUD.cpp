// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Data/PDA_HUD.h"

const FHUDVitalityData& UPDA_HUD::GetVitalityData()
{
	/*
	if(VitalityDataPtr == nullptr)
	{
		VitalityDataPtr = MakeShareable(&VitalityData);
	}
	*/
	return VitalityData;
}

const FHUDWeaponsData& UPDA_HUD::GetWeaponsData()
{
	return WeaponsData;
}

TSharedPtr<const FSlateBrush> UPDA_HUD::GetBackgroundWaveBrush()
{
	if(!BackgroundWaveBrush.IsValid())
	{
		BackgroundWaveBrush = MakeShareable(new FSlateBrush(UWidgetBlueprintLibrary::MakeBrushFromTexture(BackgroundWaveTexture , 150 , 150)));
	}
	return BackgroundWaveBrush;
}
