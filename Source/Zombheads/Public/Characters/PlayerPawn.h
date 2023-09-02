//Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated 
//documentation files(the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and 
//to permit persons to whom the Software is furnished to do so, subject to the following conditions
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SceneComponent.h"
#include "Player/Inventory/InventorySceneContainer.h"
#include "Animation/AnimInstance.h"
#include "Player/Inventory/IPlayerInventory.h"

#include "Data/AssetLoaderInitializer.h"
#include "Kismet/GameplayStatics.h"
#include "Animations/PlayerAnimInstance.h"
#include "Player/Inventory/Weapons/WeaponFirearm.h"
#include "Misc/CoreDelegates.h"
#include "Player/Inventory/Weapons/WeaponBase.h"
#include "PlayerPawn.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerPivotInitialized , USceneComponent*);

UCLASS()
class ZOMBHEADS_API APlayerPawn : public APawn
{
	GENERATED_BODY()

private:
	bool bInventorySceneContainersFetched;
	bool bIsAiming;
	bool bExitingApplication;

	bool bIsSingleMontagePlaying;

	USceneComponent* PawnPivot;
	
	IPlayerInventory* PlayerInventory;
	FDelegateHandle ChangedSlotHandle;
	FDelegateHandle InventoryUsedHandle;

	class UInventorySceneContainer* ActiveInventoryContainer;
	class UInventorySceneContainer* DisabledInventoryContainer;

	USkeletalMeshComponent* SkeletalMeshComponent;
	UPlayerAnimInstance* AnimInstance;
	UAnimBlueprint* AnimBlueprint;
	
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void SetSkeletalMeshComponent_CPP(USkeletalMeshComponent* SkeletelMeshComp);
	void AnimationsDataCallback(UAnimationsPrimaryDataAsset* AnimationsData);
	void HandleChangedSlotAnim(int CurrentSlot);
	void HandleItemUsedAnim(const IUsable& WeaponBase);
	void ExitingApplication(bool ExitingPlayMode);
	void ExitingApplication();

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void OnWeaponShotAnimEvent();

	UFUNCTION(BlueprintCallable, Category = "Comps" , meta = (AllowPrivateAccess = "true"))
	void SetPawnPivot(class USceneComponent* value)
	{
		this->PawnPivot = value;
	}

	//Well i know this is a race condition but life is to short to write perfect code
	UFUNCTION(BlueprintCallable, Category = "Comps" , meta = (AllowPrivateAccess = "true"))
	void InvokePlayerPivotDelegate();
	
	FPlayerPivotInitialized PlayerPawnInitializedDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void DisposeInventoryDelegates();
	virtual void BeginDestroy() override;

	UAnimMontage* AimMontage;
	UAnimMontage* ShotMontage;
	FTimerHandle LoopingAnimationTimerHandle;
	FTimerHandle SingleAnimationTimerHandle;

	void PlayLoopingAnimation(const FString& MontageID);
	void PlaySingleAnimationMontage(const FString& MontageID);
	void EndOfSingleAnimMontage(const FString& MontageID);

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void StartAnimationMontage(const FString& MontageID);

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void StopAnimationMontage(const FString& MontageID);

public:	
	// Sets default values for this pawn's properties
	APlayerPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetupPlayerPawn(IPlayerInventory* PlayerInventoryOther);
	void DisposePlayerPawn();
	void GetInventorySceneContainers(UInventorySceneContainer*& Active , UInventorySceneContainer*& Disabled);
	USceneComponent* GetPlayerPivot() const;
	FPlayerPivotInitialized* GetPlayerPivotInitializedDelegate();
};
