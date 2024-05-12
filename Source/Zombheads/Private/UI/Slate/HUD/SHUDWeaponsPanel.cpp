// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "UI/Slate/HUD/SHUDWeaponsPanel.h"

#include "Commandlets/GatherTextCommandlet.h"
#include "Player/Inventory/Weapons/WeaponFirearm.h"

SHUDWeaponsPanel::SHUDWeaponsPanel()
{
}

SHUDWeaponsPanel::~SHUDWeaponsPanel()
{
	if(PlayerInventoryPtr.IsValid())
	{
		if(WeaponChangedHandle.IsValid())
		{
			PlayerInventoryPtr.Get()->GetWeaponChangedDelegate()->Remove(WeaponChangedHandle);
		}
		if(InventoryItemUsedHandle.IsValid())
		{
			PlayerInventoryPtr.Get()->GetInventoryItemUsedDelegate()->Remove(InventoryItemUsedHandle);
		}
	}
}

void SHUDWeaponsPanel::Construct(const FArguments& inArgs)
{
	SetCanTick(true);
	PlayerInventoryPtr = inArgs._PlayerInventoryArg;
	WeaponsDataPtr = inArgs._WeaponsDataArg;
	VitalityData = inArgs._VitalityDataArg;

	WeaponEntries = WeaponsDataPtr.GetWeaponEntries();

	WeaponChangedHandle =  PlayerInventoryPtr.Get()->GetWeaponChangedDelegate()->AddRaw(this, &SHUDWeaponsPanel::OnPlayerWeaponChanged);
	InventoryItemUsedHandle = PlayerInventoryPtr.Get()->GetInventoryItemUsedDelegate()->AddRaw(this, &SHUDWeaponsPanel::OnInventoryItemUsed);
	
	
	WeaponIconContainer = SNew(SBox);
	WeaponIconImgPtr = SNew(SImage);

	
	//WeaponIconImgPtr
	SAssignNew(WeaponIconContainer , SBox)
	.WidthOverride(200.f)
	.HeightOverride(200.f)
	[
		SAssignNew(WeaponIconImgPtr , SImage)
	];
	
	FSlot* Slot1HZBase;
	FSlot* Slot2HZBase;

	AddSlot().Expose(Slot1HZBase);
	AddSlot().Expose(Slot2HZBase);

	Slot1HZBase->AttachWidget(WeaponIconContainer.ToSharedRef());

	FSlateFontInfo FontInfo = FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 32);
	
	SAssignNew(WeaponAmmoContainer , SBox)
	.HeightOverride(200.f)
	.WidthOverride(200.f)
	.HAlign(HAlign_Center)
	.VAlign(VAlign_Center)
	[
		SAssignNew(WeaponAmmoText , STextBlock)
		.Visibility(EVisibility::Visible)
		.ColorAndOpacity(FSlateColor(FLinearColor::White))
		.ShadowColorAndOpacity(FLinearColor::Black)
		.ShadowOffset(FIntPoint(-1, 1))
		.Font(FontInfo)
	];
	
	Slot2HZBase->AttachWidget(WeaponAmmoContainer.ToSharedRef());
}

void SHUDWeaponsPanel::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if(!CurrentWeaponUsed.IsValid())
	{
		return;
	}
	FString FormattedText;
	
	if(CurrentWeaponUsed.Get()->GetUsableType() == EItemType::Firearm)
	{
		FormattedText = FString::Printf(TEXT("%d/%d") , CurrentWeaponUsed->GetCurrentAmmo() , CurrentWeaponUsed->GetMaxAmmmo());
	}
	else
	{
		FormattedText = FString(TEXT("Infinity"));
	}

	FText ToWrite = FText::FromString(FormattedText);
	WeaponAmmoText.Get()->SetText(ToWrite);
}

void SHUDWeaponsPanel::OnPlayerWeaponChanged(TWeakObjectPtr<UObject> WeaponInstance)
{
	
	TSharedPtr<FSlateBrush> IconBrush;

	CurrentWeaponUsed = Cast<AWeaponBase>(WeaponInstance.Get());
	if(CurrentWeaponUsed.IsValid())
	{
		for (int i = 0; i < WeaponEntries.Num(); i++)
		{
			if(WeaponEntries[i].GetWeaponID() == CurrentWeaponUsed.Get()->GetWeaponID())
			{
				IconBrush = WeaponEntries[i].GetIconTextureBrush();
			}
		}
	}
	
	if(CurrentWeaponUsed.IsValid() && IconBrush.IsValid())
	{
		WeaponIconImgPtr->SetImage(IconBrush.Get());
	}
	else
	{
		WeaponIconImgPtr->SetImage(nullptr);
	}
}

void SHUDWeaponsPanel::OnInventoryItemUsed(const IUsable& Usable)
{
	
}
