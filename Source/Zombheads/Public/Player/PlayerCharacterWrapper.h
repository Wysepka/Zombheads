//Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated 
//documentation files(the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and 
//to permit persons to whom the Software is furnished to do so, subject to the following conditions
#pragma once

#include "CoreMinimal.h"
#include "Characters/PlayerPawn.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/SceneComponent.h"
#include "Math/UnrealMathUtility.h"
#include <Kismet/GameplayStatics.h>
#include <Math/UnrealMathUtility.h>
#include "Inventory/PlayerInventory.h"
#include "Inventory/IPlayerInventory.h"
#include "GameFramework/PlayerController.h"
#include <UObject/Object.h>

#include "CharacterMovement.h"
#include "Engine/AssetManager.h"
#include "Engine.h"
#include "Data/AssetLoader.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Inventory/InventorySceneContainer.h"
#include "PlayerCharacterWrapper.generated.h"

/**
 * 
 */
UENUM()
enum class EPlayerMovingCoordinates : uint8
{
	WorldCoords		UMETA(DisplayName = "World Coordinates"),
	LocalCoords		UMETA(DisplayName = "Local Coordinates"),
};

UCLASS()
class ZOMBHEADS_API APlayerCharacterWrapper : public APlayerController , public ICharacterMovement
{
GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

private:
	void LookAtMousePos();
	FVector DesiredPosition;
	FVector MovementForward;
	FVector MovementBackward;
	FVector MovementRight;
	FVector MovementLeft;
	FVector MovementFinalNormalized;
	FVector MovementFinal;
	float WalkSpeedMultiplier;
	float RunSpeedMultiplier;
	bool bIsSprinting;

	TSharedPtr<IPlayerInventory> Inventory;
	void Equip1Slot();
	void Equip2Slot();
	void Use();
	void FindPawnCharRepresentation(AActor* ActorPawn);
	class USceneComponent* PawnCharRepresentation;
	APlayerPawn* PlayerPawn;

	void ApplyBaseSpeed(UPDA_Character* Data);

	void MoveForward(const FInputActionValue& Value);
	void MoveBackwards(const FInputActionValue& Value);
	void ResetMoveForward();
	void ResetMoveBackwards();
	void MoveRight(const FInputActionValue& Value);
	void MoveLeft(const FInputActionValue& Value);
	void ResetMoveRight();
	void ResetMoveLeft();
	
	
	void SprintBegin();
	void SprintEnd();

	UPROPERTY(EditDefaultsOnly  , Category = "EnhancedInput" , meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputDataAsset> PlayerInputData;

public:

	//UFUNCTION(BlueprintImplementableEvent)
	//void BeginPlay_Impl();


	APlayerCharacterWrapper();

	UPROPERTY(Category = "Moving", BlueprintReadWrite, EditAnywhere)
	EPlayerMovingCoordinates moveCoordsType;

	UPROPERTY(Category = "Moving", BlueprintReadOnly)
	FRotator RotationToMousePos;

	UPROPERTY(Category = "Comps", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* CharacterObjPivot;

	UPROPERTY(Category = "Comps", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class APawn* DefaultPawn;

	UPROPERTY(Category = "Comps", BlueprintReadWrite)
	FPrimaryAssetType PrimaryAssetTypeTest;

	// Helper function to get the scene component pointer
	UFUNCTION(BlueprintPure, Category = "Comps")
		class USceneComponent* GetCharacterObjPivot() const
	{
		return CharacterObjPivot;
	}

	// Helper function to set the scene component pointer
	UFUNCTION(BlueprintCallable, Category = "Comps")
		void SetCharacterObjPivot(class USceneComponent* value)
	{
		this->CharacterObjPivot = value;
	}

	// Helper function to set the scene component pointer
	UFUNCTION(BlueprintCallable, Category = "Comps")
		void SetDefaultPawn(class APawn* value)
	{
		this->DefaultPawn = value;
	}

	virtual void Tick(float DeltaTime) override;

	virtual float GetCharacterRunSpeed() const override;
	virtual float GetCharacterWalkSpeed() const override;
	virtual bool GetIfCharacterSprinting() const override;
	virtual float GetCharacterMovementMagnitude() const override;
};
