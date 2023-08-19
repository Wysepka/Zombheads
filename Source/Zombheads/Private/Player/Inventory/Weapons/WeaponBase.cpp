// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Player/Inventory/Weapons/WeaponBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::Equip()
{
	for (size_t i = 0; i < WeaponMeshVisuals.Num(); i++)
	{
		WeaponMeshVisuals[i]->SetVisibility(true);
	}
}

void AWeaponBase::DeEquip()
{
	for (size_t i = 0; i < WeaponMeshVisuals.Num(); i++)
	{
		WeaponMeshVisuals[i]->SetVisibility(false);
	}
}

void AWeaponBase::Initialize()
{
	TArray<UActorComponent*> StaticMeshActors = GetComponentsByClass(UActorComponent::StaticClass());
	for (size_t i = 0 ; i < StaticMeshActors.Num() ; i++)
	{
		UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(StaticMeshActors[i]);
		if(MeshComponent != nullptr)
		{
			WeaponMeshVisuals.Add(MeshComponent);
			MeshComponent->SetVisibility(false);
		}
	}
	
	AActor* ActorInitializer = UGameplayStatics::GetActorOfClass(GetWorld(), AAssetLoaderInitializer::StaticClass());
	AAssetLoaderInitializer* LoaderInitializer = Cast<AAssetLoaderInitializer>(ActorInitializer);
	AssetLoader = LoaderInitializer->GetAssetLoader();

	if(!AssetLoader->GetIfWeaponsDataInitialized())
	{
		AssetLoader->GetWeaponDataDelegate()->AddUObject(this , &AWeaponBase::WeaponAssetsLoaded);
	} else
	{
		WeaponAssetsLoaded(AssetLoader->GetWeaponsData());
	}
}

void AWeaponBase::WeaponAssetsLoaded(UWeaponsPrimaryDataAsset* DataAsset)
{
	UE_LOG(LogTemp, Log, TEXT("Weapon Data Asset loaded"));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Weapon Data Asset loaded")));

	UseSound = DataAsset->GetWeaponsDataMap()[WeaponID].UseSound;
}

void AWeaponBase::Use()
{

}




