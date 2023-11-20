// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Data/InputDataAsset.h"

void UInputDataAsset::PrintNullMsg(FString ObjName) const
{
	UE_LOG(LogTemp , Log, TEXT("InputAction not assigned in blueprint editor: %s") , *ObjName);
	GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("AssetLoadedOverver not implemented")));
}

TWeakObjectPtr<UInputMappingContext> UInputDataAsset::GetPlayerMappingContext() const
{
	const auto RawPtr = PlayerInputMapping.Get();
	if(RawPtr != nullptr)
	{
		return  RawPtr;
	}
	else
	{
		PrintNullMsg(PlayerInputMapping.GetName());
		return nullptr;
	}
}

TWeakObjectPtr<UInputAction> UInputDataAsset::GetPlayerMoveForwardAction() const
{
	const auto RawPtr = PlayerMoveForwardAction.Get();
	if(RawPtr != nullptr)
	{
		return  RawPtr;
	}
	else
	{
		PrintNullMsg(PlayerMoveForwardAction.GetName());
		return nullptr;
	}
}

TWeakObjectPtr<UInputAction> UInputDataAsset::GetPlayerMoveBackwardAction() const
{
	const auto RawPtr = PlayerMoveBackwardAction.Get();
	if(RawPtr != nullptr)
	{
		return  RawPtr;
	}
	else
	{
		PrintNullMsg(PlayerMoveBackwardAction.GetName());
		return nullptr;
	}
}

TWeakObjectPtr<UInputAction> UInputDataAsset::GetPlayerMoveRightAction() const
{
	const auto RawPtr = PlayerMoveRightAction.Get();
	if(RawPtr != nullptr)
	{
		return  RawPtr;
	}
	else
	{
		PrintNullMsg(PlayerMoveRightAction.GetName());
		return nullptr;
	}
}

TWeakObjectPtr<UInputAction> UInputDataAsset::GetPlayerMoveLeftAction() const
{
	const auto RawPtr = PlayerMoveLeftAction.Get();
	if(RawPtr != nullptr)
	{
		return  RawPtr;
	}
	else
	{
		PrintNullMsg(PlayerMoveLeftAction.GetName());
		return nullptr;
	}
}

TWeakObjectPtr<UInputAction> UInputDataAsset::GetPlayerSlot1Action() const
{
	const auto RawPtr = PlayerSlot1Action.Get();
	if(RawPtr != nullptr)
	{
		return  RawPtr;
	}
	else
	{
		PrintNullMsg(PlayerSlot1Action.GetName());
		return nullptr;
	}
}

TWeakObjectPtr<UInputAction> UInputDataAsset::GetPlayerSlot2Action() const
{
	const auto RawPtr = PlayerSlot2Action.Get();
	if(RawPtr != nullptr)
	{
		return  RawPtr;
	}
	else
	{
		PrintNullMsg(PlayerSlot2Action.GetName());
		return nullptr;
	}
}

TWeakObjectPtr<UInputAction> UInputDataAsset::GetPlayerSprintAction() const
{
	const auto RawPtr = PlayerSprintAction.Get();
	if(RawPtr != nullptr)
	{
		return  RawPtr;
	}
	else
	{
		PrintNullMsg(PlayerSprintAction.GetName());
		return nullptr;
	}
}

TWeakObjectPtr<UInputAction> UInputDataAsset::GetPlayerUseAction() const
{
	const auto RawPtr = PlayerUseAction.Get();
	if(RawPtr != nullptr)
	{
		return  RawPtr;
	}
	else
	{
		PrintNullMsg(PlayerUseAction.GetName());
		return nullptr;
	}
}

