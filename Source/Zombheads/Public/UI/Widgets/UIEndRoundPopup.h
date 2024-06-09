// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UIEndRoundPopup.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBHEADS_API UUIEndRoundPopup : public UUserWidget
{
	GENERATED_BODY()
	/*
	UPROPERTY(EditAnywhere)
	TObjectPtr<UButton> RestartButton;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UButton> MainMenuButton;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UButton> SubmitScoreButton;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UButton> ExitButton;
	*/

public:
	UFUNCTION(BlueprintCallable)
	void OnRestartButtonPressed();

	UFUNCTION(BlueprintCallable)
	void OnMainMenuButtonPressed();
	
	UFUNCTION(BlueprintCallable)
	void OnSubmitScoreButtonPressed();

	UFUNCTION(BlueprintCallable)
	void OnExitButtonPressed();
};
