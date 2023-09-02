// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Usable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUsable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

UENUM()
enum class EItemType : uint8
{
	Firearm		UMETA(DisplayName = "Firearm"),
	NoType		UMETA(DisplayName = "NoType"),
};

class IUsable;
DECLARE_MULTICAST_DELEGATE_OneParam(FUsableItemUsed , const IUsable&)
class ZOMBHEADS_API IUsable
{
	GENERATED_BODY()
private:
	FUsableItemUsed ItemUsedDelegate;
	
public:
	virtual void Equip();
	virtual void DeEquip();
	virtual void Initialize();
	virtual void Use();

	virtual EItemType GetUsableType() const {return EItemType::NoType;}
	virtual FUsableItemUsed* GetUsableItemUsedDelegate() {return &ItemUsedDelegate;}
	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};


