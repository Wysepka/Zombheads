// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "Actors/Spawner/IEnemySpawnerInfo.h"
#include "Actors/Enemy/EnemyBase.h"
#include "Managers/Statistics/StateStatInfo.h"

/**
 * 
 */
class ZOMBHEADS_API SHUDPointsCounter : public SOverlay
{
public:
	SHUDPointsCounter();
	~SHUDPointsCounter();

	SLATE_BEGIN_ARGS(SHUDPointsCounter) {}
	SLATE_ARGUMENT(TSharedPtr<const FSlateBrush>, BackgroundPointsBrushArg);
	SLATE_ARGUMENT(TSharedPtr<StateStatInfo>, StateStatInfoArg);
	SLATE_END_ARGS()

	void Construct(const FArguments& inArgs);
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	TSharedPtr<SImage> ContainerBackgroundImg;
	TSharedPtr<SHorizontalBox> HorizontalLayout;
	FDelegateHandle OnEnemyDiedHandle;

	TSharedPtr<const FSlateBrush> BrushBackground;
	
	TSharedPtr<STextBlock> PointsNumTextBlock;

	void OnPointsChanged_Receiver(int64 CurrentPoints);
};
