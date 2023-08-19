// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Player/Inventory/Weapons/FirearmShell.h"

// Sets default values
AFirearmShell::AFirearmShell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFirearmShell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFirearmShell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

