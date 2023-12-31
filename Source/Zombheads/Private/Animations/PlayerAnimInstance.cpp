// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Animations/PlayerAnimInstance.h"

UPlayerAnimInstance::UPlayerAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{  
	//set any default values for your variables here
	ShotValue = 1.f;
	IsArmed = false;
	ShotSpeed = 1.f;
	WalkSpeedMultiplier = 1.f;
	RunSpeedMultiplier = 1.f;
}