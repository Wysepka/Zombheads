// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombheadsGameModeBase.h"

void AZombheadsGameModeBase::BeginPlay() {
	Super::BeginPlay();

	FString CurrentLevelName = GetWorld()->GetMapName();
	CurrentLevelName = CurrentLevelName.Replace(TEXT("/Game/"), TEXT(""));
	if(CurrentLevelName.Contains("MainMenu"))
	{
		return;
	}
	// Failsafe PlayerControllerClass = AYourPlayerController::StaticClass();   
	// Blueprinted Version, relies on the asset path obtained from the editor 
	//static ConstructorHelpers::FClassFinder<APlayerCharacterWrapper> VictoryPCOb(TEXT("APlayerCharacterWrapper'/Game/BPs/PlayerCharacterController_BP.PlayerCharacterController_BP_C'")); 
	//if (VictoryPCOb.Class != NULL) { PlayerControllerClass = VictoryPCOb.Class; }
}

AZombheadsGameModeBase::AZombheadsGameModeBase() {
	static ConstructorHelpers::FClassFinder<APlayerCharacterWrapper> VictoryPCOb(TEXT("APlayerCharacterWrapper'/Game/BPs/PlayerCharacterController_BP.PlayerCharacterController_BP_C'"));
	if (VictoryPCOb.Class != NULL) {
		PlayerControllerClass = VictoryPCOb.Class;
	}
}
}

void AZombheadsGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	LogClearerPtr.Get()->OnEndPlay();
	LogClearerPtr.Reset();
}

void AZombheadsGameModeBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnEndOfRound = MakeShareable(new FOnEndOfRound);
}

void AZombheadsGameModeBase::OnPlayerDied(EActorType ActorType)
{
	if(ActorType == EActorType::Player)
	{
		if(OnEndOfRound.IsValid() && OnEndOfRound->IsBound())
		{
			OnEndOfRound->Broadcast();
		}
	}
}

TSharedPtr<StateStatInfo> AZombheadsGameModeBase::GetStateStatInfo()
{
	return StateStatInfoPtr;
}

TSharedPtr<FOnEndOfRound> AZombheadsGameModeBase::GetEndOfRound()
{
	return OnEndOfRound;
}
