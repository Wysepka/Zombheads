// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharFacade.h"

// Sets default values
APlayerCharFacade::APlayerCharFacade()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharFacade::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharFacade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharFacade::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

