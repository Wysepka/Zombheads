// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Actors/Enemy/EnemyZombie.h"

// Sets default values
AEnemyZombie::AEnemyZombie()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AEnemyZombie::BeginPlay()
{
	Super::BeginPlay();
	
}

/*
void AEnemyZombie::OnControllerStateChanged(TSoftObjectPtr<APlayerPawn> PlayerPawn)
{
	Super::OnControllerStateChanged(PlayerPawn);
	
}
*/

// Called every frame
void AEnemyZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

