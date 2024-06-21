// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Managers/GameModeFacade.h"

void AGameModeFacade::StartPlay()
{
	Super::StartPlay();

	LogClearerPtr = MakeUnique<LogClearer>();

	//Initialize all of Systems here
	if(OnAllSystemsInitialized.IsBound())
	{
		OnAllSystemsInitialized.Broadcast();
	}
	
}

void AGameModeFacade::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	LogClearerPtr.Get()->OnEndPlay();
	LogClearerPtr.Reset();
}