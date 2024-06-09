// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "Actors/Spawner/IEnemySpawnerInfo.h"
#include "UObject/WeakInterfacePtr.h"

/**
 * 
 */
class ZOMBHEADS_API SHUDWavePanel : public SOverlay
{
public:
	SHUDWavePanel();
	~SHUDWavePanel();

	SLATE_BEGIN_ARGS(SHUDWavePanel) {}
	SLATE_ARGUMENT(TWeakInterfacePtr<IIEnemySpawnerInfo> , EnemySpawnerInfoArg);
	SLATE_ARGUMENT(TSharedPtr<const FSlateBrush>, BackgroundWaveBrushArg);
	SLATE_END_ARGS()

	void Construct(const FArguments& inArgs);
	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:
	TWeakInterfacePtr<IIEnemySpawnerInfo> EnemySpawnerInfoPtr;
	TSharedPtr<SImage> ContainerBackgroundImg;
	TSharedPtr<SHorizontalBox> HorizontalLayout;
	
	TSharedPtr<STextBlock> WaveLocTextBlock;
	TSharedPtr<STextBlock> WaveNumTextBlock;
	TSharedPtr<const FSlateBrush> BrushBackgroundNew;

	TSharedPtr<SHorizontalBox::FSlot> Layout1Slot;
	TSharedPtr<SHorizontalBox::FSlot> Layout2Slot;
};
