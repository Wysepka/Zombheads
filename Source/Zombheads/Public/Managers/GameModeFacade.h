// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Utility/LogClearer.h"
#include "GameModeFacade.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBHEADS_API AGameModeFacade : public AGameModeBase
{
	GENERATED_BODY()

public:
	void StartPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	TUniquePtr<LogClearer> LogClearerPtr;
};
