// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "UI/Widgets/UIMainMenu.h"

#include "Kismet/GameplayStatics.h"

void UUIMainMenu::OnStartButton_Pressed()
{
	UGameplayStatics::OpenLevel(this, FName("1STLevel_Sandbox"));
}

void UUIMainMenu::OnHighScoresButton_Pressed()
{
}

void UUIMainMenu::OnExitButton_Pressed()
{
	UKismetSystemLibrary::QuitGame(GetWorld() , GetWorld()->GetFirstPlayerController() , EQuitPreference::Quit, true);
}
