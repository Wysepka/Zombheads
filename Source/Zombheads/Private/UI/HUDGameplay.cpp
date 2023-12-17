// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#include "UI/HUDGameplay.h"
#include "UI/Slate/SGameplayHUD.h"

void AHUDGameplay::BeginPlay()
{
	Super::BeginPlay();

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
}

void AHUDGameplay::BeginDestroy()
{
	Super::BeginDestroy();
	if(HUDDataDelegate.IsValid())
	{
		if(AssetLoader.IsValid())
		{
			AssetLoader.Get()->UnRegisterCallback<UPDA_HUD>(&HUDDataDelegate);
		}
	}
}

void AHUDGameplay::PrimaryDataAssetLoaded(UPDA_HUD* Data)
{
	HUDData = TSoftObjectPtr<UPDA_HUD>(Data);
	InitializeVitalityHUD();
}

FHUDVitalityData* AHUDGameplay::GetFHUDVitalityData()
{
	return HUDData.Get()->GetVitalityData();
}

void AHUDGameplay::InitializeVitalityHUD()
{
	//StatTest = SNew(SHUDVitalityStat).
	IconBrush = MakeShareable(new FSlateBrush( UWidgetBlueprintLibrary::MakeBrushFromTexture(IconTexture , 0 , 0)));
	//IconBrush = MakeShareable()
	//IconBrush = MakeShareable(new FSlateImageBrush("" , FVector2d(30 , 30)));

	if(GEngine && GEngine->GameViewport && IconBrush != nullptr && IconBrush.IsValid())
	{
		FSlateImageBrush IconImgBrush = FSlateImageBrush("Icon" , FVector2d());
		IconImgBrush.DrawAs = IconBrush->DrawAs;
		IconImgBrush.TintColor = IconBrush->TintColor;
		IconImgBrush.Margin = IconBrush->Margin;
		IconImgBrush.Tiling = IconBrush->Tiling;
		IconImgBrush.Mirroring = IconBrush->Mirroring;
		IconImgBrush.ImageSize = IconBrush->ImageSize;
		
		//StatTest = SNew(SHUDVitalityStat).IconBrushArg(MakeShareable(&IconImgBrush));

		HUDRoot = SNew(SGameplayHUD).OwningHUDArg(MakeShareable(this));
		HUDRoot->SetVisibility(EVisibility::Visible);

		//TSharedPtr<SWidget> TestWidget = SNew(SCompoundWidget);

		SAssignNew(TestContainer, SWeakWidget).PossiblyNullContent(HUDRoot);
		GEngine->GameViewport->AddViewportWidgetContent(TestContainer.ToSharedRef());
		//GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(TestContainer , SWeakWidget).PossiblyNullContent(TestHud));
		//GEngine->GameViewport->AddViewportWidgetContent(TestContainer).PossiblyNullContent(TestHud));
		
	}
}
