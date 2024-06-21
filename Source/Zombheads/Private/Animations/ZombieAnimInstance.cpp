// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Animations/ZombieAnimInstance.h"

UZombieAnimInstance::UZombieAnimInstance(const FObjectInitializer& ObjectInitializer)
	: UEnemyAnimInstance(ObjectInitializer)
{  
	//set any default values for your variables here
	IsWalking = false;
	IsAttacking = false;
}

void UZombieAnimInstance::OnHitPerformed()
{
	if(OnEnemyHitPerformed->IsBound())
	{
		OnEnemyHitPerformed->Broadcast();
	}
}

TSharedPtr<FOnEnemyHitPerformed> UZombieAnimInstance::GetEnemyHitPerformedDelegate()
{
	if(!OnEnemyHitPerformed.IsValid())
	{
		OnEnemyHitPerformed = MakeShareable(new FOnEnemyHitPerformed);
	}
	return OnEnemyHitPerformed;
}
