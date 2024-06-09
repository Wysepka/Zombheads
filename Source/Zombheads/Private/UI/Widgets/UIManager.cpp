// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "UI/Widgets/UIManager.h"

#include "Utility/DebugUtility.h"

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
	}
}

void UUIManager::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeEndRoundPopup();
	
}
