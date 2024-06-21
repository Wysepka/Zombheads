// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Widgets/UIMainMenu.h"
#include "MainMenuInitializer.generated.h"

UCLASS()
class ZOMBHEADS_API AMainMenuInitializer : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "UI" , meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUIMainMenu> UIMainMenu;

	TWeakObjectPtr<UUIMainMenu> UIMainMenuPtr;
	
public:	
	// Sets default values for this actor's properties
	AMainMenuInitializer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
