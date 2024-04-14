// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "Actors/Spawner/EnemySpawner.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "ContentBrowserModule.h"
#include "UEnemyTypeSubclassHolder.h"
#include "SEnemySpawnerEditor.generated.h"

/**
 * 
 */

USTRUCT(Blueprintable, BlueprintType)
struct FEnemySpawnData_Slate
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TSubclassOf<AEnemyBase> EnemyBP;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	int EnemyCount;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	float InBetweenSpawnDelay;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	float DelayBeforeSpawning;

	TWeakObjectPtr<UUEnemyTypeSubclassHolder> HolderBinding;
	
	// Constructor
	FEnemySpawnData_Slate()
		: EnemyBP(nullptr),
		  EnemyCount(0),
		  InBetweenSpawnDelay(0),
		  DelayBeforeSpawning(0),
			HolderBinding(nullptr)	
	{
	}
};

class ZOMBHEADSEDITORMODULE_API SEnemySpawnerEditor : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SEnemySpawnerEditor) {}
	SLATE_ARGUMENT(TWeakObjectPtr<AEnemySpawner> , EnemySpawnerArg)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	static void OpenWindow(const TArray<TWeakObjectPtr<UObject>>& SelectedActors);
	static void CloseWindow();

	static TSharedPtr<SWindow> EnemySpawnerEditorWindow;
	static TSharedPtr<SEnemySpawnerEditor> Instance;

private:
	TSharedPtr<SListView<TSharedPtr<FEnemySpawnData_Slate>>> ListView;
	
	TArray<TSharedPtr<FEnemySpawnData_Slate>> Items;
	
	TWeakObjectPtr<AEnemySpawner> EnemySpawnerPtr;
	TSharedPtr<SOverlay> Parent;

	void RefreshList();
	FReply OnAddNewItem();
	FReply OnDeleteItem(TSharedPtr<FEnemySpawnData_Slate> Item);
	FReply OnDeleteItem();
	void OnItemSelected(TSharedPtr<FEnemySpawnData_Slate> Item, ESelectInfo::Type SelectInfo);

	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FEnemySpawnData_Slate> Item, const TSharedRef<STableViewBase>& OwnerTable);

	void OnTableRowClicked_Custom(TSharedPtr<UUEnemyTypeSubclassHolder>) const;
	void OnFinishedScrolling();
};
