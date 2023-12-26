//Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated 
//documentation files(the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and 
//to permit persons to whom the Software is furnished to do so, subject to the following conditions
#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/ActorVitalityComponent.h"
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
#include "Player/CharacterMovement.h"
#include "Player/Inventory/Weapons/WeaponBase.h"
#include "UObject/WeakInterfacePtr.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Data/InputDataAsset.h"
#include "PlayerPawn.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerPivotInitialized , USceneComponent*);

UCLASS()
class ZOMBHEADS_API APlayerPawn : public APawn , public IAssetLoaderObserver
{
	GENERATED_BODY()

private:
	bool bInventorySceneContainersFetched;
	bool bIsAiming;
	bool bExitingApplication;

	bool bIsSingleMontagePlaying;

	USceneComponent* PawnPivot;
	
	TWeakPtr<IPlayerInventory> PlayerInventory;
	FDelegateHandle ChangedSlotHandle;
	FDelegateHandle InventoryUsedHandle;

	TWeakObjectPtr<UInventorySceneContainer> ActiveInventoryContainer;
	TWeakObjectPtr<UInventorySceneContainer> DisabledInventoryContainer;

	USkeletalMeshComponent* SkeletalMeshComponent;
	UPlayerAnimInstance* AnimInstance;
	UAnimBlueprint* AnimBlueprint;

	TWeakInterfacePtr<ICharacterMovement> CharacterMovement;
	TSoftObjectPtr<UActorVitalityComponent> VitalityComponent;
	TWeakInterfacePtr<IVitalityComponent> VitalityComponentInterface;
	
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void SetSkeletalMeshComponent_CPP(USkeletalMeshComponent* SkeletelMeshComp);
	
	void AnimationsDataCallback(UAnimationsPrimaryDataAsset* AnimationsData);
	virtual void PrimaryDataAssetLoaded(UPDA_Character* Data) override;
	
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

	//Well i know this is a race condition but life is too short to write perfect code
	UFUNCTION(BlueprintCallable, Category = "Comps" , meta = (AllowPrivateAccess = "true"))
	void InvokePlayerPivotDelegate();
	
	FPlayerPivotInitialized PlayerPawnInitializedDelegate;

	UPROPERTY(EditDefaultsOnly  , Category = "EnhancedInput" , meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputDataAsset> PlayerInputData;

	TSoftObjectPtr<UActorVitalityComponent> GetVitalityComponent_Internal();

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
	void InitializeCharacterData(UAssetLoader* AssetLoaderPin);

	void SetupPlayerPawn(const TSharedPtr<IPlayerInventory>& PlayerInventoryOther ,const TWeakInterfacePtr<ICharacterMovement>& CharacterMovementOther);
	void DisposePlayerPawn();
	void GetInventorySceneContainers(TWeakObjectPtr<UInventorySceneContainer>& Active , TWeakObjectPtr<UInventorySceneContainer>& Disabled);
	USceneComponent* GetPlayerPivot() const;
	FPlayerPivotInitialized* GetPlayerPivotInitializedDelegate();

	TWeakInterfacePtr<IVitalityComponent> GetVitalityComponent();
};
