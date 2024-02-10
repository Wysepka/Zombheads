// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class ZOMBHEADS_API DebugUtility
{
public:
	DebugUtility();
	~DebugUtility();
};

#define LOG_MISSING_COMPONENT(Description, Object, ...) \
do { \
FString FormattedMessage = FString::Printf(TEXT(Description), ##__VA_ARGS__); \
FString FullMessage = FString::Printf(TEXT("%s:%d - %s"), TEXT(__FILE__), __LINE__, *FormattedMessage); \
GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("%s in %s"), *FullMessage, *Object->GetName())); \
UE_LOG(LogTemp, Log, TEXT("%s in: %s"), *FullMessage, *Object->GetName()); \
} while (false)
