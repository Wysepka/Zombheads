// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/PlayerPawn.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EEnemyState : uint8
{
	IDLE = 0			UMETA(DisplayName = "IDLE"),
	TOWARD_TARGET = 1	UMETA(DisplayName = "WALKING"),
	ATTACKING = 2		UMETA(DisplayName = "ATTACKING"),
};

USTRUCT()
struct FOnStateChangedData
{
	GENERATED_BODY()
private:
	EEnemyState State;
	TSoftObjectPtr<APlayerPawn> Pawn;

public:
	FOnStateChangedData() { State = IDLE; }
	FOnStateChangedData(EEnemyState State) { this->State = State; }
	FOnStateChangedData(EEnemyState State ,const TSoftObjectPtr<APlayerPawn>& Pawn) { this->State = State , this->Pawn = Pawn	; }

	EEnemyState GetState() const {  return State; }
	TSoftObjectPtr<APlayerPawn> GetPawn() {return Pawn;}
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStateChanged ,FOnStateChangedData);
UCLASS()
class ZOMBHEADS_API AEnemyController : public AAIController
{
	GENERATED_BODY()
private:
	AActor* Target;

	EEnemyState CurrentEnemyState;

	UPROPERTY(EditAnywhere , Category = "Settings")
	float StoppingDistance;

	USceneComponent* TargetPivot;
	TSoftObjectPtr<APlayerPawn> TargetPawn;
	void AssignTargetPivotCallback(USceneComponent* TargetPivot);
	
protected:
	void BeginPlay() override;
	void MoveToTarget(const FTransform& TargetTransform);
	void RotateToTarget(const FTransform& TargetTransform , const float DeltaTime) const;
	void Tick(float DeltaSeconds) override;
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

public:
	FOnStateChanged OnStateChanged;
	AEnemyController();
};
