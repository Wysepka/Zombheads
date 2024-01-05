// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AnimationsPrimaryDataAsset.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable, BlueprintType)
struct FPlayerAnimData {
	GENERATED_USTRUCT_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Player", meta=(AllowPrivateAccess = "true"))
	UAnimMontage* AimMontage;

	UPROPERTY(EditAnywhere , Category = "Player" , meta=(AllowPrivateAccess = "true"))
	UAnimMontage* ShotMontage;
	
public:
	UAnimMontage* GetAimMontage() const
	{
		return AimMontage;
	}

	UAnimMontage* GetShotMontage() const
	{
		return ShotMontage;
	}
};

UCLASS()
class ZOMBHEADS_API UAnimationsPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "PlayerAnims")
	FPlayerAnimData PlayerAnimData;

public:
	//inline static FString DefinedAssetKey = "DA_Animations";
	inline static FString DefinedAssetKey = "AnimationsPrimaryDataAsset";

	/*
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		FPrimaryAssetType PrimaryAssetType = FPrimaryAssetType(*DefinedAssetKey);
		FPrimaryAssetId PrimaryAssetId = FPrimaryAssetId(PrimaryAssetType , GetFName());

		//PrimaryAssetId.PrimaryAssetType = PrimaryAssetType;

		return PrimaryAssetId;
	}
	*/

	FPlayerAnimData* GetPlayerAnimData();

	static FPrimaryAssetId DefinedAssetID()
	{
		FPrimaryAssetType PrimaryAssetType = FPrimaryAssetType(*DefinedAssetKey);
		FPrimaryAssetId PrimaryAssetId;

		PrimaryAssetId.PrimaryAssetType = PrimaryAssetType;

		return PrimaryAssetId;
	}
	
};
