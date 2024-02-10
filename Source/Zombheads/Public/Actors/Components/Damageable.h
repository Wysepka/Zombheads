// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "VitalityComponent.h"
#include "Callbacks/DamageableReceiver.h"
#include "UObject/Interface.h"
#include "Damageable.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FActorTakenDamage , TWeakInterfacePtr<IVitalityComponent>);
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
inline UDamageable::UDamageable(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){}
class ZOMBHEADS_API IDamageable
{
	GENERATED_BODY()
protected:
	FActorTakenDamage TakenDamageDelegate;

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void TakeDamage(float value) = 0;
	virtual FDelegateHandle RegisterToDamageTaken(DamageableReceiver* DamageableReceiver) = 0;
	virtual void UnregisterToDamageTaken(FDelegateHandle RegisterHandle) = 0;
};
