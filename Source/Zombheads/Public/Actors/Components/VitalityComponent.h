// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "VitalityComponent.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UVitalityComponent : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
inline UVitalityComponent::UVitalityComponent(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){}
class ZOMBHEADS_API IVitalityComponent
{
	GENERATED_BODY()

public:
	virtual bool HasStaminaToSprint() const = 0;
	virtual bool GetIfSprinting() const = 0;
	virtual float CurrentStaminaPercentage() const = 0;
	virtual float CurrentHealthPercentage() const = 0;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
