// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "SHUDVitalityPanel.h"
#include "Slate.h"
//#include "SlateBasics.h"
#include "SlateCore.h"
//#include "SlateExtras.h"
#include "SHUDPointsCounter.h"
#include "SHUDWavePanel.h"
#include "SHUDWeaponsPanel.h"
#include "UI/HUDGameplay.h"
#include "Actors/Spawner/IEnemySpawnerInfo.h"
#include "Managers/Statistics/StateStatInfo.h"

/**
 * 
 */
class SGameplayHUD : public SCompoundWidget
{
	TWeakObjectPtr<AHUDGameplay> OwningHUD;
	TSharedPtr<SHUDVitalityPanel> VitalityPanelChild;
	TSharedPtr<SOverlay> ParentOverlaySlot;
	TSharedPtr<SHUDWavePanel> WavePanel;
	TSharedPtr<SHUDPointsCounter> PointsCounter;

	TSharedPtr<SHUDWeaponsPanel> WeaponPanelChild;
	
	SLATE_BEGIN_ARGS(SGameplayHUD) {}

	SLATE_ARGUMENT(TWeakObjectPtr<AHUDGameplay>, OwningHUDArg);
	SLATE_ARGUMENT(TWeakInterfacePtr<IVitalityComponent>, VitalityComponentArg);
	SLATE_ARGUMENT(TWeakPtr<IPlayerInventory> , PlayerInventoryArg)
	SLATE_ARGUMENT(TWeakInterfacePtr<IIEnemySpawnerInfo>, EnemySpawnerInfoArg)
	SLATE_ARGUMENT(TSharedPtr<StateStatInfo>, StateStatInfoArg)
	SLATE_END_ARGS()

	SGameplayHUD();
	
    void Construct(const FArguments& inArgs);
};
