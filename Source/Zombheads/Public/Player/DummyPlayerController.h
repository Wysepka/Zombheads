// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DummyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBHEADS_API ADummyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void InitMainMenuSettings();
};
