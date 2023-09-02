//Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated 
//documentation files(the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and 
//to permit persons to whom the Software is furnished to do so, subject to the following conditions
#include "Player/PlayerCharacterWrapper.h"

#include "AssetViewUtils.h"

APlayerCharacterWrapper::APlayerCharacterWrapper() {
}

//void APlayerCharacterWrapper::Tick(float deltaTime) {
//	LookAtMousePos();
//}

void APlayerCharacterWrapper::BeginPlay() {
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("BeginPlay from Code"));

	AActor* ActorPawn = UGameplayStatics::GetActorOfClass(GetWorld() , APlayerPawn::StaticClass());

	if (ActorPawn == nullptr) {
		FString PawnClassName;
		APlayerPawn::StaticClass()->GetClass()->GetName(PawnClassName);
		UE_LOG(LogTemp, Log, TEXT("Could not find ActorPawn %s") , *PawnClassName);
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("ERROR: Could not find ActorPawn Type: %s"), *PawnClassName));
		return;
	}

	FindPawnCharRepresentation(ActorPawn);

	PlayerPawn = Cast<APlayerPawn>(ActorPawn);

	if (PlayerPawn == nullptr) {
		FString PawnClassName;
		PlayerPawn->GetClass()->GetName(PawnClassName);
		UE_LOG(LogTemp, Log, TEXT("Could not find ActorPawn %s"), *PawnClassName);
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("ERROR: Could not cast PlayerPawn Type: %s"), *PawnClassName));
		return;
	}

	UInventorySceneContainer* ActiveContainer = nullptr;
	UInventorySceneContainer* DisabledContainer = nullptr;
	PlayerPawn->GetInventorySceneContainers(ActiveContainer, DisabledContainer);
	
	if (ActiveContainer == NULL || DisabledContainer == NULL) {
		UE_LOG(LogTemp, Log, TEXT("One of Inventory Container is NULL"));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("ERROR: One of Inventory Container is NULL")));
		return;
	}

	Inventory = new	PlayerInventory(ActiveContainer, DisabledContainer , ActorPawn , GetWorld());

	PlayerPawn->SetupPlayerPawn(Inventory);
	/*
	UAssetManager& AssetManager = UAssetManager::Get();
	if (AssetManager.IsValid()) {
		AssetManager.StartInitialLoading();

		//Inventory->PreloadInventory(AssetManager);
	}
	*/

	AActor* LoaderInitializerActor = UGameplayStatics::GetActorOfClass(GetWorld() , AAssetLoaderInitializer::StaticClass());
	if(LoaderInitializerActor == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , TEXT("Could not find AAssetLoaderInitializer"));
		UE_LOG(LogTemp , Log, TEXT("Could not find AAssetLoaderInitializer"));
		return;
	}

	AAssetLoaderInitializer* LoaderInitializer = Cast<AAssetLoaderInitializer>(LoaderInitializerActor);
	Inventory->PreloadInventory(LoaderInitializer);
}

void APlayerCharacterWrapper::FindPawnCharRepresentation(AActor* ActorPawn) {
	//This gives SpringArmComp
	//PawnCharRepresentation = Cast<USceneComponent>(ActorPawn->GetComponentByClass(USceneComponent::StaticClass()));
	PawnCharRepresentation = ActorPawn->GetRootComponent();

	if (PawnCharRepresentation == nullptr) {
		FString PawnClassName;
		ActorPawn->GetClass()->GetName(PawnClassName);
		UE_LOG(LogTemp, Log, TEXT("Could not find PawnCharRepresentation %s"), *PawnClassName);
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("ERROR: Could not find PawnCharRepresentation Type: %s"), *PawnClassName));
		return;
	}

	
}

void APlayerCharacterWrapper::BeginDestroy() {
	if (Inventory != nullptr) {
		Inventory->DeloadInventory();
		delete Inventory;
	}
	if(PlayerPawn != nullptr)
	{
		PlayerPawn->DisposePlayerPawn();
	}
	Super::BeginDestroy();
}

void APlayerCharacterWrapper::MoveCharacter()
{
}
/*
void APlayerCharacterWrapper::BeginPlay_Impl() {

}
*/
void APlayerCharacterWrapper::SetupInputComponent() {
	Super::SetupInputComponent();
	this->InputComponent->BindAxis("MoveForward", this, &APlayerCharacterWrapper::MoveForward);
	this->InputComponent->BindAxis("MoveRight", this, &APlayerCharacterWrapper::MoveRight);
	this->InputComponent->BindAction(FName("Slot1"),IE_Pressed, this, &APlayerCharacterWrapper::Equip1Slot);
	this->InputComponent->BindAction(FName("Slot2") , IE_Pressed , this , &APlayerCharacterWrapper::Equip2Slot);
	this->InputComponent->BindAction(FName("Use") , IE_Pressed , this, &APlayerCharacterWrapper::Use);
}

void APlayerCharacterWrapper::Equip1Slot() {
	Inventory->Equip1Slot();

	UE_LOG(LogTemp, Log, TEXT("Equiping Slot %s"), *FString("Slot1"));
}

void APlayerCharacterWrapper::Equip2Slot()
{
	Inventory->Equip2Slot();
	UE_LOG(LogTemp, Log, TEXT("Equiping Slot %s"), *FString("Slot2"));
}

void APlayerCharacterWrapper::Use()
{
	Inventory->Use();
}


void APlayerCharacterWrapper::MoveForward(float value) {
	if (FMath::IsNearlyZero(value)) { 
		MovementForward = FVector::ZeroVector;
		return; 
	}
	APawn* ControllerPawn = GetPawn();
	if (ControllerPawn) {
		if (moveCoordsType == EPlayerMovingCoordinates::LocalCoords) {
			MovementForward = value * ControllerPawn->GetActorForwardVector();
		}
		else if (moveCoordsType == EPlayerMovingCoordinates::WorldCoords) {
			MovementForward = value * FVector::ForwardVector;
		}
		//ControllerPawn->AddMovementInput(MovementForward);
		/*
		UPawnMovementComponent* PawnMovememt = ControllerPawn->GetMovementComponent();
		if (PawnMovememt != NULL) {
			PawnMovememt->AddInputVector(MovementForward);
		}
		*/
	}
	//transform.
}

void APlayerCharacterWrapper::MoveRight(float value) {
	if (FMath::IsNearlyZero(value)) { 
		MovementRight = FVector::ZeroVector;
		return; 
	}
	APawn* ControllerPawn = GetPawn();
	if (ControllerPawn) {
		if (moveCoordsType == EPlayerMovingCoordinates::LocalCoords) {
			MovementRight = value * ControllerPawn->GetActorRightVector();
		}
		else if (moveCoordsType == EPlayerMovingCoordinates::WorldCoords) {
			MovementRight = value * FVector::RightVector;
		}
		//ControllerPawn->AddMovementInput(MovementRight);
		/*
		UPawnMovementComponent* PawnMovememt = ControllerPawn->GetMovementComponent();
		if (PawnMovememt != NULL) {
			PawnMovememt->AddInputVector(MovementRight);
		}
		*/
	}
}

void APlayerCharacterWrapper::Tick(float delta) {
	Super::Tick(delta);
	LookAtMousePos();

	APawn* ControllerPawn = GetPawn();
	if (ControllerPawn) 
	{
		UPawnMovementComponent* PawnMovememt = ControllerPawn->GetMovementComponent();
		if (PawnMovememt != NULL) {
			FVector ForwardAndRight = MovementForward + MovementRight;
			if (ForwardAndRight.Normalize()) {
				PawnMovememt->AddInputVector(ForwardAndRight * MovingSpeed);
			}
		}
	}
}

void APlayerCharacterWrapper::LookAtMousePos() {
	//return;
	FVector2D MousePos;
	float locX, locY;
	GetMousePosition(locX,locY);
	MousePos = FVector2D(locX, locY);
	FTransform pawnTransform = GetPawn()->GetTransform();
	//FVector3f::UpVector
	FPlane playerPlane = FPlane(pawnTransform.GetLocation(), FVector3d::UpVector);
	FVector WorldLocation;
	FVector WorldDirection;

	// Convert screen space mouse coordinates to a ray in world space
	UGameplayStatics::DeprojectScreenToWorld(
		this,
		MousePos,
		WorldLocation,
		WorldDirection
	);

	// Calculate the intersection point between the ray and the plane
	//FVector PlanePos = WorldLocation + (WorldDirection * ((-playerPlane.W) / FVector::DotProduct(playerPlane, WorldDirection)));
	//FVector DirOnPlane = WorldLocation - pawnTransform.GetLocation();
	FVector IntersectionMousePlayerPlane = FMath::RayPlaneIntersection(WorldLocation, WorldDirection, playerPlane);
	FVector DirToWorldMousePos = (IntersectionMousePlayerPlane - pawnTransform.GetLocation());
	if (DirToWorldMousePos.Normalize()) {
		//RotationToMousePos = DirToWorldMousePos.Rotation();
		PawnCharRepresentation->SetWorldRotation(DirToWorldMousePos.Rotation());
		//GetPawn()->SetActorRotation(DirToWorldMousePos.Rotation());
	}
	//GetMousePosition(float MouseXPos, float MouseYPos);
}

