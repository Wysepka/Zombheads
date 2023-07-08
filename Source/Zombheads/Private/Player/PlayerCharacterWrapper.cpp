// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PlayerCharacterWrapper.h"

APlayerCharacterWrapper::APlayerCharacterWrapper() {
}

//void APlayerCharacterWrapper::Tick(float deltaTime) {
//	LookAtMousePos();
//}

void APlayerCharacterWrapper::BeginPlay() {
	Super::BeginPlay();
	BeginPlay_Impl();
}

void APlayerCharacterWrapper::MoveCharacter()
{
}
/*
void APlayerCharacterWrapper::BeginPlay_Impl() {

}
*/
void APlayerCharacterWrapper::SetupInputComponent() {
	Super::SetupInputComponent();
	this->InputComponent->BindAxis("MoveForward", this, &APlayerCharacterWrapper::MoveForward);
	this->InputComponent->BindAxis("MoveRight", this, &APlayerCharacterWrapper::MoveRight);
}

void APlayerCharacterWrapper::MoveForward(float value) {
	if (FMath::IsNearlyZero(value)) { 
		MovementForward = FVector::ZeroVector;
		return; 
	}
	APawn* ControllerPawn = GetPawn();
	if (ControllerPawn) {
		if (moveCoordsType == PlayerMovingCoordinates::LocalCoords) {
			MovementForward = value * ControllerPawn->GetActorForwardVector();
		}
		else if (moveCoordsType == PlayerMovingCoordinates::WorldCoords) {
			MovementForward = value * FVector::ForwardVector;
		}
		//ControllerPawn->AddMovementInput(MovementForward);
		/*
		UPawnMovementComponent* PawnMovememt = ControllerPawn->GetMovementComponent();
		if (PawnMovememt != NULL) {
			PawnMovememt->AddInputVector(MovementForward);
		}
		*/
	}
	//transform.
}

void APlayerCharacterWrapper::MoveRight(float value) {
	if (FMath::IsNearlyZero(value)) { 
		MovementRight = FVector::ZeroVector;
		return; 
	}
	APawn* ControllerPawn = GetPawn();
	if (ControllerPawn) {
		if (moveCoordsType == PlayerMovingCoordinates::LocalCoords) {
			MovementRight = value * ControllerPawn->GetActorRightVector();
		}
		else if (moveCoordsType == PlayerMovingCoordinates::WorldCoords) {
			MovementRight = value * FVector::RightVector;
		}
		//ControllerPawn->AddMovementInput(MovementRight);
		/*
		UPawnMovementComponent* PawnMovememt = ControllerPawn->GetMovementComponent();
		if (PawnMovememt != NULL) {
			PawnMovememt->AddInputVector(MovementRight);
		}
		*/
	}
}

void APlayerCharacterWrapper::Tick(float delta) {
	Super::Tick(delta);
	LookAtMousePos();

	APawn* ControllerPawn = GetPawn();
	if (ControllerPawn) 
	{
		UPawnMovementComponent* PawnMovememt = ControllerPawn->GetMovementComponent();
		if (PawnMovememt != NULL) {
			FVector ForwardAndRight = MovementForward + MovementRight;
			if (ForwardAndRight.Normalize()) {
				PawnMovememt->AddInputVector(ForwardAndRight * MovingSpeed);
			}
		}
	}
}

void APlayerCharacterWrapper::LookAtMousePos() {
	//return;
	FVector2D MousePos;
	float locX, locY;
	GetMousePosition(locX,locY);
	MousePos = FVector2D(locX, locY);
	FTransform pawnTransform = GetPawn()->GetTransform();
	//FVector3f::UpVector
	FPlane playerPlane = FPlane(pawnTransform.GetLocation(), FVector3d::UpVector);
	FVector WorldLocation;
	FVector WorldDirection;

	// Convert screen space mouse coordinates to a ray in world space
	UGameplayStatics::DeprojectScreenToWorld(
		this,
		MousePos,
		WorldLocation,
		WorldDirection
	);

	// Calculate the intersection point between the ray and the plane
	//FVector PlanePos = WorldLocation + (WorldDirection * ((-playerPlane.W) / FVector::DotProduct(playerPlane, WorldDirection)));
	//FVector DirOnPlane = WorldLocation - pawnTransform.GetLocation();
	FVector IntersectionMousePlayerPlane = FMath::RayPlaneIntersection(WorldLocation, WorldDirection, playerPlane);
	FVector DirToWorldMousePos = (IntersectionMousePlayerPlane - pawnTransform.GetLocation());
	if (DirToWorldMousePos.Normalize()) {
		RotationToMousePos = DirToWorldMousePos.Rotation();
		//GetPawn()->SetActorRotation(DirToWorldMousePos.Rotation());
	}
	//GetMousePosition(float MouseXPos, float MouseYPos);
}
