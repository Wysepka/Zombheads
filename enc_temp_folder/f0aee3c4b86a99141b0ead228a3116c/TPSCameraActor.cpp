// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Camera/TPSCameraActor.h"

void ATPSCameraActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	CalculateCameraDampPos(DeltaTime);
}

void ATPSCameraActor::BeginPlay() {
	Super::BeginPlay();
	SetActorTickEnabled(true);
}

void ATPSCameraActor::CalculateCameraDampPos(float DeltaTime) {
	//auto s = 's';
	USceneComponent* CharRep = GetYourCharacterRepresentation();
	if (CharRep != NULL) {
		FVector OffsetDesiredPosition = CharRep->GetComponentTransform().GetLocation() + Offset;
		FVectorSpringState SpringState;
		CurrentCameraPos = UKismetMathLibrary::VectorSpringInterp(CurrentCameraPos, OffsetDesiredPosition, SpringState, Stifness, Damping, DeltaTime, Mass);
		SetActorLocation(CurrentCameraPos);
	}
}

void ATPSCameraActor::SetCharacterRepresentation(class USceneComponent* value)
{
	this->PawnCharRep = value;
}

USceneComponent* ATPSCameraActor::GetYourCharacterRepresentation() const
{
	return PawnCharRep;
}