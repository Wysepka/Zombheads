// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "UI/Slate/HUD/SHUDVitalityPanel.h"


SHUDVitalityPanel::SHUDVitalityPanel(SWidget* Owner, FName Name)
{
	
	//this->Owner = Owner;
}


SHUDVitalityPanel::SHUDVitalityPanel()
{
	//ChildrenSlots = {this};
}

void SHUDVitalityPanel::Construct(const FArguments& inArgs)
{
	FSlot* Slot1HZBase;
	FSlot* Slot2HZBase;

	AddSlot().Expose(Slot1HZBase);
	AddSlot().Expose(Slot2HZBase);
	
	Slot1HZBase->SetVerticalAlignment(VAlign_Top);
	Slot2HZBase->SetVerticalAlignment(VAlign_Bottom);

	//-const auto worldLoc = GEngine->GetWorld();
	
	//auto VitalityComp = PlayerPawn->GetVitalityComponent();
	VitalityData = inArgs._VitalityDataArg;
	VitalityComp = inArgs._VitalityCompArg;

	/* const TFunction<float()> */ StaminaPercentageFnc = [this](){return VitalityComp.Get()->CurrentStaminaPercentage();};
	/* const TFunction<float()> */ HealthPercentageFnc = [this](){return VitalityComp.Get()->CurrentHealthPercentage();};
	
	StaminaStat = SNew(SHUDVitalityStat).VitalityStatDataArg(VitalityData.GetStaminaData()).StatPercentageFunctionArg(StaminaPercentageFnc);
	StaminaStat->SetVisibility(EVisibility::Visible);
	HealthStat = SNew(SHUDVitalityStat).VitalityStatDataArg(VitalityData.GetHealthData()).StatPercentageFunctionArg(HealthPercentageFnc);
	HealthStat->SetVisibility(EVisibility::Visible);

	Slot1HZBase->SetMaxHeight(100.f);
	Slot2HZBase->SetMaxHeight(100.f);
	
	Slot1HZBase->AttachWidget(StaminaStat.ToSharedRef());
	Slot2HZBase->AttachWidget(HealthStat.ToSharedRef());
}
