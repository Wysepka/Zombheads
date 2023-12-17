//Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated 
//documentation files(the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and 
//to permit persons to whom the Software is furnished to do so, subject to the following conditions
#include "Player/PlayerCharacterWrapper.h"

#include "AssetViewUtils.h"
#include "Data/PDA_Character.h"
#include "DSP/Encoders/OggVorbisEncoder.h"
#include "DSP/Encoders/OggVorbisEncoder.h"
#include "Evaluation/MovieSceneEvaluationKey.h"
#include "UObject/WeakInterfacePtr.h"

APlayerCharacterWrapper::APlayerCharacterWrapper() {
}

//void APlayerCharacterWrapper::Tick(float deltaTime) {
//	LookAtMousePos();
//}

void APlayerCharacterWrapper::BeginPlay() {
	Super::BeginPlay();

	FInputModeGameOnly InputMode; 
	SetInputMode(InputMode);

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

	TWeakObjectPtr<UInventorySceneContainer> ActiveContainer = nullptr;
	TWeakObjectPtr<UInventorySceneContainer> DisabledContainer = nullptr;
	PlayerPawn->GetInventorySceneContainers(ActiveContainer, DisabledContainer);
	
	if (ActiveContainer == NULL || DisabledContainer == NULL) {
		UE_LOG(LogTemp, Log, TEXT("One of Inventory Container is NULL"));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("ERROR: One of Inventory Container is NULL")));
		return;
	}

	Inventory = MakeShared<PlayerInventory>(ActiveContainer , DisabledContainer , ActorPawn , GetWorld());

	PlayerPawn->SetupPlayerPawn(Inventory , TWeakInterfacePtr<ICharacterMovement>(this));

	AActor* LoaderInitializerActor = UGameplayStatics::GetActorOfClass(GetWorld() , AAssetLoaderInitializer::StaticClass());
	if(LoaderInitializerActor == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , TEXT("Could not find AAssetLoaderInitializer"));
		UE_LOG(LogTemp , Log, TEXT("Could not find AAssetLoaderInitializer"));
		return;
	}

	AAssetLoaderInitializer* LoaderInitializer = Cast<AAssetLoaderInitializer>(LoaderInitializerActor);
	Inventory->PreloadInventory(LoaderInitializer);

	AssetLoader = LoaderInitializer->GetAssetLoader();

	UPDA_Character* CharData;
	auto arg = AssetLoader->GetPrimaryDataAsset<UPDA_Character>(this, CharData);

	if(arg.Key)
	{
		ApplyBaseSpeed(CharData);
	}
	else
	{
		CharDataDelegate = arg.Value;
	}
	/*
	if(AssetLoader->GetIfCharactersDataInitialized())
	{
		ApplyBaseSpeed(AssetLoader->GetCharacterData());
	} else
	{
		AssetLoader->GetCharacterDataDelegate()->AddUObject(this, &APlayerCharacterWrapper::ApplyBaseSpeed);
	}
	*/
}

void APlayerCharacterWrapper::PrimaryDataAssetLoaded(UPDA_Character* Data)
{
	ApplyBaseSpeed(Data);
}

void APlayerCharacterWrapper::ApplyBaseSpeed(UPDA_Character* Data)
{
	WalkSpeedMultiplier = Data->GetPlayerWalkingSpeed();
	RunSpeedMultiplier = Data->GetPlayerRunningSpeed();
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
		Inventory = nullptr;
	}
	if(PlayerPawn != nullptr)
	{
		PlayerPawn->DisposePlayerPawn();
	}
	if(AssetLoader != nullptr)
	{
		if(CharDataDelegate.IsValid())
		{
			AssetLoader->UnRegisterCallback<UPDA_Character>(&CharDataDelegate);
		}
	}
	Super::BeginDestroy();
}

void APlayerCharacterWrapper::SetupInputComponent() {
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer());
	InputSubsystem->AddMappingContext(PlayerInputData->GetPlayerMappingContext().Get() , 0);
	
	UEnhancedInputComponent* Eic = Cast<UEnhancedInputComponent>(this->InputComponent);

	Eic->BindAction(PlayerInputData->GetPlayerMoveForwardAction().Get() , ETriggerEvent::Triggered , this, &APlayerCharacterWrapper::MoveForward);
	Eic->BindAction(PlayerInputData->GetPlayerMoveForwardAction().Get() , ETriggerEvent::Completed , this, &APlayerCharacterWrapper::ResetMoveForward);

	Eic->BindAction(PlayerInputData->GetPlayerMoveBackwardAction().Get() , ETriggerEvent::Triggered , this, &APlayerCharacterWrapper::MoveBackwards);
	Eic->BindAction(PlayerInputData->GetPlayerMoveBackwardAction().Get() , ETriggerEvent::Completed , this, &APlayerCharacterWrapper::ResetMoveBackwards);

	Eic->BindAction(PlayerInputData->GetPlayerMoveRightAction().Get() , ETriggerEvent::Triggered , this, &APlayerCharacterWrapper::MoveRight);
	Eic->BindAction(PlayerInputData->GetPlayerMoveRightAction().Get() , ETriggerEvent::Completed , this, &APlayerCharacterWrapper::ResetMoveRight);

	Eic->BindAction(PlayerInputData->GetPlayerMoveLeftAction().Get() , ETriggerEvent::Triggered , this, &APlayerCharacterWrapper::MoveLeft);
	Eic->BindAction(PlayerInputData->GetPlayerMoveLeftAction().Get() , ETriggerEvent::Completed , this, &APlayerCharacterWrapper::ResetMoveLeft);

	
	Eic->BindAction(PlayerInputData->GetPlayerSlot1Action().Get() , ETriggerEvent::Triggered , this, &APlayerCharacterWrapper::Equip1Slot);
	Eic->BindAction(PlayerInputData->GetPlayerSlot2Action().Get() , ETriggerEvent::Triggered , this, &APlayerCharacterWrapper::Equip2Slot);
	Eic->BindAction(PlayerInputData->GetPlayerUseAction().Get() , ETriggerEvent::Triggered , this, &APlayerCharacterWrapper::Use);
	Eic->BindAction(PlayerInputData->GetPlayerSprintAction().Get() , ETriggerEvent::Triggered , this , &APlayerCharacterWrapper::SprintBegin);
	Eic->BindAction(PlayerInputData->GetPlayerSprintAction().Get() , ETriggerEvent::Completed , this, &APlayerCharacterWrapper::SprintEnd);
	
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


void APlayerCharacterWrapper::MoveForward(const FInputActionValue& Value) {
	float moveValue = Value.Get<float>();
	if (FMath::IsNearlyZero(moveValue)) { 
		MovementForward = FVector::ZeroVector;
		return; 
	}
	APawn* ControllerPawn = GetPawn();
	if (ControllerPawn) {
		if (moveCoordsType == EPlayerMovingCoordinates::LocalCoords) {
			MovementForward = moveValue * ControllerPawn->GetActorForwardVector();
		}
		else if (moveCoordsType == EPlayerMovingCoordinates::WorldCoords) {
			MovementForward = moveValue * FVector::ForwardVector;
		}
	}
}

void APlayerCharacterWrapper::MoveBackwards(const FInputActionValue& Value)
{
	float moveValue = Value.Get<float>();
	if (FMath::IsNearlyZero(moveValue)) { 
		MovementBackward = FVector::ZeroVector;
		return; 
	}
	APawn* ControllerPawn = GetPawn();
	if (ControllerPawn) {
		if (moveCoordsType == EPlayerMovingCoordinates::LocalCoords) {
			MovementBackward = moveValue * ControllerPawn->GetActorForwardVector();
		}
		else if (moveCoordsType == EPlayerMovingCoordinates::WorldCoords) {
			MovementBackward = moveValue * FVector::ForwardVector;
		}
	}
}

void APlayerCharacterWrapper::ResetMoveForward()
{
	MovementForward = FVector::ZeroVector;
}

void APlayerCharacterWrapper::ResetMoveBackwards()
{
	MovementBackward = FVector::ZeroVector;
}

void APlayerCharacterWrapper::MoveRight(const FInputActionValue& Value) {
	float moveValue = Value.Get<float>();
	if (FMath::IsNearlyZero(moveValue)) { 
		MovementRight = FVector::ZeroVector;
		return; 
	}
	APawn* ControllerPawn = GetPawn();
	if (ControllerPawn) {
		if (moveCoordsType == EPlayerMovingCoordinates::LocalCoords) {
			MovementRight = moveValue * ControllerPawn->GetActorRightVector();
		}
		else if (moveCoordsType == EPlayerMovingCoordinates::WorldCoords) {
			MovementRight = moveValue * FVector::RightVector;
		}
	}
}

void APlayerCharacterWrapper::MoveLeft(const FInputActionValue& Value)
{
	float moveValue = Value.Get<float>();
	if (FMath::IsNearlyZero(moveValue)) { 
		MovementLeft = FVector::ZeroVector;
		return; 
	}
	APawn* ControllerPawn = GetPawn();
	if (ControllerPawn) {
		if (moveCoordsType == EPlayerMovingCoordinates::LocalCoords) {
			MovementLeft = moveValue * ControllerPawn->GetActorRightVector();
		}
		else if (moveCoordsType == EPlayerMovingCoordinates::WorldCoords) {
			MovementLeft = moveValue * FVector::RightVector;
		}
	}
}

void APlayerCharacterWrapper::ResetMoveRight()
{
	MovementRight = FVector::ZeroVector;
}

void APlayerCharacterWrapper::ResetMoveLeft()
{
	MovementLeft = FVector::ZeroVector;
}

void APlayerCharacterWrapper::SprintBegin()
{
	bIsSprinting = true;
}

void APlayerCharacterWrapper::SprintEnd()
{
	bIsSprinting = false;
}

void APlayerCharacterWrapper::Tick(float delta) {
	Super::Tick(delta);
	LookAtMousePos();

	APawn* ControllerPawn = GetPawn();
	if (ControllerPawn) 
	{
		UPawnMovementComponent* PawnMovememt = ControllerPawn->GetMovementComponent();
		if (PawnMovememt != NULL) {
			MovementFinalNormalized = MovementForward - MovementBackward + MovementRight - MovementLeft;
			MovementFinalNormalized.Normalize();
			
			if(bIsSprinting)
			{
				MovementFinal = MovementFinalNormalized * RunSpeedMultiplier;
			}
			else
			{
				MovementFinal = MovementFinalNormalized * WalkSpeedMultiplier;
			}
			
			PawnMovememt->AddInputVector(MovementFinal);
		}
	}
}

float APlayerCharacterWrapper::GetCharacterRunSpeed() const
{
	return RunSpeedMultiplier;
}

float APlayerCharacterWrapper::GetCharacterWalkSpeed() const
{
	return WalkSpeedMultiplier;
}


bool APlayerCharacterWrapper::GetIfCharacterSprinting() const
{
	return bIsSprinting;
}

float APlayerCharacterWrapper::GetCharacterMovementMagnitude() const
{
	return MovementFinal.Size();
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

