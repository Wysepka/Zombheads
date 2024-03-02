// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Actors/Spawner/EnemySpawnPoint.h"

// Sets default values
AEnemySpawnPoint::AEnemySpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	if (WITH_EDITOR)
	{
		PrimaryActorTick.bCanEverTick = true;
		PrimaryActorTick.bStartWithTickEnabled = true;
	}
}

bool AEnemySpawnPoint::ShouldTickIfViewportsOnly() const
{
	return true;
}

// Called when the game starts or when spawned
void AEnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#if WITH_EDITOR
	DrawDebugCubeAtActorLocation();
#endif
	
}

void AEnemySpawnPoint::DrawDebugCubeAtActorLocation() const
{
	FVector ActorLocation = GetActorLocation();
	FVector BoxExtent(50.f, 50.f, 50.f); // Size of the box (X, Y, Z)
	FColor Color(255, 0, 0); // Red color, you can customize it
	FRotator ActorRotation = GetActorRotation();

	// Draw the debug box
	DrawDebugBox(GetWorld(), ActorLocation, BoxExtent, ActorRotation.Quaternion(), Color, false, -1, 0, 2.f);
}

