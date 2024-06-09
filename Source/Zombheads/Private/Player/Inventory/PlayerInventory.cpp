//Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated 
//documentation files(the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and 
//to permit persons to whom the Software is furnished to do so, subject to the following conditions

#include "Player/Inventory/PlayerInventory.h"
#include "Player/Inventory/Weapons/WeaponFirearm.h"
#include "Engine/SkeletalMeshSocket.h"

//const FString PlayerInventory::WeaponSocketRightID = FString("Socket_Weapon_Right");

PlayerInventory::PlayerInventory(const TWeakObjectPtr<USceneComponent>& ActiveContainer, const TWeakObjectPtr<USceneComponent>& DisabledContainer ,const TWeakObjectPtr<AActor>& Owner , UWorld* World) : IPlayerInventory()
{
	
	this->ActiveContainer = ActiveContainer;
	this->DisabledContainer = DisabledContainer;
	this->World = World;
	this->Owner = Owner;

	UActorComponent* SkeletalMeshActorComponent = Owner->GetComponentByClass(USkeletalMeshComponent::StaticClass());
	//USceneComponent* SkeletalMeshSceneComp = 
	if(SkeletalMeshActorComponent == nullptr)
	{
		UE_LOG(LogTemp , Log, TEXT("Could not find Skeletal Mesh Component in: %s") , *Owner->GetName());
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red, FString::Printf(TEXT("Could not find Skeletal Mesh Component in: %s") , *Owner->GetName()));
		return;
	}
	
	SkeletalMeshComp = Cast<USkeletalMeshComponent>(SkeletalMeshActorComponent);
	if(SkeletalMeshComp == nullptr)
	{
		UE_LOG(LogTemp , Log, TEXT("Could not cast Skeletal Mesh Component in: %s") , *Owner->GetName());
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red, FString::Printf(TEXT("Could not cast Skeletal Mesh Component in: %s") , *Owner->GetName()));
		return;
	}
}

PlayerInventory::~PlayerInventory()
{
}

void PlayerInventory::PreloadInventory(AAssetLoaderInitializer* AssetInitializer)
{
	TWeakObjectPtr<UAssetLoader> AssetLoader = AssetInitializer->GetAssetLoader();
	if(AssetLoader.Get()->GetIfWeaponsDataInitialized())
	{
		GetWeaponsFromData(AssetLoader.Get()->GetWeaponsData());
	} else
	{
		AssetLoader.Get()->GetWeaponDataDelegate()->AddRaw(this , &PlayerInventory::GetWeaponsFromData);
	}
}

void PlayerInventory::GetWeaponsFromData(UWeaponsPrimaryDataAsset* WeaponsData)
{
	FPrimaryAssetId WeaponsID = UWeaponsPrimaryDataAsset::DefinedAssetID();
	if (WeaponsData == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("ERROR: Could not load WeaponsData"));
		return;
	}
	TArray<FString> ActiveWeaponsIDs = WeaponsData->GetActiveWeaponsIDs();
	if (ActiveWeaponsIDs.Num() < 0) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("ERROR: Active Weapons Count is zero :("));
		return;
	}

	for (size_t i = 0 ; i < ActiveWeaponsIDs.Num() ; i++)
	{
		//UWorld::SpawnActor()
		FTransform DisabledContainerTransform = DisabledContainer->GetComponentTransform();
		FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
		SpawnParameters.Owner = Owner.Get();
		TMap<FString , FWeaponsData> WeaponsDataMap = WeaponsData->GetWeaponsDataMap();
		FWeaponsData WeaponDataStruct = WeaponsDataMap[ActiveWeaponsIDs[i]];
		TSubclassOf<AWeaponBase> Template = WeaponDataStruct.ActorBlueprint;

		//AActor* WeaponActor = World->SpawnActor(AStaticMeshActor::StaticClass(), &DisabledContainerTransform, SpawnParameters);
		
		AActor* WeaponActor = World->SpawnActor(Template, &DisabledContainerTransform, SpawnParameters);
		if (WeaponActor == nullptr) {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("ERROR: Could not Spawn Weapon %s :(") , *WeaponsID.ToString()));
			UE_LOG(LogTemp, Log, TEXT("ERROR: Could not Spawn Weapon: %s"), *ActiveWeaponsIDs[i]);
			return;
		}

		const FAttachmentTransformRules AttachmentRules =
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget , EAttachmentRule::SnapToTarget , EAttachmentRule::KeepRelative , true);

		//WeaponActor->AttachToComponent(DisabledContainer, AttachmentRules);
		FName SocketName = FName(WeaponSocketRightID);
		const USkeletalMeshSocket* MeshSocket = SkeletalMeshComp->GetSocketByName(SocketName);
		//SkeletalMeshComp->AttachToComponent(SkeletalMeshComp , AttachmentRules , SocketName);
		if(MeshSocket == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("ERROR: Could not find Socket: %s :(") , *SocketName.ToString()));
			UE_LOG(LogTemp, Log, TEXT("ERROR: Could not find Socket: %s :("), *SocketName.ToString());
			return;
		}
		
		MeshSocket->AttachActor(WeaponActor , SkeletalMeshComp);
		
		AWeaponBase* WeaponBP = Cast<AWeaponBase>(WeaponActor);

		if (WeaponBP == nullptr) {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("ERROR: Could not Cast to AWeponBase %s :(") , *WeaponsID.ToString()));
			UE_LOG(LogTemp, Log, TEXT("ERROR: Could not cast to AWeaponBase: %s"), *ActiveWeaponsIDs[i]);
			return;
		}

		IUsable* Usable = Cast<IUsable>(WeaponActor);

		Usable->Initialize();

		WeaponCache.Add(WeaponDataStruct.SlotID , Usable);
		
		UE_LOG(LogTemp, Log, TEXT("Spawning WeaponID: %s"), *ActiveWeaponsIDs[i]);
	}
}

void PlayerInventory::DeloadInventory() {
	IPlayerInventory::DeloadInventory();
}

void PlayerInventory::Use()
{
	if(CurrentSlotEquiped > 0)
	{
		WeaponCache[CurrentSlotEquiped]->Use();
		if(InventoryItemUsedDelegate.IsBound())
		{
			InventoryItemUsedDelegate.Broadcast(*WeaponCache[CurrentSlotEquiped]);
		}
		if(WeaponCache[CurrentSlotEquiped]->GetUsableType() == EItemType::Firearm)
		{
			
		}
	}
}

bool PlayerInventory::IsAiming()
{
	return CurrentSlotEquiped > 0;
}

FChangedSlotDelegate* PlayerInventory::GetChangedSlotDelegate()
{
	return &ChangedSlotDelegate;
}

FInventoryItemUsedDelegate* PlayerInventory::GetInventoryItemUsedDelegate()
{
	return &InventoryItemUsedDelegate;
}

FOnWeaponChanged* PlayerInventory::GetWeaponChangedDelegate()
{
	return &WeaponChangedDelegate;
}


void PlayerInventory::Equip1Slot() {
	if (CurrentSlotEquiped == 0) {
		WeaponCache[1]->Equip();
		CurrentSlotEquiped = 1;
	}
	else if(CurrentSlotEquiped == 1){
		WeaponCache[1]->DeEquip();
		CurrentSlotEquiped = 0;
	}
	else {
		WeaponCache[CurrentSlotEquiped]->DeEquip();
		WeaponCache[1]->Equip();
		CurrentSlotEquiped = 1;
	}

	if(ChangedSlotDelegate.IsBound())
	{
		ChangedSlotDelegate.Broadcast(CurrentSlotEquiped);
	}

	TryInvokeOnWeaponChangedDelegate();
}

void PlayerInventory::TryInvokeOnWeaponChangedDelegate()
{
	if(WeaponChangedDelegate.IsBound())
	{
		if(WeaponCache.Contains(CurrentSlotEquiped) && WeaponCache[CurrentSlotEquiped]->GetUsableType() == EItemType::Firearm)
		{
			TWeakObjectPtr<AWeaponBase> WeaponBase = Cast<AWeaponBase>(WeaponCache[CurrentSlotEquiped]);
			if(WeaponBase.IsValid())
			{
				WeaponChangedDelegate.Broadcast(TWeakObjectPtr<AWeaponBase>(WeaponBase));
			}
			else
			{
				//LOG_INCORRECT_CAST("Could not cast from %s to %s" , *WeaponCache[CurrentSlotEquiped] , AWeaponBase::StaticClass()->GetName());
			}
		}
		else
		{
			WeaponChangedDelegate.Broadcast(TWeakObjectPtr<UObject>(nullptr));
		}
	}
}

void PlayerInventory::Equip2Slot()
{
	if (CurrentSlotEquiped == 0) {
		WeaponCache[2]->Equip();
		CurrentSlotEquiped = 2;
	}
	else if(CurrentSlotEquiped == 2){
		WeaponCache[2]->DeEquip();
		CurrentSlotEquiped = 0;
	}
	else {
		WeaponCache[CurrentSlotEquiped]->DeEquip();
		WeaponCache[2]->Equip();
		CurrentSlotEquiped = 2;
	}

	if(ChangedSlotDelegate.IsBound())
	{
		ChangedSlotDelegate.Broadcast(CurrentSlotEquiped);
	}
	TryInvokeOnWeaponChangedDelegate();
}

