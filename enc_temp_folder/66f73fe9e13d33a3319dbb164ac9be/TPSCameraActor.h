// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "TPSCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBHEADS_API ATPSCameraActor : public ACameraActor
{
	GENERATED_BODY()
private:
	void CalculateCameraDampPos(float DeltaTime);
	USceneComponent* PawnCharRep;
	FVector CurrentCameraPos;

public:
	UPROPERTY(Category = "CameraMovement", BlueprintReadOnly)
		FVector DampedPos;

	UPROPERTY(Category = "CameraMovement", EditAnywhere)
		FVector Offset;

	UPROPERTY(Category = "CameraMovement", EditAnywhere)
		float Stifness = 0.5f;

	UPROPERTY(Category = "CameraMovement", EditAnywhere)
		float Damping = 0.5f;

	UPROPERTY(Category = "CameraMovement", EditAnywhere)
		float Mass = 10.f;

	UFUNCTION(BlueprintCallable, Category = "Comps")
		void SetCharacterRepresentation(class USceneComponent* value);

	// Helper function to set the scene component pointer
	UFUNCTION(BlueprintPure, Category = "Comps")
		class USceneComponent* GetYourCharacterRepresentation() const;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;
};
