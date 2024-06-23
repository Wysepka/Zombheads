#pragma once

#include "CoreMinimal.h"
#include "UIEndRoundPopup.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UIManager.generated.h"

UCLASS()
class ZOMBHEADS_API UUIManager : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly , Category = "UI" , meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUIEndRoundPopup> EndRoundPopup;

	TWeakObjectPtr<UUIEndRoundPopup> EndRoundPopupPtr;

	void OnEndOfRound();

public:
	virtual void NativeConstruct() override;
	void InitializeEndRoundPopup();
};