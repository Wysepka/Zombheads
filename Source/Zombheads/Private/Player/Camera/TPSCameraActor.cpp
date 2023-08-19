//Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated 
//documentation files(the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and 
//to permit persons to whom the Software is furnished to do so, subject to the following conditions

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
	/*
	if (CharRep != NULL) {
		FVector OffsetDesiredPosition = CharRep->GetComponentTransform().GetLocation() + Offset;
		FVectorSpringState SpringState;
		CurrentCameraPos = UKismetMathLibrary::VectorSpringInterp(CurrentCameraPos, OffsetDesiredPosition, SpringState, Stifness, Damping, DeltaTime, Mass);
		SetActorLocation(CurrentCameraPos);
	}
	*/
	if (CharRep != NULL) {
		FVector TargetLocation = CharRep->GetComponentTransform().GetLocation() + Offset;
		FVector CurrentLocation = GetActorLocation();

		FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, InterpolationSpeed);
		SetActorLocation(NewLocation);
		/*
		// Apply damping
		FVector DeltaLocation = NewLocation - CurrentLocation;
		FVector DampedLocation = CurrentLocation + DeltaLocation * DampingFactor * DeltaTime;
		*/
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