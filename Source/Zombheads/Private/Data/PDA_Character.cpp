// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Data/PDA_Character.h"

float UPDA_Character::GetPlayerWalkingSpeed() const
{
	return PlayerWalkingSpeed;
}

float UPDA_Character::GetPlayerRunningSpeed() const
{
	return PlayerRunningSpeed;
}

float UPDA_Character::GetCharacterMaxHealth() const
{
	return MaxHealth;
}

float UPDA_Character::GetCharacterMaxStamina() const
{
	return MaxStamina;
}

float UPDA_Character::GetCharacterStaminaDepletePerSec() const
{
	return StaminaDepletePerSec;
}

float UPDA_Character::GetCharacterStaminaIncreasePerSec() const
{
	return StaminaIncreasePerSec;
}
