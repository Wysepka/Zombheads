// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Actors/Enemy/EnemyController.h"
#include "Animations/EnemyAnimInstance.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class ZOMBHEADS_API AEnemyBase : public APawn , public DamageableReceiver , public IAssetLoaderObserver
{
	GENERATED_BODY()
private:
	
	FDelegateHandle OnReachedDestHandle;
	TSoftObjectPtr<AEnemyController> EnemyController;

	TObjectPtr<USkeletalMeshComponent> EnemyMesh;
	TSoftObjectPtr<UEnemyAnimInstance> AnimInstance;
	TSoftObjectPtr<UMaterialInstanceDynamic> DynamicEnemyMaterial;
	TSoftObjectPtr<UCapsuleComponent> CapsuleCompPtr;

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true") , Category = "Enemy")
	virtual void AssignSkeletalMesh_Blueprint(USkeletalMeshComponent* SkeletalMeshComponent);
	virtual void LoadVitalityData(TSoftObjectPtr<UActorVitalityComponent> VitalityComponent);

	virtual EActorType GetActorType();
	virtual void PrimaryDataAssetLoaded(UPDA_Character* Data) override;
	bool IsDead;
	
public:
	// Sets default values for this pawn's properties
	AEnemyBase();
	void GetDamageableComponent(TSoftObjectPtr<UActorComponent> VitalityComponent);
	void GetVitalityComponent(TSoftObjectPtr<UActorComponent>& VitalityComponent);
	void GetCapsuleComponent();

protected:
	UPDA_Character* CharData;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnControllerStateChanged(FOnStateChangedData StateData);
	virtual void BeginDestroy() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void DamageTaken_Receiver(TWeakInterfacePtr<IVitalityComponent> VitalityComponent) override;
	bool GetIsDead();
	
};
