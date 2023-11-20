// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Player/CharacterMovement.h"

// Add default functionality here for any ICharacterMovement functions that are not pure virtual.

float ICharacterMovement::GetCharacterWalkSpeed() const
{
	UE_LOG(LogTemp , Log, TEXT("CharacterMovement method not implemented"))
	GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("ICharacterMovement not implemented")));
	return 0.f;
}

float ICharacterMovement::GetCharacterRunSpeed() const
{
	UE_LOG(LogTemp , Log, TEXT("CharacterMovement method not implemented"))
	GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("ICharacterMovement not implemented")));
	return 0.f;
}

float ICharacterMovement::GetCharacterMovementMagnitude() const
{
	UE_LOG(LogTemp , Log, TEXT("CharacterMovement method not implemented"))
	GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("ICharacterMovement not implemented")));
	return 0.f;
}

bool ICharacterMovement::GetIfCharacterSprinting() const
{
	UE_LOG(LogTemp , Log, TEXT("CharacterMovement method not implemented"))
	GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("ICharacterMovement not implemented")));
	return false;
}

