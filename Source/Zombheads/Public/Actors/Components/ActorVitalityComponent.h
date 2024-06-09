// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "Damageable.h"
#include "VitalityComponent.h"
#include "Components/ActorComponent.h"
#include "Data/PDA_Character.h"
#include "ActorVitalityComponent.generated.h"

UENUM()
enum class EActorType : uint8
{
	Invalid = 0		UMETA(DisplayName = "Invalid"),
	Player = 1		UMETA(DisplayName = "Player"),
	Zombie = 2		UMETA(DisplayName = "Zombie"),
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnActorDied, EActorType)
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBHEADS_API UActorVitalityComponent : public UActorComponent , public IVitalityComponent , public IDamageable
{
	GENERATED_BODY()

private:
	float MaxHealth;
	float CurrentHealth;
	float MaxStamina;
	float CurrentStamina;
	float StaminaDepletePerSec;
	float StaminaIncreasePerSec;

	bool bIsSprintingInput;
	bool bIsSprintingApplied;

	TSharedPtr<FOnActorDied> OnActorDied;

public:	
	// Sets default values for this component's properties
	UActorVitalityComponent();

	void BeginSprint();
	void EndSprint();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	void LoadData(EActorType ActorType, const TSoftObjectPtr<UPDA_Character>& CharData);
	virtual bool HasStaminaToSprint() const override;
	virtual bool GetIfSprinting() const override;
	virtual float CurrentStaminaPercentage() const override;
	virtual float CurrentHealthPercentage() const override;
	virtual void TakeDamage(float value) override;
	virtual FDelegateHandle RegisterToDamageTaken(DamageableReceiver* DamageableReceiver) override;
	virtual void UnregisterToDamageTaken(FDelegateHandle RegisterHandle) override;

	TSharedPtr<FOnActorDied> GetOnActorDiedDelegate();
};
