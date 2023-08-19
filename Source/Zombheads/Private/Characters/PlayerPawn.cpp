//Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated 
//documentation files(the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and 
//to permit persons to whom the Software is furnished to do so, subject to the following conditions

#include "Characters/PlayerPawn.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerPawn::GetInventorySceneContainers(UInventorySceneContainer*& Active, UInventorySceneContainer*& Disabled) {
	if (!InventorySceneContainersFetched) {
		TArray<AActor*> Childs;
		GetAttachedActors(Childs, true, true);

		TArray<UActorComponent*> Components = GetComponentsByClass(UInventorySceneContainer::StaticClass());
		for (size_t i = 0; i < Components.Num(); i++)
		{
			UInventorySceneContainer* Container = Cast<UInventorySceneContainer>(Components[i]);
			if (Container != nullptr) {
				if (Container->GetContainerType() == EInventoryContainerType::Active) {
					ActiveInventoryContainer = Container;
				}
				else if (Container->GetContainerType() == EInventoryContainerType::Disabled) {
					DisabledInventoryContainer = Container;
				}
			}
		}
		InventorySceneContainersFetched = true;
	}
	Active = ActiveInventoryContainer;
	Disabled = DisabledInventoryContainer;
	//TArray<UInventorySceneContainer*> Containers = { ActiveInventoryContainer, DisabledInventoryContainer };
	//return Containers;
}
