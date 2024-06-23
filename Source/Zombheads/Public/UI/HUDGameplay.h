// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Callbacks/AssetLoaderObserver.h"
#include "Data/AssetLoader.h"
#include "Player/Inventory/IPlayerInventory.h"
#include "ComponentUtility.h"
#include "Player/PlayerCharacterWrapper.h"
#include "Widgets/UIMainMenu.h"
#include "Widgets/UIManager.h"
#include "HUDGameplay.generated.h"

/**
 * 
 */
class SGameplayHUD;

UCLASS()
class ZOMBHEADS_API AHUDGameplay : public AHUD , public IAssetLoaderObserver
{
	GENERATED_BODY()

protected:
	void InitializeVitalityHUD();
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	void DestroyWidgets();
	//virtual ~AHUDGameplay() override {  }
	
private:
	TOptional<FDelegateHandle> HUDDataDelegate;
	TWeakObjectPtr<UAssetLoader> AssetLoader;
	TSharedPtr<SWidget> TestContainer;
	TSharedPtr<SGameplayHUD> HUDRoot;
	TSharedPtr<IPlayerInventory> PlayerInventory;
	TWeakObjectPtr<UUIManager> UIManagerInstance;

	UPROPERTY(EditDefaultsOnly , Category = "Textures" , meta = (AllowPrivateAccess = "true"))
	UTexture2D* IconTexture;
	
	UPROPERTY(EditDefaultsOnly , Category = "HUD" , meta = (AllowPrivateAccess = "true"))
	UUserWidget* PlayerHUD;

	UPROPERTY(EditDefaultsOnly, Category = "UI" , meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUIManager> UIManager;

	TSharedPtr<FSlateBrush> IconBrush;

	TSoftObjectPtr<UPDA_HUD> HUDData;

public:
	virtual void PrimaryDataAssetLoaded(UPDA_HUD* Data) override;
	const FHUDVitalityData& GetFHUDVitalityData();
	const FHUDWeaponsData& GetFHUDWeaponsData();
	TSharedPtr<const FSlateBrush> GetBackgroundWaveBrush();
	
};