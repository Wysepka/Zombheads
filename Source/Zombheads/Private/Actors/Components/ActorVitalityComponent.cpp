// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Actors/Components/ActorVitalityComponent.h"

#include "Characters/PlayerPawn.h"
#include "Utility/DebugUtility.h"

void UActorVitalityComponent::BeginSprint()
{
	if(HasStaminaToSprint())
	{
		bIsSprintingInput = true;
	}
}

void UActorVitalityComponent::EndSprint()
{
	bIsSprintingInput = false;
}

// Sets default values for this component's properties
UActorVitalityComponent::UActorVitalityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActorVitalityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UActorVitalityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bIsSprintingInput)
	{
		if(HasStaminaToSprint())
		{
			CurrentStamina -= StaminaDepletePerSec * DeltaTime;
			bIsSprintingApplied = true;
		}
		else
		{
			bIsSprintingApplied = false;
		}
	}
	else
	{
		bIsSprintingApplied = false;
	}

	if(!bIsSprintingApplied)
	{
		if(CurrentStamina <= MaxStamina)
		{
			CurrentStamina += StaminaIncreasePerSec * DeltaTime;
		}
	}
	// ...
}

void UActorVitalityComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if(this != nullptr)
	{
		FInputActionBinding ActionBindingBS = PlayerInputComponent->BindAction("Sprint" , IE_Pressed , this, &UActorVitalityComponent::BeginSprint);
		FInputActionBinding ActionBindingBE = PlayerInputComponent->BindAction("Sprint" , IE_Released  , this, &UActorVitalityComponent::EndSprint);
	}
}

void UActorVitalityComponent::LoadData(EActorType ActorTypeArg, const TSoftObjectPtr<UPDA_Character>& CharData)
{
	this->ActorType = ActorTypeArg;
	if(ActorTypeArg == EActorType::Player)
	{
		MaxHealth = CharData.Get()->GetCharacterMaxHealth();
		CurrentHealth = MaxHealth;
		MaxStamina = CharData.Get()->GetCharacterMaxStamina();
		CurrentStamina = MaxStamina;
		StaminaDepletePerSec = CharData.Get()->GetCharacterStaminaDepletePerSec();
		StaminaIncreasePerSec = CharData.Get()->GetCharacterStaminaIncreasePerSec();
	} else if(ActorTypeArg == EActorType::Zombie)
	{
		MaxHealth = CharData.Get()->GetZombieMaxHealth();
		CurrentHealth = MaxHealth;
	}
	else
	{
		LOG_MISSING_COMPONENT("Invalid Actor Type in %s, define new type of Actor in %s" ,*this, *UActorVitalityComponent::GetName());
	}
}

bool UActorVitalityComponent::HasStaminaToSprint() const
{
	return CurrentStamina > 0;
}

bool UActorVitalityComponent::GetIfSprinting() const
{
	return bIsSprintingApplied;
}

float UActorVitalityComponent::CurrentStaminaPercentage() const
{
	return CurrentStamina / MaxStamina;
}

float UActorVitalityComponent::CurrentHealthPercentage() const
{
	return CurrentHealth / MaxHealth; 
}

void UActorVitalityComponent::TakeDamage(float value)
{
	CurrentHealth -= value;
	
	if(TakenDamageDelegate.IsBound())
	{
		TakenDamageDelegate.Broadcast(TWeakInterfacePtr<IVitalityComponent>(this));
	}
	if(CurrentHealth <= 0)
	{
		if(OnActorDied.IsValid() && OnActorDied->IsBound())
		{
			OnActorDied->Broadcast(ActorType);
		}
	}
}

FDelegateHandle UActorVitalityComponent::RegisterToDamageTaken(DamageableReceiver* DamageableReceiver)
{
	return TakenDamageDelegate.AddRaw(DamageableReceiver , &DamageableReceiver::DamageTaken_Receiver);
}

void UActorVitalityComponent::UnregisterToDamageTaken(FDelegateHandle RegisterHandle)
{
	TakenDamageDelegate.Remove(RegisterHandle);
}

TSharedPtr<FOnActorDied> UActorVitalityComponent::GetOnActorDied()
{
	if(!OnActorDied.IsValid())
	{
		OnActorDied = MakeShareable(new FOnActorDied);
	}
	return OnActorDied;
}

