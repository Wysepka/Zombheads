//Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated 
//documentation files(the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and 
//to permit persons to whom the Software is furnished to do so, subject to the following conditions
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SceneComponent.h"
#include "Player/Inventory/InventorySceneContainer.h"
#include "PlayerPawn.generated.h"

UCLASS()
class ZOMBHEADS_API APlayerPawn : public APawn
{
	GENERATED_BODY()

private:
	bool InventorySceneContainersFetched;

	class UInventorySceneContainer* ActiveInventoryContainer;
	class UInventorySceneContainer* DisabledInventoryContainer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this pawn's properties
	APlayerPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetInventorySceneContainers(UInventorySceneContainer*& Active , UInventorySceneContainer*& Disabled);

};
