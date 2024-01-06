// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Actors/Enemy/EnemyBase.h"
// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	
	EnemyController = Cast<AEnemyController>(ThisController);
	if(!EnemyController.IsValid() || EnemyController == nullptr)
	{
		UE_LOG(LogTemp , Log, TEXT("Could not cast EnemyController"));
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , TEXT("Could not cast EnemyController"));
	}
	
	OnReachedDestHandle = EnemyController->OnStateChanged.AddUObject(this , &AEnemyBase::OnControllerStateChanged);

	TSoftObjectPtr<UActorComponent> VitalityComponent = FindComponentByClass<UActorVitalityComponent>();

	if(!VitalityComponent.IsValid())
	{
		UE_LOG(LogTemp , Log, TEXT("Could not find IDamageable Interface Component"));
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , TEXT("Could not find IDamageable Interface Component"));
		return;
	}
	
	TWeakInterfacePtr<IDamageable> DamageableInterface = Cast<IDamageable>(VitalityComponent.Get());
	if(!DamageableInterface.IsValid())
	{
		UE_LOG(LogTemp , Log, TEXT("Could not cast IDamageable Interface Component"));
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , TEXT("Could not cast IDamageable Interface Component"));
		return;
	}

	DamageableInterface.Get()->RegisterToDamageTaken(this);
}

void AEnemyBase::OnControllerStateChanged(FOnStateChangedData StateData)
{
	//UE_LOG(LogTemp , Log, TEXT("Attacking from: %s") , *GetName());
	//GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red ,  FString::Printf(TEXT("Attacking from: %s") ,*GetName()));

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
}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyBase::DamageTaken_Receiver()
{
	AnimInstance->CurrentTime = GetWorld()->GetTimeSeconds();
	AnimInstance->LastHitTime = GetWorld()->GetTimeSeconds();
	AnimInstance->IsHit = true;
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
}

