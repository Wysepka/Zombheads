// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Player/Inventory/Weapons/WeaponFirearm.h"

#include "Actors/Enemy/EnemyBase.h"

void AWeaponFirearm::Use()
{
	if(!Muzzle.IsValid())
	{
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , TEXT("Muzzle Component is not set in Blueprint"));
		UE_LOG(LogTemp , Log , TEXT("Muzzle Component is not set in Blueprint"));
		return;
	}

	if(!WeaponStartRaycast.IsValid())
	{
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , TEXT("WeaponStartRay is not set in Blueprint"));
		UE_LOG(LogTemp , Log , TEXT("WeaponStartRay is not set in Blueprint"));
		return;
	}

	FHitResult HitResult;
	FVector Dir = WeaponStartRaycast->GetForwardVector() * 20000.f;
	if(GetWorld()->LineTraceSingleByChannel(HitResult , WeaponStartRaycast->GetComponentLocation() , Dir , ECC_GameTraceChannel2))
	{
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Hit with Weapon %s |-| Object: %s") , *this->GetName() , *HitResult.GetActor()->GetName()));
		UE_LOG(LogTemp , Log , TEXT("Hit with weapon %s |-| Object: %s") , *this->GetName() , *HitResult.GetActor()->GetName());

		TSoftObjectPtr<AEnemyBase> EnemyBase = Cast<AEnemyBase>(HitResult.GetActor());
		if(!EnemyBase.IsValid())
		{
			GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Hit Wrong Actor Check CollisionChannels")));
			UE_LOG(LogTemp , Log , TEXT("Hit Wrong Actor Check CollisionChannels"));
			return;
		}

		TSoftObjectPtr<UActorComponent> ActorVitalityComp = EnemyBase.Get()->FindComponentByClass(UActorVitalityComponent::StaticClass());
		if(!ActorVitalityComp.IsValid())
		{
			GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not finf ActorVitalityComponent Component in: %s") , *EnemyBase->GetName()));
			UE_LOG(LogTemp , Log , TEXT("Could not finf ActorVitalityComponent Component in: %s") , *EnemyBase->GetName());
			return;
		}
		
		TWeakInterfacePtr<IDamageable> DamageableComp = Cast<IDamageable>(ActorVitalityComp.Get());
		if(!DamageableComp.IsValid())
		{
			GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not find IDamageable Component in %s") , *ActorVitalityComp->GetName()));
			UE_LOG(LogTemp , Log , TEXT("Could not find IDamageable Component in: %s") , *EnemyBase->GetName());
			return;
		}

		DamageableComp->TakeDamage(WeaponDamage);
	}
	
	//Super::Use();
	if(UseSound != nullptr)
	{
		//UGameplayStatics::PlaySoundAtLocation(this , UseSound , Muzzle->GetComponentLocation());
	}
	/*
	if(OnWeaponShotDelegate.IsBound())
	{
		OnWeaponShotDelegate.Broadcast(TWeakObjectPtr<AWeaponFirearm>(this));
	}
	*/
	CurrentAmmo--;
}
