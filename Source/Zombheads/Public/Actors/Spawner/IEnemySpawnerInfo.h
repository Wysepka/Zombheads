// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "Actors/Enemy/EnemyBase.h"
#include "UObject/Interface.h"
#include "IEnemySpawnerInfo.generated.h"

// This class does not need to be modified.
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewWaveSpawned , int)

UINTERFACE(MinimalAPI)
class UIEnemySpawnerInfo : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZOMBHEADS_API IIEnemySpawnerInfo
{
	GENERATED_BODY()

public:
	virtual int GetCurrentWave() {return 0;}
	virtual TSharedPtr<FOnEnemyDied> GetOnEnemyDiedDelegate() {return MakeShareable(new FOnEnemyDied());}
	virtual TSharedPtr<FOnNewWaveSpawned> GetOnNewWaveSpanedDelegate() {return MakeShareable(new FOnNewWaveSpawned());}
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
