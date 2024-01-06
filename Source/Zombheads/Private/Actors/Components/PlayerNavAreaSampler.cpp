// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Actors/Components/PlayerNavAreaSampler.h"

#include "NavigationSystem.h"
#include "Characters/PlayerPawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPlayerNavAreaSampler::UPlayerNavAreaSampler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerNavAreaSampler::BeginPlay()
{
	Super::BeginPlay();
	NavMesh = UNavigationSystemV1::GetCurrent(GetWorld());

	TSoftObjectPtr<AActor> PawnActor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPawn::StaticClass());
	if(!PawnActor.IsValid())
	{
		UE_LOG(LogTemp , Log, TEXT("Could not find Actor of Class: %s") , *APlayerPawn::StaticClass()->GetName());
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not find Actor of Class: %ls") , *APlayerPawn::StaticClass()->GetName()));
		return;
	}

	TSoftObjectPtr<UCapsuleComponent> CapsuleComponent = PawnActor->FindComponentByClass(UCapsuleComponent::StaticClass());

	if(!CapsuleComponent.IsValid())
	{
		UE_LOG(LogTemp , Log, TEXT("Could not find ActorComponent of Class: %s") , *UCapsuleComponent::StaticClass()->GetName());
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not find ActorComponent of Class: %ls") , *UCapsuleComponent::StaticClass()->GetName()));
		return;
	}

	PlayerPawnRadius = CapsuleComponent->GetScaledCapsuleRadius();

	for (int32 i = 0; i<= 360; i+= AngleStep)
	{
		auto ObjName = FString::Printf(TEXT("NavSampler_Angle:%d") , i);
		TSoftObjectPtr<UBoxComponent> BoxComponent = NewObject<UBoxComponent>();
		BoxComponent->SetupAttachment(this);
		//FVector GetRelativeLocation = PawnActor->GetActorRotation() * (PlayerPawnRadius * PawnActor.Get()->GetActorForwardVector()) ;
		//BoxComponent.Get()->SetRelativeLocation()
	}
	// ...
}


// Called every frame
void UPlayerNavAreaSampler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	// ...
}

