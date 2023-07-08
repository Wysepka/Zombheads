// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/SceneComponent.h"
#include "Math/UnrealMathUtility.h"
#include <Kismet/GameplayStatics.h>
#include <Math/UnrealMathUtility.h>
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterWrapper.generated.h"

/**
 * 
 */
UENUM()
enum class PlayerMovingCoordinates : uint8
{
	WorldCoords		UMETA(DisplayName = "World Coordinates"),
	LocalCoords		UMETA(DisplayName = "Local Coordinates"),
};

UCLASS()
class ZOMBHEADS_API APlayerCharacterWrapper : public APlayerController
{
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

private:
	void LookAtMousePos();
	FVector DesiredPosition;
	FVector MovementForward;
	FVector MovementRight;

public:

	UFUNCTION(BlueprintImplementableEvent)
	void BeginPlay_Impl();

	GENERATED_BODY()

	APlayerCharacterWrapper();

	UPROPERTY(Category = "Moving", BlueprintReadWrite, EditAnywhere)
	PlayerMovingCoordinates moveCoordsType;

	UPROPERTY(Category = "Moving" , BlueprintReadWrite , EditAnywhere)
	float MovingSpeed;

	UPROPERTY(Category = "Moving", BlueprintReadOnly)
	FRotator RotationToMousePos;

	UPROPERTY(Category = "Comps", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* CharacterObjPivot;

	UPROPERTY(Category = "Comps", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class APawn* DefaultPawn;

	void MoveCharacter();

	void MoveForward(float value);

	void MoveRight(float value);

	// Helper function to get the scene component pointer
	UFUNCTION(BlueprintPure, Category = "Comps")
		class USceneComponent* GetYourSceneComponent() const
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
};
