// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Actors/Enemy/EnemyBase.h"

#include "ComponentUtility.h"
#include "Components/CapsuleComponent.h"
#include "Player/Camera/TPSCameraActor.h"
#include "Utility/ActorUtility.h"
#include "Utility/DebugUtility.h"
// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyBase::GetDamageableComponent(TSoftObjectPtr<UActorComponent> VitalityComponent)
{
	TWeakInterfacePtr<IDamageable> DamageableInterface = Cast<IDamageable>(VitalityComponent.Get());
	TSoftObjectPtr<UActorVitalityComponent> ActorVitalityComponent = Cast<UActorVitalityComponent>(VitalityComponent.Get());
	
	if(!DamageableInterface.IsValid())
	{
		UE_LOG(LogTemp , Log, TEXT("Could not cast IDamageable Interface Component"));
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , TEXT("Could not cast IDamageable Interface Component"));
		return;
	}

	DamageableInterface.Get()->RegisterToDamageTaken(this);
}

void AEnemyBase::GetVitalityComponent(TSoftObjectPtr<UActorComponent>& VitalityComponent)
{
	VitalityComponent = FindComponentByClass<UActorVitalityComponent>();

	if(!VitalityComponent.IsValid())
	{
		UE_LOG(LogTemp , Log, TEXT("Could not find IDamageable Interface Component"));
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , TEXT("Could not find IDamageable Interface Component"));
		return;
	}
}

void AEnemyBase::GetCapsuleComponent()
{
	CapsuleCompPtr = FindComponentByClass<UCapsuleComponent>();
	if(!CapsuleCompPtr.IsValid())
	{
		LOG_MISSING_COMPONENT("Could not find CapsuleComponent in: %s" , *this, *this->GetName());
		return;
	}
}

int32 AEnemyBase::GetKillingPoints()
{
	return KillingPoints;
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	AController* ThisController =  GetController();
	if(ThisController == nullptr)
	{
		UE_LOG(LogTemp , Log, TEXT("Could not find Controller for: %s") , *GetName());
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not find Controller for: %s") , *GetName()));
	}

	AActor* AssetLoaderInitializerActor = UGameplayStatics::GetActorOfClass(GetWorld() , AAssetLoaderInitializer::StaticClass());
	AAssetLoaderInitializer* AssetLoaderInitializer = Cast<AAssetLoaderInitializer>(AssetLoaderInitializerActor);
	TWeakObjectPtr<UAssetLoader> AssetLoaderPin = AssetLoaderInitializer->GetAssetLoader();
	if(!AssetLoaderPin.IsValid())
	{
		auto result = AssetLoaderPin.IsValid();
		AssetLoaderInitializer->GetAssetLoader();
		LOG_MISSING_COMPONENT("Could not find AssetLoader in %s" , *this , *this->GetName() , NULL);
	}
	else
	{
		auto CharDataTuple = AssetLoaderPin.Get()->GetPrimaryDataAsset<UPDA_Character>(this, CharData);
		if(CharDataTuple.Key)
		{
			PrimaryDataAssetLoaded(CharData);
		}
	}
	
	EnemyController = Cast<AEnemyController>(ThisController);
	if(!EnemyController.IsValid() || EnemyController == nullptr)
	{
		UE_LOG(LogTemp , Log, TEXT("Could not cast EnemyController"));
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , TEXT("Could not cast EnemyController"));
	}
	
	OnReachedDestHandle = EnemyController->OnStateChanged.AddUObject(this , &AEnemyBase::OnControllerStateChanged);

	TSoftObjectPtr<UActorComponent> VitalityComponent;
	
	GetVitalityComponent(VitalityComponent);

	if(VitalityComponent.IsValid())
	{
		GetDamageableComponent(VitalityComponent);
	}

	GetCapsuleComponent();

	auto CameraClass = ComponentUtility::FindActorOfType<ATPSCameraActor>(GetWorld());
	CameraComponent = ComponentUtility::FindComponentOfType<UCameraComponent>(CameraClass.Get());
	if(!CameraComponent.IsValid())
	{
		LOG_MISSING_COMPONENT("Missing Camera Component In EnemyBase" , this);
	}
}

void AEnemyBase::OnControllerStateChanged(FOnStateChangedData StateData)
{
	//UE_LOG(LogTemp , Log, TEXT("Attacking from: %s") , *GetName());
	//GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red ,  FString::Printf(TEXT("Attacking from: %s") ,*GetName()));

	if(IsDead)
	{
		return;
	}
	switch (StateData.GetState())
	{
	case ATTACKING:
		AnimInstance.Get()->IsAttacking = true;
		AnimInstance.Get()->IsWalking = false;
		break;
	case TOWARD_TARGET:
		AnimInstance.Get()->IsAttacking = false;
		AnimInstance.Get()->IsWalking = true;
		break;
	case IDLE:
		AnimInstance.Get()->IsAttacking = false;
		AnimInstance.Get()->IsWalking = false;
		break;
	default:
		break;
	}
}

void AEnemyBase::BeginDestroy()
{
	Super::BeginDestroy();
	if(EnemyController != nullptr)
	{
		EnemyController->OnStateChanged.Remove(OnReachedDestHandle);
	}
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(AnimInstance->IsHit)
	{
		float CurrentSeconds = GetWorld()->GetTimeSeconds();
		float SeqLength = AnimInstance->HitSequence->GetPlayLength();
		if(CurrentSeconds - AnimInstance->LastHitTime > SeqLength)
		{
			AnimInstance->IsHit = false;
		}
		else
		{
			AnimInstance->CurrentTime = GetWorld()->GetTimeSeconds();
		}
	}

	if(IsDead && IsValid(EnemyMesh) && CameraComponent.IsValid() && IsValid(this))
	{
		if(!IsBeingDestroyed)
		{
			GetWorld()->GetTimerManager().SetTimer(DestroyHandle , this, &AEnemyBase::DelayedDestroy , 20.f , false);
			IsBeingDestroyed = true;
		}
	}
}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyBase::DamageTaken_Receiver(TWeakInterfacePtr<IVitalityComponent> VitalityComponent)
{
	AnimInstance->CurrentTime = GetWorld()->GetTimeSeconds();
	AnimInstance->LastHitTime = GetWorld()->GetTimeSeconds();
	AnimInstance->IsHit = true;
	if(!VitalityComponent.IsValid())
	{
		UE_LOG(LogTemp , Log , TEXT("Vitality Component received on: %s is null !") , *EnemyMesh.GetName());
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Vitality Component received on: %s is null !") ,*EnemyMesh.GetName()));
		return;
	}
	float value = VitalityComponent.Get()->CurrentHealthPercentage();
	DynamicEnemyMaterial->SetScalarParameterValue(FName("HealthOverlayOpacity") , 1.f - value);

	if(VitalityComponent->CurrentHealthPercentage() <= 0.f)
	{
		IsDead = true;
		AnimInstance.Get()->IsDead = true;
		Controller.Get()->StopMovement();
		EnemyController.Get()->Disable();
		CapsuleCompPtr.Get()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CapsuleCompPtr.Get()->Deactivate();

		if(OnActorDied.IsBound())
		{
			OnActorDied.Broadcast(TWeakObjectPtr<AEnemyBase>(this));
		}
	}
}

bool AEnemyBase::GetIsDead()
{
	return IsDead;
}

void AEnemyBase::AssignSkeletalMesh_Blueprint(USkeletalMeshComponent* SkeletalMeshComponent)
{
	EnemyMesh = SkeletalMeshComponent;
	auto AnimInstanceRaw = EnemyMesh.Get()->GetAnimInstance();
	if(AnimInstanceRaw == nullptr)
	{
		UE_LOG(LogTemp , Log , TEXT("Could not find AnimInstance on: %s") , *EnemyMesh.GetName());
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not find AnimInstance on: %s") ,*EnemyMesh.GetName()));
		return;
	}
	AnimInstance = Cast<UEnemyAnimInstance>(AnimInstanceRaw);
	AnimInstance.Get()->GetEnemyHitPerformedDelegate()->AddUObject(this, &AEnemyBase::OnEnemyAnimHitPerformed);
	TSoftObjectPtr<UMaterialInterface> EnemyMaterial = EnemyMesh.Get()->GetMaterial(0);
	if(!EnemyMaterial.IsValid())
	{
		UE_LOG(LogTemp , Log , TEXT("Could not find Material on: %s") , *EnemyMesh.GetName());
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not find Material on: %s") ,*EnemyMesh.GetName()));
		return;
	}

	DynamicEnemyMaterial = UMaterialInstanceDynamic::Create(EnemyMaterial.Get(), this);
	DynamicEnemyMaterial.Get()->SetScalarParameterValue(FName("NoiseOffset") , FMath::FRand());
	EnemyMesh->SetMaterial(0 ,DynamicEnemyMaterial.Get());
}

void AEnemyBase::LoadVitalityData(TSoftObjectPtr<UActorVitalityComponent> VitalityComponent)
{
	
}

EActorType AEnemyBase::GetActorType()
{
	return EActorType::Invalid;
}

void AEnemyBase::PrimaryDataAssetLoaded(UPDA_Character* Data)
{
	CharData = Data;
	const TSoftObjectPtr<UActorVitalityComponent> VitalityComponent = FindComponentByClass<UActorVitalityComponent>();
	if(!VitalityComponent.IsValid())
	{
		LOG_MISSING_COMPONENT("Missing Component: %hs in %s" ,this, typeid(UActorVitalityComponent).name() , *this->GetName());
		return;
	}
	KillingPoints = CharData->GetEnemyKillingPoints(EnemyType);
	DamagePoints = CharData->GetEnemyHitDamage(EnemyType);
	LoadVitalityData(VitalityComponent);
}

void AEnemyBase::OnEnemyAnimHitPerformed()
{
	EnemyController->GetTargetPlayerPawn()->GetDamegeableComponent()->TakeDamage(DamagePoints);
}

void AEnemyBase::DelayedDestroy()
{
	
	K2_DestroyActor();
}

