// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#include "UI/HUDGameplay.h"

#include "Player/PlayerCharacterWrapper.h"
#include "UI/Slate/HUD/SGameplayHUD.h"

void AHUDGameplay::BeginPlay()
{
	Super::BeginPlay();
	//return;

	auto argName = GetClass()->GetFName();
	if(argName.IsValid())
	{
		auto c = "c";
	}
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
	
	if(!this)
	{
		return;
	}
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
		if(HUDRoot.IsValid())
		{
			GEngine->GameViewport->RemoveViewportWidgetContent(HUDRoot.ToSharedRef());
		}
		if(TestContainer.IsValid())
		{
			GEngine->GameViewport->RemoveViewportWidgetContent(TestContainer.ToSharedRef());
		}
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

const FHUDWeaponsData& AHUDGameplay::GetFHUDWeaponsData()
{
	return HUDData->GetWeaponsData();
}

void AHUDGameplay::InitializeVitalityHUD()
{
	//IconBrush = MakeShareable(new FSlateBrush( UWidgetBlueprintLibrary::MakeBrushFromTexture(IconTexture , 0 , 0)));
	//return;
	if(GEngine && GEngine->GameViewport)
	{
		AActor* PlayerPawnActor = UGameplayStatics::GetActorOfClass(GetWorld() , APlayerPawn::StaticClass());
		if(PlayerPawnActor == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , TEXT("Could not find PlayerPawn actor, VitalityStat HUD is not initialized"));
			UE_LOG(LogTemp, Log, TEXT("Could not find PlayerPawn actor, VitalityStat HUD is not initialized"));
			return;
		}
		APlayerPawn* PlayerPawn = Cast<APlayerPawn>(PlayerPawnActor);
		//const auto VitalityComp = PlayerPawn->GetVitalityComponent();
		const auto VitalityComp = PlayerPawn->GetVitalityComponent();

		if(!VitalityComp.IsValid() || VitalityComp == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , TEXT("Could not find VitalityComponent, VitalityStat HUD is not initialized"));
			UE_LOG(LogTemp, Log, TEXT("Could not find VitalityComponent, VitalityStat HUD is not initialized"));
			return;
		}

		TWeakObjectPtr<AActor> CharWrapperActor = TWeakObjectPtr<AActor>(UGameplayStatics::GetActorOfClass(GetWorld() , APlayerCharacterWrapper::StaticClass()));
		TWeakObjectPtr<APlayerCharacterWrapper> CharWrapper = Cast<APlayerCharacterWrapper>(CharWrapperActor);

		if(!CharWrapper.IsValid())
		{
			GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , TEXT("Could not find PlayerCharacterWrapper, WeaponsHUD is not initialized"));
			UE_LOG(LogTemp, Log, TEXT("Could not find PlayerCharacterWrappers, Players HUD is not initialized"));
			return;
		}
		
		HUDRoot = SNew(SGameplayHUD).OwningHUDArg(TWeakObjectPtr<AHUDGameplay>(this)).VitalityComponentArg(VitalityComp).PlayerInventoryArg(CharWrapper->GetPlayerInventoryInterface());
		HUDRoot->SetVisibility(EVisibility::Visible);

		SAssignNew(TestContainer, SWeakWidget).PossiblyNullContent(HUDRoot);
		GEngine->GameViewport->AddViewportWidgetContent(TestContainer.ToSharedRef());
	}
}
