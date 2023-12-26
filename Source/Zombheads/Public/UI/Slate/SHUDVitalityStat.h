// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "SlateCore.h"
#include "SlateExtras.h"
#include "SlateBasics.h"
#include "Data/Containers/Vitality/FHUDVitalityData.h"

/**
 * 
 */
class SHUDVitalityStat : public SHorizontalBox /* , public FChildren */
{
	//SLATE_DECLARE_WIDGET(SHUDVitalityStat, SPanel)
	SLATE_BEGIN_ARGS(SHUDVitalityStat){}
	
	SLATE_ARGUMENT(FHUDVitalityStatData, VitalityStatDataArg)
	SLATE_ARGUMENT(TFunction<float()> , StatPercentageFunctionArg);
	
	SLATE_END_ARGS()

	SHUDVitalityStat(SWidget* Owner , FName Name);
	SHUDVitalityStat();

    void Construct(const FArguments& inArgs);
	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	FHUDVitalityStatData StatData;
	
	TSharedPtr<SImage> IconImg;
	TSharedPtr<SImage> BackgroundImg;
	TSharedPtr<SProgressBar> FillerImg;
	TFunction<float()> StatPercentageFunction;
};
