// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Player/Inventory/Weapons/WeaponFirearm.h"

void AWeaponFirearm::Use()
{
	if(Muzzle == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , TEXT("Muzzle Component is not set in Blueprint"));
		UE_LOG(LogTemp , Log , TEXT("Muzzle Component is not set in Blueprint"));
		return;
	}
	//Super::Use();
	if(UseSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this , UseSound , Muzzle->GetComponentLocation());
	}
}
