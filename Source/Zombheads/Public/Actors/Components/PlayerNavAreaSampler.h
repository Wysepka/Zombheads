// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "NavigationSystem.h"
#include "Components/ActorComponent.h"
#include "PlayerNavAreaSampler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBHEADS_API UPlayerNavAreaSampler : public USceneComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	uint32 AngleStep;

	float PlayerPawnRadius;
	
	TSoftObjectPtr<UNavigationSystemV1> NavMesh;
	
public:	
	// Sets default values for this component's properties
	UPlayerNavAreaSampler();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
