// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombheadsGameModeBase.h"

#include "ComponentUtility.h"
#include "Actors/Spawner/IEnemySpawnerInfo.h"

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

	LogClearerPtr = MakeUnique<LogClearer>();

	//Initialize all of Systems here
	if(OnAllSystemsInitialized.IsBound())
	{
		OnAllSystemsInitialized.Broadcast();
	}

	TWeakInterfacePtr<IIEnemySpawnerInfo> EnemySpawnerInfo = ComponentUtility::FindActorWithInterface<IIEnemySpawnerInfo , UIEnemySpawnerInfo>(GetWorld());
	StateStatInfoPtr = MakeShareable(new StateStatInfo(EnemySpawnerInfo));

	auto PlayerPawn = ComponentUtility::FindActorOfType<APlayerPawn>(GetWorld());
	if(PlayerPawn.IsValid())
	{
		PlayerPawn->GetVitalityComponentInstance()->GetOnActorDied()->AddUObject(this, &AZombheadsGameModeBase::OnPlayerDied);
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

TSharedPtr<StateStatInfo> AZombheadsGameModeBase::GetStateStatInfo()
{
	return StateStatInfoPtr;
}

TSharedPtr<FOnEndOfRound> AZombheadsGameModeBase::GetEndOfRound()
{
	return OnEndOfRound;
}
