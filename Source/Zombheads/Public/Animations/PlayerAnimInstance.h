// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, BlueprintType)
class ZOMBHEADS_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	UPlayerAnimInstance(const FObjectInitializer& ObjectInitializer);
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AnimData")
	float ShotValue;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category= "AnimData")
	bool IsArmed;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "AnimData")
	float ShotSpeed;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "AnimData")
	bool IsWalking;
	
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "AnimData")
	bool IsRunning;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "AnimData")
	float WalkSpeedMultiplier;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "AnimData")
	float RunSpeedMultiplier;
};
