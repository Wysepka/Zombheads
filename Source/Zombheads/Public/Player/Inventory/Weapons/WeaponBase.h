// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Usable.h"
#include "Data/AssetLoader.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/AssetManager.h"
#include "Data/AssetLoaderInitializer.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Inventory/PlayerInventory.h"
#include "Player/Inventory/PlayerInventory.h"
#include "WeaponBase.generated.h"



//class UAssetLoader;
UCLASS()
class ZOMBHEADS_API AWeaponBase : public AActor , public IUsable
{
	GENERATED_BODY()

private:
	TArray<UStaticMeshComponent*> WeaponMeshVisuals;
	UAssetLoader* AssetLoader;
	void WeaponAssetsLoaded(UWeaponsPrimaryDataAsset* DataAsset);

	UPROPERTY(EditAnywhere)
	FString WeaponID;
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	USoundWave* UseSound;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Equip() override;
	virtual void DeEquip() override;
	virtual void Initialize() override;
	virtual void Use() override;
};