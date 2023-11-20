// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Engine/DataAsset.h"
#include "InputDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBHEADS_API UInputDataAsset : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly  , Category = "EnhancedInput" , meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> PlayerInputMapping;

	UPROPERTY(EditDefaultsOnly  , Category = "EnhancedInput" , meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PlayerMoveForwardAction;

	UPROPERTY(EditDefaultsOnly  , Category = "EnhancedInput" , meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PlayerMoveBackwardAction;
	
	UPROPERTY(EditDefaultsOnly  , Category = "EnhancedInput" , meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PlayerMoveRightAction;

	UPROPERTY(EditDefaultsOnly  , Category = "EnhancedInput" , meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PlayerMoveLeftAction;
	
	UPROPERTY(EditDefaultsOnly  , Category = "EnhancedInput" , meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PlayerSlot1Action;
	
	UPROPERTY(EditDefaultsOnly  , Category = "EnhancedInput" , meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PlayerSlot2Action;
	
	UPROPERTY(EditDefaultsOnly  , Category = "EnhancedInput" , meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PlayerSprintAction;
	
	UPROPERTY(EditDefaultsOnly  , Category = "EnhancedInput" , meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PlayerUseAction;

	void PrintNullMsg(FString ObjName) const;
	
public:
	TWeakObjectPtr<UInputMappingContext> GetPlayerMappingContext() const;

	TWeakObjectPtr<UInputAction> GetPlayerMoveForwardAction() const;
	TWeakObjectPtr<UInputAction> GetPlayerMoveBackwardAction() const;
	TWeakObjectPtr<UInputAction> GetPlayerMoveRightAction() const;
	TWeakObjectPtr<UInputAction> GetPlayerMoveLeftAction() const;
	TWeakObjectPtr<UInputAction> GetPlayerSlot1Action() const;
	TWeakObjectPtr<UInputAction> GetPlayerSlot2Action() const;
	TWeakObjectPtr<UInputAction> GetPlayerSprintAction() const;
	TWeakObjectPtr<UInputAction> GetPlayerUseAction() const;
	
};
