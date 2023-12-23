// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#include "UI/Slate/SGameplayHUD.h"
#include "UI/HUDGameplay.h"


SGameplayHUD::SGameplayHUD()
{
}

void SGameplayHUD::Construct(const FArguments& inArgs)
{
	OwningHUD = inArgs._OwningHUDArg;
	ParentOverlaySlot = SNew(SOverlay);
	ChildSlot.AttachWidget(ParentOverlaySlot.ToSharedRef());
	
	SOverlay::FOverlaySlot* ParentSlotBase;
	ParentOverlaySlot->AddSlot().Expose(ParentSlotBase);
	ParentSlotBase->SetHorizontalAlignment(HAlign_Right);
	ParentSlotBase->SetVerticalAlignment(VAlign_Top);

	SAssignNew(VitalityPanelChild , SHUDVitalityPanel).VitalityDataArg(OwningHUD->GetFHUDVitalityData());
	VitalityPanelChild->SetVisibility(EVisibility::Visible);
	
	//VitalityPanelChild = SNew(SHUDVitalityPanel);
	ParentSlotBase->AttachWidget(VitalityPanelChild.ToSharedRef());
	//ParentSlotBase->AttachWidget(VitalityPanelChild.Pin().ToSharedRef());
}
