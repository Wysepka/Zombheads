// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Data/AssetLoaderInitializer.h"

// Sets default values
AAssetLoaderInitializer::AAssetLoaderInitializer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AssetLoader = UObject::CreateDefaultSubobject<UAssetLoader>(FName("AssetLoader"));
}

// Called when the game starts or when spawned
void AAssetLoaderInitializer::BeginPlay()
{
	Super::BeginPlay();
	UAssetManager& AssetManager = UAssetManager::Get();
	AssetLoader->LoadAssets(&AssetManager);
}

// Called every frame
void AAssetLoaderInitializer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UAssetLoader* AAssetLoaderInitializer::GetAssetLoader()
{
	if(AssetLoader == nullptr)
	{
		UE_LOG(LogTemp , Log, TEXT("AssetLoader is not initialized ! Creating new Instance"));
		AssetLoader = NewObject<UAssetLoader>(UAssetLoader::StaticClass());
	}
	return AssetLoader;
}


