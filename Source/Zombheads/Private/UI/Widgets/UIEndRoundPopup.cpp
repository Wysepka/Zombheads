// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "UI/Widgets/UIEndRoundPopup.h"

void UUIEndRoundPopup::RestartMap_Delayed()
{
	if (GetWorld())
	{
		FString CurrentLevelName = GetWorld()->GetMapName();
		CurrentLevelName = CurrentLevelName.Replace(TEXT("/Game/"), TEXT(""));
		UGameplayStatics::OpenLevel(this, FName(*CurrentLevelName));
	}
}

void UUIEndRoundPopup::OnRestartButtonPressed()
{
	if (GetWorld())
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UUIEndRoundPopup::RestartMap_Delayed, 3.0f, false);
	}
}

void UUIEndRoundPopup::OnMainMenuButtonPressed()
{
	UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}

void UUIEndRoundPopup::OnSubmitScoreButtonPressed()
{
	auto s = 's';
}

void UUIEndRoundPopup::OnExitButtonPressed()
{
	UWorld* World = GetWorld();
	if (World)
	{
		if (World->WorldType == EWorldType::PIE)
		{
			if (GEngine)
			{
				
			}
		}
		else
		{
			APlayerController* PlayerController = World->GetFirstPlayerController();
			if (PlayerController)
			{
				UKismetSystemLibrary::QuitGame(World, PlayerController, EQuitPreference::Quit, true);
			}
		}
	}
}
