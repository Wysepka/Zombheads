// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Player/PlayerCharacterWrapper.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ZombheadsGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBHEADS_API AZombheadsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AZombheadsGameModeBase();

protected:
	virtual void BeginPlay() override;

	
};
