// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterMovement.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCharacterMovement : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZOMBHEADS_API ICharacterMovement
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float GetCharacterWalkSpeed() const;
	virtual float GetCharacterRunSpeed() const;
	virtual float GetCharacterMovementMagnitude() const;
	virtual bool GetIfCharacterSprinting() const;
public:
};
