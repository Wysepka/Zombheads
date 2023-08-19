//Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated 
//documentation files(the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and 
//to permit persons to whom the Software is furnished to do so, subject to the following conditions
#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InventorySceneContainer.generated.h"

UENUM()
enum class EInventoryContainerType {
	Active = 0,
	Disabled = 1
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBHEADS_API UInventorySceneContainer : public USceneComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Settings")
		EInventoryContainerType ContainerType;

public:	
	// Sets default values for this component's properties
	UInventorySceneContainer();



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	EInventoryContainerType GetContainerType();
		
};
