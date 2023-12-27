//Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated 
//documentation files(the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and 
//to permit persons to whom the Software is furnished to do so, subject to the following conditions
#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
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
	FQuat StartRotation;

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
		float Mass = 10.0f;

	UPROPERTY(Category = "CameraMovement", EditAnywhere)
		float DampingFactor = 0.5f;

	UPROPERTY(Category = "CameraMovement", EditAnywhere)
		float InterpolationSpeed = 0.5f;

	UPROPERTY(Category = "CameraMovement", EditAnywhere)
		bool isLookingAtTarget;

	UFUNCTION(BlueprintCallable, Category = "Comps")
		void SetCharacterRepresentation(class USceneComponent* value);

	// Helper function to set the scene component pointer
	UFUNCTION(BlueprintPure, Category = "Comps")
		class USceneComponent* GetYourCharacterRepresentation() const;

	void LookAtTarget();
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;
};
