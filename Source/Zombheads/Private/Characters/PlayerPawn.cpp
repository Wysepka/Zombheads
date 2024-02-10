//Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated 
//documentation files(the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and 
//to permit persons to whom the Software is furnished to do so, subject to the following conditions

#include "Characters/PlayerPawn.h"

#include "Data/AnimationsPrimaryDataAsset.h"
#include "Player/PlayerCharacterWrapper.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	FCoreDelegates::OnExit.AddUObject(this, &APlayerPawn::ExitingApplication);
}

void APlayerPawn::DisposeInventoryDelegates()
{
	if(PlayerInventory != nullptr && PlayerInventory.IsValid())
	{
		IPlayerInventory* InvPin = PlayerInventory.Pin().Get();

		if(InvPin != nullptr)
		{
			FChangedSlotDelegate* SlotDelegate =InvPin->GetChangedSlotDelegate();
			if(SlotDelegate != nullptr)
			{
				if(SlotDelegate->IsBoundToObject(this))
				{
					SlotDelegate->Remove(ChangedSlotHandle);
				}
			}
			FInventoryItemUsedDelegate* InventoryItemUsedDelegate = InvPin->GetInventoryItemUsedDelegate();
			if(InventoryItemUsedDelegate != nullptr)
			{
				if(InventoryItemUsedDelegate->IsBoundToObject(this))
				{
					InventoryItemUsedDelegate->Remove(InventoryUsedHandle);
				}
			}
		}
	}
}

void APlayerPawn::BeginDestroy()
{
	Super::BeginDestroy();
	if(bExitingApplication)
	{
		return;
	}
	
	DisposeInventoryDelegates();
}

void APlayerPawn::ExitingApplication(bool ExitingPlayMode)
{
	this->bExitingApplication = ExitingPlayMode;
}

void APlayerPawn::ExitingApplication()
{
	this->bExitingApplication = true;
}

void APlayerPawn::InvokePlayerPivotDelegate()
{
	if(PlayerPawnInitializedDelegate.IsBound())
	{
		PlayerPawnInitializedDelegate.Broadcast(GetPlayerPivot());
	}
}


// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CharacterMovement.IsValid())
	{
		const bool IsSprinting = CharacterMovement.Get()->GetIfCharacterSprinting();
		const float MovementMagnitude = CharacterMovement.Get()->GetCharacterMovementMagnitude();

		AnimInstance->IsWalking = !FMath::IsNearlyZero(MovementMagnitude);
		AnimInstance->IsRunning = IsSprinting && !FMath::IsNearlyZero(MovementMagnitude);
		
	/*
	if(AnimInstance->IsWalking != ! IsSprinting)
	{
		AnimInstance->IsWalking = FMath::IsNearlyZero(MovementMagnitude);
	}
	if(AnimInstance->IsRunning != IsSprinting)
	{
		AnimInstance->IsRunning = IsSprinting && FMath::IsNearlyZero(MovementMagnitude);
	}
	*/
		AnimInstance->WalkSpeedMultiplier = MovementMagnitude * CharacterMovement.Get()->GetCharacterWalkSpeed();
		AnimInstance->RunSpeedMultiplier = MovementMagnitude * CharacterMovement.Get()->GetCharacterRunSpeed();
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerCharacterWrapper* CharWrapper = Cast<APlayerCharacterWrapper>(GetController());

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(CharWrapper->GetLocalPlayer());
	InputSubsystem->AddMappingContext(PlayerInputData->GetPlayerMappingContext().Get() , 0);

	if(GetVitalityComponent().Get() != nullptr)
	{
		UEnhancedInputComponent* Eic = Cast<UEnhancedInputComponent>(PlayerInputComponent);
		Eic->BindAction(PlayerInputData->GetPlayerSprintAction().Get() , ETriggerEvent::Triggered , GetVitalityComponent_Internal().Get() , &UActorVitalityComponent::BeginSprint);
		Eic->BindAction(PlayerInputData->GetPlayerSprintAction().Get() , ETriggerEvent::Completed , GetVitalityComponent_Internal().Get() , &UActorVitalityComponent::EndSprint);
	}
}

void APlayerPawn::SetupPlayerPawn(const TSharedPtr<IPlayerInventory>& PlayerInventoryOther ,const TWeakInterfacePtr<ICharacterMovement>& CharacterMovementOther)
{
	AActor* AssetLoaderInitializerActor = UGameplayStatics::GetActorOfClass(GetWorld() , AAssetLoaderInitializer::StaticClass());
	AAssetLoaderInitializer* AssetLoaderInitializer = Cast<AAssetLoaderInitializer>(AssetLoaderInitializerActor);
	TWeakObjectPtr<UAssetLoader> AssetLoaderPin = AssetLoaderInitializer->GetAssetLoader();

	auto animsInit = AssetLoaderPin.Get()->GetIfAnimationsDataInitialized();
	if(animsInit)
	{
		//AimMontage = AssetLoaderInitializer->GetAssetLoader()->GetAnimationsData()->GetPlayerAnimData()->GetAimMontage();
		AnimationsDataCallback(AssetLoaderInitializer->GetAssetLoader()->GetAnimationsData());
		//StartLoopingAnimation();
	} else
	{
		AssetLoaderInitializer->GetAssetLoader()->GetAnimationsDataDelegate()->AddUObject(this, &APlayerPawn::AnimationsDataCallback);
	}
	
	InitializeCharacterData(AssetLoaderPin.Get());

	//Not checking if Inventory is destroyed due to calling it in BeginPlay
	ChangedSlotHandle = PlayerInventoryOther.Get()->GetChangedSlotDelegate()->AddUObject(this, &APlayerPawn::HandleChangedSlotAnim);
	InventoryUsedHandle = PlayerInventoryOther.Get()->GetInventoryItemUsedDelegate()->AddUObject(this, &APlayerPawn::HandleItemUsedAnim);
	this->CharacterMovement = CharacterMovementOther;
	this->PlayerInventory = PlayerInventoryOther;
	//SkeletalMeshComponent->GetAnimInstance()
	//PlayerInventoryOther.
}

void APlayerPawn::InitializeCharacterData(UAssetLoader* AssetLoaderPin)
{
	UPDA_Character* CharData;

	if(AssetLoaderPin != nullptr)
	{
		const auto charInit = AssetLoaderPin->GetPrimaryDataAsset<UPDA_Character>(this,CharData);
		if(charInit.Key)
		{
			PrimaryDataAssetLoaded(CharData);
		}
	}
}

void APlayerPawn::DisposePlayerPawn()
{
	PlayerInventory = nullptr;
	CharacterMovement = nullptr;
}

void APlayerPawn::GetInventorySceneContainers(TWeakObjectPtr<UInventorySceneContainer>& Active, TWeakObjectPtr<UInventorySceneContainer>& Disabled) {
	if (!bInventorySceneContainersFetched) {
		TArray<AActor*> Childs;
		GetAttachedActors(Childs, true, true);

		TArray<UActorComponent*> Components = GetComponentsByClass(UInventorySceneContainer::StaticClass());
		for (size_t i = 0; i < Components.Num(); i++)
		{
			UInventorySceneContainer* Container = Cast<UInventorySceneContainer>(Components[i]);
			if (Container != nullptr) {
				if (Container->GetContainerType() == EInventoryContainerType::Active) {
					ActiveInventoryContainer = Container;
				}
				else if (Container->GetContainerType() == EInventoryContainerType::Disabled) {
					DisabledInventoryContainer = Container;
				}
			}
		}
		bInventorySceneContainersFetched = true;
	}
	Active = ActiveInventoryContainer.Get();
	Disabled = DisabledInventoryContainer.Get();

	//TArray<UInventorySceneContainer*> Containers = { ActiveInventoryContainer, DisabledInventoryContainer };
	//return Containers;
}

USceneComponent* APlayerPawn::GetPlayerPivot() const
{
	GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , TEXT("Accessigng Pawn Pivot"));
	return this->PawnPivot;
}

FPlayerPivotInitialized* APlayerPawn::GetPlayerPivotInitializedDelegate()
{
	return &PlayerPawnInitializedDelegate;
}

TSoftObjectPtr<UActorVitalityComponent> APlayerPawn::GetVitalityComponent_Internal()
{
	if(!VitalityComponent)
	{
		VitalityComponent = FindComponentByClass<UActorVitalityComponent>();
	}
	return VitalityComponent;
}

TWeakInterfacePtr<IVitalityComponent> APlayerPawn::GetVitalityComponent()
{
	if(!VitalityComponentInterface.IsValid())
	{
		VitalityComponentInterface = Cast<IVitalityComponent>(GetVitalityComponent_Internal().Get());
	}
	return VitalityComponentInterface;
}

void APlayerPawn::SetSkeletalMeshComponent_CPP(USkeletalMeshComponent* SkeletelMeshComp)
{
	this->SkeletalMeshComponent = SkeletelMeshComp;
	AnimInstance = Cast<UPlayerAnimInstance>(SkeletalMeshComponent->GetAnimInstance());
	AnimBlueprint = Cast<UAnimBlueprint>(SkeletalMeshComponent->GetAnimInstance());
}

void APlayerPawn::AnimationsDataCallback(UAnimationsPrimaryDataAsset* AnimationsData)
{
	AimMontage = AnimationsData->GetPlayerAnimData()->GetAimMontage();
	ShotMontage = AnimationsData->GetPlayerAnimData()->GetShotMontage();
}

void APlayerPawn::PrimaryDataAssetLoaded(UPDA_Character* Data)
{
	const auto VitCompPin = GetVitalityComponent_Internal().Get();
	if(VitCompPin != nullptr)
	{
		VitCompPin->LoadData(EActorType::Player, TSoftObjectPtr<UPDA_Character>(Data));
	}
}

void APlayerPawn::HandleChangedSlotAnim(int CurrentSlot)
{
	if(CurrentSlot <= 0)
	{
		//StopAnimationMontage(FString("Aim"));
		AnimInstance->IsArmed = false;
	}
	else
	{
		//StartAnimationMontage(FString("Aim"));
		AnimInstance->IsArmed = true;
	}
}

void APlayerPawn::HandleItemUsedAnim(const IUsable& WeaponBase)
{
	if(WeaponBase.GetUsableType() == EItemType::Firearm)
	{
		//StartAnimationMontage(FString("Shot"));
		//AnimBlueprint
		AnimInstance->ShotValue = 100.f;
	}
}

void APlayerPawn::OnWeaponShotAnimEvent()
{
	AnimInstance->ShotValue = 1.f;
}

void APlayerPawn::StartAnimationMontage(const FString& MontageID)
{
	if(MontageID == "Aim")
	{
		PlayLoopingAnimation(MontageID);
	}
	else if(MontageID == "Shot")
	{
		if(!bIsSingleMontagePlaying)
		{
			//StopAnimationMontage("Aim");
			PlaySingleAnimationMontage(MontageID);
		}
	}
}

void APlayerPawn::StopAnimationMontage(const FString& MontageID)
{
	if(MontageID == "Aim")
	{
		SkeletalMeshComponent->GetAnimInstance()->Montage_Stop(0.f , AimMontage);
		//SkeletalMeshComponent->GetAnimInstance().mont
		GetWorldTimerManager().ClearTimer(LoopingAnimationTimerHandle);
	}
}

void APlayerPawn::PlayLoopingAnimation(const FString& MontageID)
{
	FTimerDelegate TimerDelegate;
	if (AimMontage)
	{
		SkeletalMeshComponent->GetAnimInstance()->Montage_Play(AimMontage);
		// Call PlayLoopingAnimation again after the montage duration
		const float MontageDuration = AimMontage->GetPlayLength();
		TimerDelegate.BindLambda([=]()
		{
			PlayLoopingAnimation(MontageID);
		});
		GetWorldTimerManager().SetTimer(LoopingAnimationTimerHandle, TimerDelegate, MontageDuration, false);
	}
}

void APlayerPawn::PlaySingleAnimationMontage(const FString& MontageID)
{
	FTimerDelegate TimerDelegate;
	float MontageDuration;
	if(MontageID == "Shot")
	{
		MontageDuration = ShotMontage->GetPlayLength();
		TimerDelegate.BindLambda([=]()
		{
			EndOfSingleAnimMontage(MontageID);
		});
		SkeletalMeshComponent->GetAnimInstance()->Montage_Play(ShotMontage);
		bIsSingleMontagePlaying = true;
	}
	GetWorldTimerManager().SetTimer(SingleAnimationTimerHandle , TimerDelegate , MontageDuration , false);
}

void APlayerPawn::EndOfSingleAnimMontage(const FString& MontageID)
{
	if(MontageID == "Shot")
	{
		bIsSingleMontagePlaying = false;
		StartAnimationMontage(FString("Aim"));
	}
}