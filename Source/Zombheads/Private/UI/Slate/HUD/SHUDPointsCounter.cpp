// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "UI/Slate/HUD/SHUDPointsCounter.h"

#include <string>

SHUDPointsCounter::SHUDPointsCounter()
{
}

SHUDPointsCounter::~SHUDPointsCounter()
{
}

void SHUDPointsCounter::Construct(const FArguments& inArgs)
{
	SetCanTick(true);

	auto OnPointsChangedDlgt = inArgs._StateStatInfoArg.Get()->GetOnPointsChangedDelegate(); 
	OnEnemyDiedHandle = OnPointsChangedDlgt->AddRaw(this, &SHUDPointsCounter::OnPointsChanged_Receiver);
	
	BrushBackground = inArgs._BackgroundPointsBrushArg;
	const FSlateBrush* PinBrush = BrushBackground.Get();

	FOverlaySlot* Overlay1Slot;
	FOverlaySlot* Overlay2Slot;
	AddSlot().Expose(Overlay1Slot);
	AddSlot().Expose(Overlay2Slot);
	
	FSlateFontInfo FontInfo = FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 52);

	SAssignNew(HorizontalLayout , SHorizontalBox);
	
	SHorizontalBox::FSlot* Layout1SlotTemp;
	
	HorizontalLayout->AddSlot().Expose(Layout1SlotTemp);

	Layout1SlotTemp->SetAutoWidth();

	SAssignNew(ContainerBackgroundImg , SImage)
	.DesiredSizeOverride(FVector2d(150 , 150));

	ContainerBackgroundImg->SetImage(PinBrush);

	SAssignNew(PointsNumTextBlock , STextBlock)
	.Visibility(EVisibility::Visible)
	.ColorAndOpacity(FSlateColor(FLinearColor::Black))
	.ShadowColorAndOpacity(FLinearColor::Gray)
	.ShadowOffset(FIntPoint(-1, 1))
	.Font(FontInfo)
	.Text(FText::FromString(FString("Test")));

	Layout1SlotTemp->AttachWidget(PointsNumTextBlock.ToSharedRef());

	Overlay1Slot->AttachWidget(ContainerBackgroundImg.ToSharedRef());
	Overlay2Slot->AttachWidget(HorizontalLayout.ToSharedRef());
	
	Overlay2Slot->VAlign(VAlign_Fill);
	Overlay2Slot->HAlign(HAlign_Fill);
}

void SHUDPointsCounter::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if(HorizontalLayout.IsValid() && ContainerBackgroundImg.IsValid())
	{
		ContainerBackgroundImg->SetDesiredSizeOverride(HorizontalLayout->GetDesiredSize());
	}
}

void SHUDPointsCounter::OnPointsChanged_Receiver(int64 CurrentPoints)
{
	if(PointsNumTextBlock.IsValid())
	{
		PointsNumTextBlock->SetText(FText::AsNumber(CurrentPoints));
	}
}
