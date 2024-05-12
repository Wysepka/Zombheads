// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "UI/Slate/HUD/SHUDVitalityStat.h"

#include "Chaos/ChaosPerfTest.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION


SHUDVitalityStat::SHUDVitalityStat(SWidget* Owner, FName Name)
{
}

SHUDVitalityStat::SHUDVitalityStat()
{
}

void SHUDVitalityStat::Construct(const FArguments& inArgs)
{
	this->SetCanTick(true);
	
	StatData = inArgs._VitalityStatDataArg;
	StatPercentageFunction = inArgs._StatPercentageFunctionArg;
	
	FScopedWidgetSlotArguments Slot2Arg = AddSlot();
	Slot2Arg.MaxWidth(300.f);

	TSharedRef<SBox> OverlayBox = SNew(SBox);
	OverlayBox->SetWidthOverride(300.f);
	
	TSharedRef<SOverlay> BackgroundOverlay = SNew(SOverlay);
	{
		SOverlay::FOverlaySlot* Slot1OverlayBase;
		BackgroundOverlay.Get().AddSlot().Expose(Slot1OverlayBase);
		
		BackgroundImg = SNew(SImage);
		//BackgroundImg.Get()->SetImage(StatData.GetBackgroundTextureBrush().Get());

		//Slot1OverlayBase->AttachWidget(BackgroundImg.ToSharedRef());
		
		SOverlay::FOverlaySlot* Slot2OverlayBase;
		BackgroundOverlay.Get().AddSlot().Expose(Slot2OverlayBase);

		auto BackgroundBrush = StatData.GetBackgroundTextureBrush();
		BackgroundBrush.Get()->TintColor = StatData.GetBackgroundTintColor();
		
		auto FillImgBrush = StatData.GetFillerTextureBrush();
		FillImgBrush.Get()->TintColor = StatData.GetFillerTintColor();

		FillerImg = SNew(SProgressBar);
		FillerImg.Get()->SetBackgroundImage(BackgroundBrush.Get());
		FillerImg.Get()->SetFillImage(FillImgBrush.Get());
		FillerImg.Get()->SetBarFillStyle(EProgressBarFillStyle::Mask);
		FillerImg.Get()->SetBarFillType(EProgressBarFillType::LeftToRight);

		FillerImg.Get()->SetPercent(1.f);

		Slot2OverlayBase->AttachWidget(FillerImg.ToSharedRef());
	}
	OverlayBox.Get().SetContent(BackgroundOverlay);
	
	Slot2Arg.AttachWidget(OverlayBox);
	
	FScopedWidgetSlotArguments Slot1Arg = AddSlot();
	TSharedRef<SBox> OverlayIconBox = SNew(SBox);
	OverlayIconBox->SetWidthOverride(100.f);

	TSharedRef<SOverlay> OverlayIcon = SNew(SOverlay);
	SOverlay::FOverlaySlot* Slot1OverlayIconBase;
	OverlayIcon.Get().AddSlot().Expose(Slot1OverlayIconBase);
	
	IconImg = SNew(SImage);
	IconImg.Get()->SetImage(StatData.GetIconTextureBrush().Get());

	Slot1OverlayIconBase->AttachWidget(IconImg.ToSharedRef());
	OverlayIconBox->SetContent(OverlayIcon);

	Slot1Arg.AttachWidget(OverlayIconBox);

	Slot1Arg.HAlign(HAlign_Right);

	Slot2Arg.HAlign(HAlign_Right);
}

void SHUDVitalityStat::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SHorizontalBox::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	//return;
	const float currPercentage = StatPercentageFunction();
	FillerImg.Get()->SetPercent(currPercentage);
	IconImg.Get()->SetImage(StatData.GetIconTextureBrush().Get());
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
