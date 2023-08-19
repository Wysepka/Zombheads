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
	if(EnemyController == nullptr)
	{
		UE_LOG(LogTemp , Log, TEXT("Could not cast EnemyController"));
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , TEXT("Could not cast EnemyController"));
	}
	
	OnReachedDestHandle = EnemyController->OnReachedTarget.AddUObject(this , &AEnemyBase::Attack);
}

void AEnemyBase::Attack()
{
	UE_LOG(LogTemp , Log, TEXT("Attacking from: %s") , *GetName());
	GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red ,  FString::Printf(TEXT("Attacking from: %s") ,*GetName()));
}

void AEnemyBase::BeginDestroy()
{
	Super::BeginDestroy();
	if(EnemyController != nullptr)
	{
		EnemyController->OnReachedTarget.Remove(OnReachedDestHandle);
	}
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

