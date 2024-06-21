// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Player/PlayerCharacterWrapper.h"
#include "CoreMinimal.h"
#include "Utility/LogClearer.h"
#include "GameFramework/GameModeBase.h"
#include "Public/Managers/Statistics/StateStatInfo.h"
#include "ZombheadsGameModeBase.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnAllSystemsInitialized);
UCLASS()
class ZOMBHEADS_API AZombheadsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AZombheadsGameModeBase();

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PostInitializeComponents() override;

public:
	FOnAllSystemsInitialized OnAllSystemsInitialized;
	TSharedPtr<class StateStatInfo> GetStateStatInfo();
	TSharedPtr<FOnEndOfRound> GetEndOfRound();

private:
	TUniquePtr<LogClearer> LogClearerPtr;
	TSharedPtr<StateStatInfo> StateStatInfoPtr;
	
};
