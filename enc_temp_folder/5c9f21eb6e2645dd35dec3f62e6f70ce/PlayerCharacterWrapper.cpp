// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PlayerCharacterWrapper.h"

APlayerCharacterWrapper::APlayerCharacterWrapper() {
	/*
	// Expose the component to the Blueprint Details Panel
	SetIsReplicated(false);
	SetVisibility(true);
	SetHiddenInGame(false);
	SetMobility(EComponentMobility::Movable);
	bEditableWhenInherited = true;
	bVisibleAnywhere = true;
	bVisibleDefaultsOnly = false;
	bCreateNew = true;

	// Make the component editable in the Blueprint Details Panel
	SetEditInline(true);
	*/
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
	if (FMath::IsNearlyZero(value)) { return; }
	APawn* ControllerPawn = GetPawn();
	if (ControllerPawn) {
		
		FVector MovementForward = value * 100.0f * ControllerPawn->GetActorForwardVector();
		ControllerPawn->AddMovementInput(MovementForward);
		UPawnMovementComponent* PawnMovememt = ControllerPawn->GetMovementComponent();
		if (PawnMovememt != NULL) {
			PawnMovememt->AddInputVector(MovementForward);
		}
	}
	//transform.
}

void APlayerCharacterWrapper::MoveRight(float value) {
	if (FMath::IsNearlyZero(value)) { return; }
	APawn* ControllerPawn = GetPawn();
	if (ControllerPawn) {
		FVector MovementRight = value * ControllerPawn->GetActorRightVector();
		ControllerPawn->AddMovementInput(MovementRight);
		UPawnMovementComponent* PawnMovememt = ControllerPawn->GetMovementComponent();
		if (PawnMovememt != NULL) {
			PawnMovememt->AddInputVector(MovementRight);
		}
	}
}

void APlayerCharacterWrapper::Tick(float delta) {
	Super::Tick(delta);
	LookAtMousePos();
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
