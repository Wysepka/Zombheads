// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#include "UI/HUDGameplay.h"
#include "UI/Slate/SGameplayHUD.h"

void AHUDGameplay::BeginPlay()
{
	Super::BeginPlay();
	//return;

	AActor* AssetLoaderInitializerActor = UGameplayStatics::GetActorOfClass(GetWorld() , AAssetLoaderInitializer::StaticClass());
	AAssetLoaderInitializer* AssetLoaderInitializer = Cast<AAssetLoaderInitializer>(AssetLoaderInitializerActor);
	AssetLoader = AssetLoaderInitializer->GetAssetLoader();

	UPDA_HUD* HUDDataLocal;
	auto arg = AssetLoader.Get()->GetPrimaryDataAsset<UPDA_HUD>(this, HUDDataLocal);
	if(arg.Key)
	{
		HUDData = TSoftObjectPtr<UPDA_HUD>(HUDDataLocal);
		InitializeVitalityHUD();
	}
	else
	{
		HUDDataDelegate = arg.Value;
	}
	//FTimerHandle testDelegate;
	//GetWorld()->GetTimerManager().SetTimer<AHUDGameplay>(testDelegate , this , &AHUDGameplay::DestroyWidgets , 5.f , false , 5.f);
}

void AHUDGameplay::BeginDestroy()
{
	Super::BeginDestroy();
	DestroyWidgets();
	return;
	if(!this)
	{
		return;
	}
	return;
	if(HUDDataDelegate.IsSet())
	{
		if(AssetLoader.IsValid())
		{
			auto const AssetLoaderPin = AssetLoader.Get();
			if(AssetLoaderPin == nullptr || !IsValid(AssetLoaderPin))
			{
				return;
			}
			AssetLoaderPin->UnRegisterCallback<UPDA_HUD>(&HUDDataDelegate.GetValue());
		}
	}
}

void AHUDGameplay::DestroyWidgets()
{
	auto const gengineLocal = GEngine;
	
	if(gengineLocal && gengineLocal->GameViewport)
	{
		//GEngine->GameViewport->AddViewportWidgetContent(TestContainer.ToSharedRef());
		GEngine->GameViewport->RemoveViewportWidgetContent(HUDRoot.ToSharedRef());
		GEngine->GameViewport->RemoveViewportWidgetContent(TestContainer.ToSharedRef());
		
		//GEngine->GameViewport->RemoveAllViewportWidgets();
	}
}


void AHUDGameplay::PrimaryDataAssetLoaded(UPDA_HUD* Data)
{
	HUDData = TSoftObjectPtr<UPDA_HUD>(Data);
	InitializeVitalityHUD();
}

const FHUDVitalityData& AHUDGameplay::GetFHUDVitalityData()
{
	return HUDData->GetVitalityData();
}

void AHUDGameplay::InitializeVitalityHUD()
{
	//IconBrush = MakeShareable(new FSlateBrush( UWidgetBlueprintLibrary::MakeBrushFromTexture(IconTexture , 0 , 0)));
	//return;
	if(GEngine && GEngine->GameViewport)
	{
		HUDRoot = SNew(SGameplayHUD).OwningHUDArg(TWeakObjectPtr<AHUDGameplay>(this));
		HUDRoot->SetVisibility(EVisibility::Visible);

		SAssignNew(TestContainer, SWeakWidget).PossiblyNullContent(HUDRoot);
		GEngine->GameViewport->AddViewportWidgetContent(TestContainer.ToSharedRef());
	}
}
