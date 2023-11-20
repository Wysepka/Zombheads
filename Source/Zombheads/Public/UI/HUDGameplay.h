// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidgetBlueprint.h"
#include "GameFramework/HUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "SlateCore.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "HUDGameplay.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBHEADS_API AHUDGameplay : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
private:

	TSharedPtr<SWidget> TestContainer;

	UPROPERTY(EditDefaultsOnly , Category = "Textures" , meta = (AllowPrivateAccess = "true"))
	UTexture2D* IconTexture;
	
	UPROPERTY(EditDefaultsOnly , Category = "HUD" , meta = (AllowPrivateAccess = "true"))
	UUserWidget* PlayerHUD;

	TSharedPtr<FSlateBrush> IconBrush;
};