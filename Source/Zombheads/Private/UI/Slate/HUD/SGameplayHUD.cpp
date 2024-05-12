// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#include "UI/Slate/HUD/SGameplayHUD.h"
#include "UI/HUDGameplay.h"


SGameplayHUD::SGameplayHUD()
{
}

void SGameplayHUD::Construct(const FArguments& inArgs)
{
	OwningHUD = inArgs._OwningHUDArg;
	ParentOverlaySlot = SNew(SOverlay);
	ChildSlot.AttachWidget(ParentOverlaySlot.ToSharedRef());
	
	SOverlay::FOverlaySlot* VitalityParentSlot;
	ParentOverlaySlot->AddSlot().Expose(VitalityParentSlot);
	VitalityParentSlot->SetHorizontalAlignment(HAlign_Right);
	VitalityParentSlot->SetVerticalAlignment(VAlign_Top);

	SAssignNew(VitalityPanelChild , SHUDVitalityPanel).VitalityDataArg(OwningHUD->GetFHUDVitalityData()).VitalityCompArg(inArgs._VitalityComponentArg);
	VitalityPanelChild->SetVisibility(EVisibility::Visible);
	
	//VitalityPanelChild = SNew(SHUDVitalityPanel);
	VitalityParentSlot->AttachWidget(VitalityPanelChild.ToSharedRef());

	VitalityParentSlot->SetHorizontalAlignment(HAlign_Right);

	SOverlay::FOverlaySlot* WeaponsParentSlot;
	ParentOverlaySlot->AddSlot().Expose(WeaponsParentSlot);
	WeaponsParentSlot->SetHorizontalAlignment(HAlign_Right);
	WeaponsParentSlot->SetVerticalAlignment(VAlign_Bottom);

	SAssignNew(WeaponPanelChild , SHUDWeaponsPanel).PlayerInventoryArg(inArgs._PlayerInventoryArg.Pin()).WeaponsDataArg(OwningHUD->GetFHUDWeaponsData()).VitalityDataArg(OwningHUD->GetFHUDVitalityData());
	WeaponPanelChild->SetVisibility(EVisibility::Visible);
	
	WeaponsParentSlot->AttachWidget(WeaponPanelChild.ToSharedRef());

	//ParentSlotBase->AttachWidget(VitalityPanelChild.Pin().ToSharedRef());
}
