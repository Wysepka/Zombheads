// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "Data/PDA_HUD.h"
#include "UObject/Interface.h"

#include "AssetLoaderObserver.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAssetLoaderObserver : public UInterface
{
	GENERATED_BODY()

};

/**
 * 
 */
class UPrimaryDataAsset;
class UPDA_Character;
class UWeaponsPrimaryDataAsset;
class UAnimationsPrimaryDataAsset;

class ZOMBHEADS_API IAssetLoaderObserver
{
	GENERATED_BODY()

	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void PrimaryDataAssetLoaded(UPrimaryDataAsset* Data) ;
	virtual void PrimaryDataAssetLoaded(UPDA_Character* Data);
	virtual void PrimaryDataAssetLoaded(UAnimationsPrimaryDataAsset* Data);
	virtual void PrimaryDataAssetLoaded(UWeaponsPrimaryDataAsset* Data);
	virtual void PrimaryDataAssetLoaded(UPDA_HUD* Data);
	//template <typename T, typename = std::enable_if_t<std::is_base_of<UPrimaryDataAsset, T>::value>>
	//void PrimaryDataAssetLoaded(T* Data);

};

/*
template <typename T, typename>
void IAssetLoaderObserver::PrimaryDataAssetLoaded(T* Data)
{
	UE_LOG(LogTemp , Log, TEXT("AssetLoadedOverver method not implemented for type: %s") , typeid(T).name());
	GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("AssetLoadedOverver not implemented for type: %hs") , typeid(T).name()));
}
*/