// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Data/AssetLoaderInitializer.h"

// Sets default values
AAssetLoaderInitializer::AAssetLoaderInitializer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//AssetLoader = UObject::CreateDefaultSubobject<UAssetLoader>(FName("AssetLoader"));
}

void AAssetLoaderInitializer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if(AssetLoader == nullptr)
	{
		AssetLoader = TWeakObjectPtr<UAssetLoader>(NewObject<UAssetLoader>(UAssetLoader::StaticClass()));
	}
}

// Called when the game starts or when spawned
void AAssetLoaderInitializer::BeginPlay()
{
	Super::BeginPlay();
	UAssetManager& AssetManager = UAssetManager::Get();
	GetAssetLoader()->LoadAssets(&AssetManager);
	//AssetLoader->LoadAssets(&AssetManager);
}

void AAssetLoaderInitializer::BeginDestroy()
{
	Super::BeginDestroy();
	GetAssetLoader()->UnloadAssets(&UAssetManager::Get());
}

// Called every frame
void AAssetLoaderInitializer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TWeakObjectPtr<UAssetLoader> AAssetLoaderInitializer::GetAssetLoader()
{
	return AssetLoader;
}


