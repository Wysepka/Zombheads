// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "SHUDVitalityPanel.h"
#include "Slate.h"
//#include "SlateBasics.h"
#include "SlateCore.h"
//#include "SlateExtras.h"
#include "UI/HUDGameplay.h"

/**
 * 
 */
class SGameplayHUD : public SCompoundWidget
{
	TWeakObjectPtr<AHUDGameplay> OwningHUD;
	TSharedPtr<SHUDVitalityPanel> VitalityPanelChild;
	TSharedPtr<SOverlay> ParentOverlaySlot;
	
	SLATE_BEGIN_ARGS(SGameplayHUD) {}

	SLATE_ARGUMENT(TWeakObjectPtr<AHUDGameplay>, OwningHUDArg);
	SLATE_ARGUMENT(TWeakInterfacePtr<IVitalityComponent>, VitalityComponentArg);
	
	SLATE_END_ARGS()

	SGameplayHUD();
	
    void Construct(const FArguments& inArgs);
};
