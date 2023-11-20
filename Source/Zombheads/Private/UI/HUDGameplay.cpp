// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "UI/HUDGameplay.h"

#include "UI/Slate/SGameplayHUD.h"

void AHUDGameplay::BeginPlay()
{
	Super::BeginPlay();
	
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

		TSharedPtr<SGameplayHUD> TestHud = SNew(SGameplayHUD).OwningHUDArg(MakeShareable(this));
		TestHud->SetVisibility(EVisibility::Visible);

		//TSharedPtr<SWidget> TestWidget = SNew(SCompoundWidget);
		
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(TestContainer, SWeakWidget).PossiblyNullContent(TestHud));
		
	}
}
