//Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated 
//documentation files(the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and 
//to permit persons to whom the Software is furnished to do so, subject to the following conditions

#include "Characters/PlayerPawn.h"

#include "Editor.h"
#include "Data/AnimationsPrimaryDataAsset.h"

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
/*	
#if WITH_EDITOR
	FEditorDelegates::EndPIE.AddUObject(this, &APlayerPawn::ExitingApplication);
#else
	FCoreDelegates::OnExit.AddUObject(this, &APlayerpa)	
#endif
*/	
}

void APlayerPawn::DisposeInventoryDelegates()
{
	if(PlayerInventory != nullptr && PlayerInventory->IsValid())
	{
		FChangedSlotDelegate* SlotDelegate = PlayerInventory->GetChangedSlotDelegate();
		if(SlotDelegate != nullptr)
		{
			if(SlotDelegate->IsBoundToObject(this))
			{
				SlotDelegate->Remove(ChangedSlotHandle);
			}
		}

		FInventoryItemUsedDelegate* InventoryItemUsedDelegate = PlayerInventory->GetInventoryItemUsedDelegate();
		if(InventoryItemUsedDelegate != nullptr)
		{
			if(InventoryItemUsedDelegate->IsBoundToObject(this))
			{
				InventoryItemUsedDelegate->Remove(InventoryUsedHandle);
			}
		}
	}
}

void APlayerPawn::BeginDestroy()
{
	if(bExitingApplication)
	{
		return;
	}
	
	Super::BeginDestroy();
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

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerPawn::SetupPlayerPawn(IPlayerInventory* PlayerInventoryOther)
{
	AActor* AssetLoaderInitializerActor = UGameplayStatics::GetActorOfClass(GetWorld() , AAssetLoaderInitializer::StaticClass());
	AAssetLoaderInitializer* AssetLoaderInitializer = Cast<AAssetLoaderInitializer>(AssetLoaderInitializerActor);
	auto animsInit = AssetLoaderInitializer->GetAssetLoader()->GetIfAnimationsDataInitialized();
	if(animsInit)
	{
		//AimMontage = AssetLoaderInitializer->GetAssetLoader()->GetAnimationsData()->GetPlayerAnimData()->GetAimMontage();
		AnimationsDataCallback(AssetLoaderInitializer->GetAssetLoader()->GetAnimationsData());
		//StartLoopingAnimation();
	} else
	{
		AssetLoaderInitializer->GetAssetLoader()->GetAnimationsDataDelegate()->AddUObject(this, &APlayerPawn::AnimationsDataCallback);
	}
	this->PlayerInventory = PlayerInventoryOther;
	ChangedSlotHandle = PlayerInventory->GetChangedSlotDelegate()->AddUObject(this, &APlayerPawn::HandleChangedSlotAnim);
	InventoryUsedHandle = PlayerInventory->GetInventoryItemUsedDelegate()->AddUObject(this, &APlayerPawn::HandleItemUsedAnim);

	//SkeletalMeshComponent->GetAnimInstance()
	//PlayerInventoryOther.
}

void APlayerPawn::DisposePlayerPawn()
{
	PlayerInventory = nullptr;
}

void APlayerPawn::GetInventorySceneContainers(UInventorySceneContainer*& Active, UInventorySceneContainer*& Disabled) {
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
	Active = ActiveInventoryContainer;
	Disabled = DisabledInventoryContainer;
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
	//StartLoopingAnimation();
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
	//UPlayerAnimInstance* AnimInstance = Cast<UPlayerAnimInstance>(SkeletalMeshComponent->GetAnimInstance());
	AnimInstance->ShotValue = 1.f;
}

//{ Animation Montages

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
//}
