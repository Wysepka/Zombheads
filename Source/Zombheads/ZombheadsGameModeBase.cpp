// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombheadsGameModeBase.h"

#include "ComponentUtility.h"
#include "Actors/Spawner/IEnemySpawnerInfo.h"

void AZombheadsGameModeBase::BeginPlay() {
	Super::BeginPlay();

	// Failsafe PlayerControllerClass = AYourPlayerController::StaticClass();   
	// Blueprinted Version, relies on the asset path obtained from the editor 
	//static ConstructorHelpers::FClassFinder<APlayerCharacterWrapper> VictoryPCOb(TEXT("APlayerCharacterWrapper'/Game/BPs/PlayerCharacterController_BP.PlayerCharacterController_BP_C'")); 
	//if (VictoryPCOb.Class != NULL) { PlayerControllerClass = VictoryPCOb.Class; }

	LogClearerPtr = MakeUnique<LogClearer>();

	//Initialize all of Systems here
	if(OnAllSystemsInitialized.IsBound())
	{
		OnAllSystemsInitialized.Broadcast();
	}

	TWeakInterfacePtr<IIEnemySpawnerInfo> EnemySpawnerInfo = ComponentUtility::FindActorWithInterface<IIEnemySpawnerInfo , UIEnemySpawnerInfo>(GetWorld());
	StateStatInfoPtr = MakeShareable(new StateStatInfo(EnemySpawnerInfo));

	TWeakObjectPtr<APlayerPawn> PlayerPawnPtr = ComponentUtility::FindActorOfType<APlayerPawn>(GetWorld());
	if(PlayerPawnPtr.IsValid())
	{
		TWeakObjectPtr<UActorVitalityComponent> VitalityComponent = ComponentUtility::FindComponentOfType<UActorVitalityComponent>(PlayerPawnPtr.Get());
		if(VitalityComponent.IsValid())
		{
			VitalityComponent->GetOnActorDiedDelegate()->AddUObject(this, &AZombheadsGameModeBase::OnPlayerDied);
		}
		else
		{
			LOG_EMPTY_ARRAY("Could not Find VitalityComponent EndGameCheck not working for 0 player hp")
		}
	}
	else
	{
		LOG_EMPTY_ARRAY("Could not find PlayerPawn EndGameCheck not working for 0 player HP")
	}
}

void AZombheadsGameModeBase::BeginDestroy()
{
	//StateStatInfoPtr->Dispose();
	if(StateStatInfoPtr.IsValid())
	{
		StateStatInfoPtr->Dispose();
		StateStatInfoPtr.Reset();
	}
	//StateStatInfoPtr = nullptr;
	Super::BeginDestroy();
}

AZombheadsGameModeBase::AZombheadsGameModeBase() {
	static ConstructorHelpers::FClassFinder<APlayerCharacterWrapper> VictoryPCOb(TEXT("APlayerCharacterWrapper'/Game/BPs/PlayerCharacterController_BP.PlayerCharacterController_BP_C'"));
	if (VictoryPCOb.Class != NULL) {
		PlayerControllerClass = VictoryPCOb.Class;
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

	/*
	TArray<AActor*> EnemySpawnerActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld() , UIEnemySpawnerInfo::StaticClass(), EnemySpawnerActors);

	if(EnemySpawnerActors.Num() <= 0)
	{
		LOG_EMPTY_ARRAY(FString("EnemySpawnerActors are empty ! Try Another interface lookout"))
		return;
	}
		
	TWeakInterfacePtr<IIEnemySpawnerInfo> EnemySpawnerInfo = Cast<IIEnemySpawnerInfo>(EnemySpawnerActors[0]);
	if(!EnemySpawnerInfo.IsValid())
	{
		LOG_INCORRECT_CAST("Incorrect cast From %s to %s" , EnemySpawnerActors[0] , UIEnemySpawnerInfo::StaticClass()->GetName());
		return;
	}
	StateStatInfoPtr = MakeShareable(new StateStatInfo(EnemySpawnerInfo));
	*/
}

void AZombheadsGameModeBase::OnPlayerDied(EActorType ActorType)
{
	if(ActorType == EActorType::Player)
	{
		if(OnEndOfRound->IsBound())
		{
			OnEndOfRound->Broadcast();
		}
	}
}

TSharedPtr<StateStatInfo> AZombheadsGameModeBase::GetStateStatInfo()
{
	return StateStatInfoPtr;
}
