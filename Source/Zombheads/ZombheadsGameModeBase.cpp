// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombheadsGameModeBase.h"

void AZombheadsGameModeBase::BeginPlay() {
	Super::BeginPlay();

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