// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "SlateCore.h"
#include "SlateExtras.h"
#include "SHUDVitalityStat.h"
#include "UI/HUDGameplay.h"

/**
 * 
 */
class  SHUDVitalityPanel : public SVerticalBox /* , public FChildren */
{
	//SLATE_DECLARE_WIDGET(SHUDVitalityPanel, SPanel)
	SLATE_BEGIN_ARGS(SHUDVitalityPanel) {}
	
	//SLATE_ARGUMENT(TSharedPtr<SHUDVitalityStat>, StaminaStatArg);
	//SLATE_ARGUMENT(TSharedPtr<SHUDVitalityStat>, HealthStatArg);
	SLATE_ARGUMENT(TSharedPtr<AHUDGameplay>, OwningHUDArg);

	SLATE_END_ARGS()

	//virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;
	//virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;
	//virtual bool SupportsKeyboardFocus() const override;
	//virtual FChildren* GetChildren() override;
	
	SHUDVitalityPanel(SWidget* Owner, FName Name);
	SHUDVitalityPanel();
    void Construct(const FArguments& inArgs);

	//virtual int32 Num() const override;
	//virtual TSharedRef<const SWidget> GetChildAt(int32 Index) const override;
	//virtual TSharedRef<SWidget> GetChildAt(int32 Index) override;
	//virtual const FSlotBase& GetSlotAt(int32 ChildIndex) const override;
	//virtual FConstWidgetRef GetChildRefAt(int32 Index) const override;
	//virtual FWidgetRef GetChildRefAt(int32 Index) override;
	
	TSharedPtr<SHUDVitalityStat> StaminaStat;
	TSharedPtr<SHUDVitalityStat> HealthStat;
	TSharedPtr<SVerticalBox> LayoutGroup;

	TArray<TSharedPtr<FSlotBase>> SlotsContainer;
	TSharedPtr<AHUDGameplay> OwningHUD;
public:
	void SetGameplayHUD(TSharedPtr<AHUDGameplay> HUDGameplay);

	//TPanelChildren<SVerticalBox::FSlot> ChildrenSlots;
};
