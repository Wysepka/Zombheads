// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "UI/Slate/SHUDVitalityStat.h"

#include "Chaos/ChaosPerfTest.h"

/*
void SHUDVitalityStat::OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const
{
}

FVector2D SHUDVitalityStat::ComputeDesiredSize(float LayoutScaleMultiplier) const
{
	//return FVector2d(IconImg.Get().GetDesiredSize().X + FillerImg.Get().GetDesiredSize().X , IconImg.Get().GetDesiredSize().Y);
	return FVector2d(IconImg.Get()->GetDesiredSize().X + FillerImg.Get()->GetDesiredSize().X , IconImg.Get()->GetDesiredSize().Y);
}


bool SHUDVitalityStat::SupportsKeyboardFocus() const
{
	return false;
}

FChildren* SHUDVitalityStat::GetChildren()
{
	return &ChildrenSlots;
}
*/

//Below is region for FChildren derived methods

/*
int32 SHUDVitalityStat::Num() const
{
	return 1;
}

TSharedRef<const SWidget> SHUDVitalityStat::GetChildAt(int32 Index) const
{
	//return LayoutGroup;
	return LayoutGroup.ToSharedRef();
}

TSharedRef<SWidget> SHUDVitalityStat::GetChildAt(int32 Index)
{
	//return LayoutGroup;
	return LayoutGroup.ToSharedRef();
}

const FSlotBase& SHUDVitalityStat::GetSlotAt(int32 ChildIndex) const
{
	return LayoutGroup->GetSlot(ChildIndex);
}

FChildren::FConstWidgetRef SHUDVitalityStat::GetChildRefAt(int32 Index) const
{
	//return FConstWidgetRef(ECopyConstruct::CopyConstruct , LayoutGroup);
	return FConstWidgetRef(ECopyConstruct::CopyConstruct , LayoutGroup.ToSharedRef());
}

FChildren::FWidgetRef SHUDVitalityStat::GetChildRefAt(int32 Index)
{
	//return FWidgetRef(ECopyConstruct::CopyConstruct , LayoutGroup);
	return FWidgetRef(ECopyConstruct::CopyConstruct , LayoutGroup.ToSharedRef());
}
*/

//Above is region for FChildren derived methods

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

/*
SHUDVitalityStat::SHUDVitalityStat(SWidget* Owner, FName Name): FChildren(this)
{
	//Children = MakeShareable(new FChildren(Owner));
	this->Owner = Owner;
}
*/

SHUDVitalityStat::SHUDVitalityStat(SWidget* Owner, FName Name)
{
	//ChildrenSlots = {this};
	//Children = MakeShareable(new FChildren(Owner));
}

/*
SHUDVitalityStat::SHUDVitalityStat() : FChildren(this)
{
}
*/

SHUDVitalityStat::SHUDVitalityStat()
{
	//ChildrenSlots = {this};
}

void SHUDVitalityStat::Construct(const FArguments& inArgs)
{
	IconImgDir = inArgs._IconImgDirArg;
	IconBrush = inArgs._IconBrushArg;

	BackgroundBrush = inArgs._BackgroundBrushArg;
	FillerBrush = inArgs._FillerBrushArg;

	StatData = inArgs._VitalityStatDataArg;
	
	FScopedWidgetSlotArguments Slot1Arg = AddSlot();

	Slot1Arg.HAlign(HAlign_Left);

	IconImg = SNew(SImage);
	IconImg.Get()->SetImage(StatData.GetIconTextureBrush().Get());
	
	Slot1Arg.AttachWidget(IconImg.ToSharedRef());

	FScopedWidgetSlotArguments Slot2Arg = AddSlot();
	Slot2Arg.HAlign(HAlign_Right);

	TSharedRef<SOverlay> BackgroundOverlay = SNew(SOverlay);
	Slot2Arg.AttachWidget(BackgroundOverlay);
	
	SOverlay::FOverlaySlot* Slot1OverlayBase;
	BackgroundOverlay.Get().AddSlot().Expose(Slot1OverlayBase);
	
	BackgroundImg = SNew(SImage);
	BackgroundImg.Get()->SetImage(StatData.GetBackgroundTextureBrush().Get());
	//BackgroundImg.Get()->SetDesiredSizeOverride(FVector2d(30.f , 30.f));

	Slot1OverlayBase->AttachWidget(BackgroundImg.ToSharedRef());

	SOverlay::FOverlaySlot* Slot2OverlayBase;
	BackgroundOverlay.Get().AddSlot().Expose(Slot2OverlayBase);

	FillerImg = SNew(SImage);
	FillerImg.Get()->SetImage(StatData.GetFillerTextureBrush().Get());
	//FillerImg.Get()->SetDesiredSizeOverride(FVector2d(30.f , 30.f));

	Slot2OverlayBase->AttachWidget(FillerImg.ToSharedRef());
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION