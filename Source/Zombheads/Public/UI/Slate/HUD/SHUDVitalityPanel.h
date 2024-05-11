// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "SlateCore.h"
#include "SlateExtras.h"
#include "Characters/PlayerPawn.h"
#include "SHUDVitalityStat.h"

/**
 * 
 */
class  SHUDVitalityPanel : public SVerticalBox
{
	SLATE_BEGIN_ARGS(SHUDVitalityPanel) {}
	
	SLATE_ARGUMENT(FHUDVitalityData, VitalityDataArg);
	SLATE_ARGUMENT(TWeakInterfacePtr<IVitalityComponent> , VitalityCompArg);

	SLATE_END_ARGS()
	
	SHUDVitalityPanel(SWidget* Owner, FName Name);
	SHUDVitalityPanel();
    void Construct(const FArguments& inArgs);
	
	TSharedPtr<SHUDVitalityStat> StaminaStat;
	TSharedPtr<SHUDVitalityStat> HealthStat;
	
	FHUDVitalityData VitalityData;
	TWeakInterfacePtr<IVitalityComponent> VitalityComp;

	TFunction<float()> StaminaPercentageFnc;
	TFunction<float()> HealthPercentageFnc;
};
