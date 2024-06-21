// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "UI/MainMenuInitializer.h"

#include "ComponentUtility.h"
#include "Player/DummyPlayerController.h"
#include "Utility/DebugUtility.h"

// Sets default values
AMainMenuInitializer::AMainMenuInitializer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainMenuInitializer::BeginPlay()
{
	Super::BeginPlay();

	if(!IsValid(UIMainMenu))
	{
		LOG_MISSING_COMPONENT("EndRoundPopup variable in:%s is not valid! EndRoundPopupType:%s" , *this, *UUIMainMenu::StaticClass()->GetName());
		return;
	}
	UIMainMenuPtr = TWeakObjectPtr<UUIMainMenu>(CreateWidget<UUIMainMenu>(GetWorld(), UIMainMenu));
	if(UIMainMenuPtr.IsValid())
	{
		UIMainMenuPtr->AddToViewport();
	}

	auto PlayerControllerDummy = ComponentUtility::FindActorOfType<ADummyPlayerController>(GetWorld());
	PlayerControllerDummy->InitMainMenuSettings();
}

// Called every frame
void AMainMenuInitializer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

