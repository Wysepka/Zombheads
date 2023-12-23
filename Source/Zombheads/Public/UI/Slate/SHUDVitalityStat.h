// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "SlateCore.h"
#include "SlateExtras.h"
#include "SlateBasics.h"
#include "Data/Containers/Vitality/FHUDVitalityData.h"

/**
 * 
 */
class SHUDVitalityStat : public SHorizontalBox /* , public FChildren */
{
	//SLATE_DECLARE_WIDGET(SHUDVitalityStat, SPanel)
	SLATE_BEGIN_ARGS(SHUDVitalityStat){}

	SLATE_ARGUMENT(TSharedPtr<SImage>, IconImageArg);
	SLATE_ARGUMENT(TSharedPtr<FSlateImageBrush>, IconBrushArg);
	SLATE_ARGUMENT(TSharedPtr<FSlateImageBrush>, BackgroundBrushArg);
	SLATE_ARGUMENT(TSharedPtr<FSlateImageBrush>, FillerBrushArg);
	SLATE_ARGUMENT(FString, IconImgDirArg);
	SLATE_ARGUMENT(FHUDVitalityStatData, VitalityStatDataArg);
	
	SLATE_END_ARGS()

	SHUDVitalityStat(SWidget* Owner , FName Name);
	SHUDVitalityStat();

    void Construct(const FArguments& inArgs);

	/*
	virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;
	virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;
	virtual bool SupportsKeyboardFocus() const override;
	virtual FChildren* GetChildren() override;
	*/

	/*
	virtual int32 Num() const override;
	virtual TSharedRef<const SWidget> GetChildAt(int32 Index) const override;
	virtual TSharedRef<SWidget> GetChildAt(int32 Index) override;
	virtual const FSlotBase& GetSlotAt(int32 ChildIndex) const override;
	virtual FConstWidgetRef GetChildRefAt(int32 Index) const override;
	virtual FWidgetRef GetChildRefAt(int32 Index) override;
	*/
	
	TSharedPtr<FSlateBrush> IconBrush;
	TSharedPtr<FSlateBrush> BackgroundBrush;
	TSharedPtr<FSlateBrush> FillerBrush;

	FHUDVitalityStatData StatData;
	
	TSharedPtr<SImage> IconImg;
	TSharedPtr<SImage> BackgroundImg;
	TSharedPtr<SImage> FillerImg;
	
	TArray<TSharedPtr<FSlotBase>> SlotContainer;
	TSharedPtr<FSlotBase> Slot1;
	TSharedPtr<FSlotBase> Slot2;
	
	//TSharedPtr<SVerticalBox> LayoutGroup;
	
	TSharedPtr<FChildren> Children;
	TSharedPtr<SImage> IconImage;
	FString IconImgDir;

public:
	//TPanelChildren<SVerticalBox::FSlot> ChildrenSlots;
};
