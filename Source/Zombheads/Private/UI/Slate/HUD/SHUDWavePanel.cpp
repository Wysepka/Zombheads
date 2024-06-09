// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "UI/Slate/HUD/SHUDWavePanel.h"

#include "ImageUtils.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Brushes/SlateImageBrush.h"

SHUDWavePanel::SHUDWavePanel()
{
}

SHUDWavePanel::~SHUDWavePanel()
{
}

void SHUDWavePanel::Construct(const FArguments& inArgs)
{
	SetCanTick(true);
	
	EnemySpawnerInfoPtr = inArgs._EnemySpawnerInfoArg;
	BrushBackgroundNew = inArgs._BackgroundWaveBrushArg;
	
	FOverlaySlot* Overlay1Slot;
	FOverlaySlot* Overlay2Slot;
	AddSlot().Expose(Overlay1Slot);
	AddSlot().Expose(Overlay2Slot);

	FSlateFontInfo FontInfo = FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 32);
	
	SAssignNew(HorizontalLayout , SHorizontalBox);

	SHorizontalBox::FSlot* Layout1SlotTemp;
	SHorizontalBox::FSlot* Layout2SlotTemp;
	
	
	HorizontalLayout->AddSlot().Expose(Layout1SlotTemp);
	HorizontalLayout->AddSlot().Expose(Layout2SlotTemp);

	//Layout1Slot = MakeShareable(Layout1SlotTemp);
	//Layout1Slot = MakeShareable(Layout2SlotTemp);

	Layout1SlotTemp->SetAutoWidth();
	Layout2SlotTemp->SetAutoWidth();

	const FSlateBrush* PinBrush = BrushBackgroundNew.Get();
	
	SAssignNew(ContainerBackgroundImg , SImage)
	//.Image(&BrushBackgroundNew)
	.DesiredSizeOverride(FVector2d(150 , 150))
	;//.ColorAndOpacity(BackgroundColor);
	ContainerBackgroundImg->SetImage(PinBrush);
	
	SAssignNew(WaveLocTextBlock , STextBlock)
	.Visibility(EVisibility::Visible)
	.ColorAndOpacity(FSlateColor(FLinearColor::Black))
	.ShadowColorAndOpacity(FLinearColor::Gray)
	.ShadowOffset(FIntPoint(-1, 1))
	.Font(FontInfo)
	.Text(FText::FromString("Wave:"));

	SAssignNew(WaveNumTextBlock , STextBlock)
	.Visibility(EVisibility::Visible)
	.ColorAndOpacity(FSlateColor(FLinearColor::Black))
	.ShadowColorAndOpacity(FLinearColor::Gray)
	.ShadowOffset(FIntPoint(-1, 1))
	.Font(FontInfo)
	.Text(FText::FromString("0"));

	Layout1SlotTemp->AttachWidget(WaveLocTextBlock.ToSharedRef());
	Layout2SlotTemp->AttachWidget(WaveNumTextBlock.ToSharedRef());

	Overlay1Slot->AttachWidget(ContainerBackgroundImg.ToSharedRef());
	Overlay2Slot->AttachWidget(HorizontalLayout.ToSharedRef());
	
	Overlay2Slot->VAlign(VAlign_Fill);
	Overlay2Slot->HAlign(HAlign_Fill);
}

void SHUDWavePanel::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if(HorizontalLayout.IsValid() && ContainerBackgroundImg.IsValid())
	{
		ContainerBackgroundImg->SetDesiredSizeOverride(HorizontalLayout->GetDesiredSize());
	}
}
