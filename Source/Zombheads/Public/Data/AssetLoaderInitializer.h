// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "AssetLoader.h"
#include "GameFramework/Actor.h"
#include "AssetLoaderInitializer.generated.h"

UCLASS()
class ZOMBHEADS_API AAssetLoaderInitializer : public AActor
{
	GENERATED_BODY()

private:
	UAssetLoader* AssetLoader;
	
public:	
	// Sets default values for this actor's properties
	AAssetLoaderInitializer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	TWeakObjectPtr<UAssetLoader> GetAssetLoader();

};
