// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Actors/Enemy/EnemyController.h"
#include "Animations/EnemyAnimInstance.h"
#include "EnemyBase.generated.h"

UCLASS(Blueprintable)
class ZOMBHEADS_API AEnemyBase : public APawn
{
	GENERATED_BODY()
private:
	FDelegateHandle OnReachedDestHandle;
	TSoftObjectPtr<AEnemyController> EnemyController;

	TObjectPtr<USkeletalMeshComponent> EnemyMesh;
	TSoftObjectPtr<UEnemyAnimInstance> AnimInstance;

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true") , Category = "Enemy")
	virtual void AssignSkeletalMesh_Blueprint(USkeletalMeshComponent* SkeletalMeshComponent);
	
public:
	// Sets default values for this pawn's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnControllerStateChanged(FOnStateChangedData StateData);
	virtual void BeginDestroy() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
