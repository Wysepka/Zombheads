// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBHEADS_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	UEnemyAnimInstance(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "AnimData")
	bool IsWalking;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "AnimData")
	bool IsAttacking;

	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite , Category = "AnimData")
	bool IsHit;

	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite , Category = "AnimData")
	bool IsDead;

	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite , Category = "AnimData")
	float LastHitTime;

	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite , Category = "AnimData")
	float CurrentTime;

	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite , Category = "AnimData")
	TSoftObjectPtr<UAnimSequence> HitSequence;
};
