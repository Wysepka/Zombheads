// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "UI/Widgets/UIManager.h"

#include "ComponentUtility.h"
#include "Utility/DebugUtility.h"
#include "Zombheads/ZombheadsGameModeBase.h"

void UUIManager::InitializeEndRoundPopup()
{
	if(!IsValid(EndRoundPopup))
	{
		LOG_MISSING_COMPONENT("EndRoundPopup variable in:%s is not valid! EndRoundPopupType:%s" , *this, *UUIEndRoundPopup::StaticClass()->GetName());
		return;
	}
	EndRoundPopupPtr = TWeakObjectPtr<UUIEndRoundPopup>(CreateWidget<UUIEndRoundPopup>(this, EndRoundPopup));
	if(EndRoundPopupPtr.IsValid())
	{
		EndRoundPopupPtr->AddToViewport();
		EndRoundPopupPtr->SetVisibility(ESlateVisibility::Hidden);
		TSoftObjectPtr<AZombheadsGameModeBase> GameMode = Cast<AZombheadsGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if(GameMode.IsValid())
		{
			GameMode->GetEndOfRound()->AddUObject(this, &UUIManager::OnEndOfRound);
		}
	}
}

void UUIManager::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeEndRoundPopup();
	
}

void UUIManager::OnEndOfRound()
{
	EndRoundPopupPtr->SetVisibility(ESlateVisibility::Visible);
}
