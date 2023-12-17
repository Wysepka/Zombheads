// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "UI/Slate/SHUDVitalityPanel.h"

/*
void SHUDVitalityPanel::OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const
{
}

FVector2D SHUDVitalityPanel::ComputeDesiredSize(float LayoutScaleMultiplier) const
{
	return FVector2d(10 , 10);
	//return StaminaStat->ComputeDesiredSize(LayoutScaleMultiplier) + HealthStat->ComputeDesiredSize(LayoutScaleMultiplier);
}


bool SHUDVitalityPanel::SupportsKeyboardFocus() const
{
	return false;
}

FChildren* SHUDVitalityPanel::GetChildren()
{
	return &ChildrenSlots;
}
*/

/*
SHUDVitalityPanel::SHUDVitalityPanel(SWidget* Owner, FName Name) : FChildren(this)
{
	//this->Owner = Owner;
	this->Owner = Owner;
}
*/


SHUDVitalityPanel::SHUDVitalityPanel(SWidget* Owner, FName Name)
{
	
	//this->Owner = Owner;
}

/*
SHUDVitalityPanel::SHUDVitalityPanel() : FChildren(this)
{
}
*/

SHUDVitalityPanel::SHUDVitalityPanel()
{
	//ChildrenSlots = {this};
}

void SHUDVitalityPanel::Construct(const FArguments& inArgs)
{
	//LayoutGroup = SNew(SVerticalBox);
	/*
	SHorizontalBox::FSlot* Slot1HZ;
	SHorizontalBox::FSlot* Slot2HZ;
	LayoutGroup->AddSlot().Expose(Slot1HZ);
	LayoutGroup->AddSlot().Expose(Slot2HZ);
	*/
	//SBoxPanel::FScopedWidgetSlotArguments Slot1HZ = LayoutGroup->AddSlot();
	//SBoxPanel::FScopedWidgetSlotArguments Slot2HZ = LayoutGroup->AddSlot();
	FSlot* Slot1HZBase;
	FSlot* Slot2HZBase;

	AddSlot().Expose(Slot1HZBase);
	AddSlot().Expose(Slot2HZBase);
	
	Slot1HZBase->SetVerticalAlignment(VAlign_Top);
	Slot2HZBase->SetVerticalAlignment(VAlign_Bottom);

	//ChildrenSlots.AddSlot(Slot1HZ.StealSlot());
	//SlotsContainer.Add(MakeShareable(Slot1HZ));
	//SlotsContainer.Add(MakeShareable(Slot2HZ));
	//Children.AddSlot(Slot1HZBase);
	
	StaminaStat = SNew(SHUDVitalityStat).VitalityStatDataArg(MakeShareable( inArgs._VitalityDataArg.Get()->GetStaminaData()));
	StaminaStat->SetVisibility(EVisibility::Visible);
	HealthStat = SNew(SHUDVitalityStat).VitalityStatDataArg(MakeShareable(inArgs._VitalityDataArg.Get()->GetHealthData()));
	HealthStat->SetVisibility(EVisibility::Visible);

	Slot1HZBase->AttachWidget(StaminaStat.ToSharedRef());
	Slot2HZBase->AttachWidget(HealthStat.ToSharedRef());
}

//Region below is FChildren derived abstract methods

/*
int32 SHUDVitalityPanel::Num() const
{
	return 1;
}

TSharedRef<const SWidget> SHUDVitalityPanel::GetChildAt(int32 Index) const
{
	return LayoutGroup.ToSharedRef();
}

TSharedRef<SWidget> SHUDVitalityPanel::GetChildAt(int32 Index)
{
	return LayoutGroup.ToSharedRef();
}

const FSlotBase& SHUDVitalityPanel::GetSlotAt(int32 ChildIndex) const
{
	return SlotsContainer[ChildIndex].ToSharedRef().Get();
}

FChildren::FConstWidgetRef SHUDVitalityPanel::GetChildRefAt(int32 Index) const
{
	return FConstWidgetRef(ECopyConstruct::CopyConstruct, LayoutGroup.ToSharedRef());
}

FChildren::FWidgetRef SHUDVitalityPanel::GetChildRefAt(int32 Index)
{
	return FWidgetRef(ECopyConstruct::CopyConstruct, LayoutGroup.ToSharedRef());
}
*/

//Region above is FChildren derived abstract methods
