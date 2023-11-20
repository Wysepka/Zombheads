// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#include "Callbacks/AssetLoaderObserver.h"
#include "Data/PDA_Character.h"
#include "Data/WeaponsPrimaryDataAsset.h"
#include "Data/AnimationsPrimaryDataAsset.h"

// Add default functionality here for any IAssetLoaderObserver functions that are not pure virtual.
void IAssetLoaderObserver::PrimaryDataAssetLoaded(UPrimaryDataAsset* Data)
{
	UE_LOG(LogTemp , Log, TEXT("AssetLoadedOverver method not implemented"))
	GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("AssetLoadedOverver not implemented")));
}

void IAssetLoaderObserver::PrimaryDataAssetLoaded(UPDA_Character* Data)
{
	UE_LOG(LogTemp , Log, TEXT("AssetLoadedOverver method not implemented"))
	GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("AssetLoadedOverver not implemented")));
}

void IAssetLoaderObserver::PrimaryDataAssetLoaded(UAnimationsPrimaryDataAsset* Data)
{
	UE_LOG(LogTemp , Log, TEXT("AssetLoadedOverver method not implemented"))
	GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("AssetLoadedOverver not implemented")));
}

void IAssetLoaderObserver::PrimaryDataAssetLoaded(UWeaponsPrimaryDataAsset* Data)
{
	UE_LOG(LogTemp , Log, TEXT("AssetLoadedOverver method not implemented"))
	GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("AssetLoadedOverver not implemented")));
}
