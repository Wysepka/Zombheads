// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#include "ZombheadsEditorModule/Public/Actors/Spawner/SEnemySpawnerEditor.h"

#include <string>

#include "Actors/Enemy/EnemyZombie.h"
#include "Actors/Spawner/UEnemyTypeSubclassHolder.h"
#include "Utility/DebugUtility.h"

void SEnemySpawnerEditor::Construct(const FArguments& InArgs)
{
	EnemySpawnerPtr = InArgs._EnemySpawnerArg;

	RefreshListSource();
	
	SAssignNew(ListView, SListView<TSharedPtr<FEnemySpawnData_Slate>>)
	.ListItemsSource(&Items)
	.OnGenerateRow(this, &SEnemySpawnerEditor::OnGenerateRowForList)
	.OnFinishedScrolling(FOnFinishedScrolling::CreateLambda([this](){OnFinishedScrolling();}))
	.ScrollbarVisibility(EVisibility::Visible)
	.OnSelectionChanged(this, &SEnemySpawnerEditor::OnListRowSelectionChanged);

	ListView->RequestListRefresh();
	
	TSharedPtr<SVerticalBox> VerticalBox = SNew(SVerticalBox);
	
	ChildSlot.AttachWidget(VerticalBox.ToSharedRef());
	
	SVerticalBox::FSlot* VerticalBox1Slot;
	SVerticalBox::FSlot* VerticalBox2Slot;
	SVerticalBox::FSlot* VerticalBox3Slot;
	VerticalBox->AddSlot().Expose(VerticalBox1Slot);
	VerticalBox->AddSlot().Expose(VerticalBox2Slot);
	VerticalBox->AddSlot().Expose(VerticalBox3Slot);

	VerticalBox1Slot->SetFillHeight(1.f);
	VerticalBox2Slot->SetAutoHeight();
	VerticalBox3Slot->SetAutoHeight();
	
	VerticalBox1Slot->AttachWidget(ListView.ToSharedRef());
	
	TSharedPtr<SButton> AddNewButton;
	TSharedPtr<SBox> ButtonAddContentBox;
	FOnClicked OnAddNewBtnClickedDelegate;

	TSharedPtr<STextBlock> AddBtnText = SNew(STextBlock);
	SAssignNew(AddNewButton, SButton).OnClicked(FOnClicked::CreateRaw(this , &SEnemySpawnerEditor::OnAddNewItem))
	[
		SAssignNew(ButtonAddContentBox, SBox)
		// Initially, you can add any widget here
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SAssignNew(AddBtnText, STextBlock)
			.Text(NSLOCTEXT("ZombheadsEditorModule", "AddNewBtnTxt", "Add New Entry"))
		]
	];

	VerticalBox2Slot->AttachWidget(AddNewButton.ToSharedRef());

	TSharedPtr<SButton> RemoveButton;
	TSharedPtr<SBox> ButtonRemoveContentBox;
	
	TSharedPtr<STextBlock> RemoveBtnText = SNew(STextBlock);
	SAssignNew(RemoveButton, SButton).OnClicked(FOnClicked::CreateRaw(this , &SEnemySpawnerEditor::OnDeleteItem))
	[
		SAssignNew(ButtonRemoveContentBox, SBox)
		// Initially, you can add any widget here
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SAssignNew(RemoveBtnText, STextBlock)
			.Text(NSLOCTEXT("ZombheadsEditorModule", "RemoveBtnText", "Remove Selected Entry"))
		]
	];
	
	VerticalBox3Slot->AttachWidget(RemoveButton.ToSharedRef());
	
	ListView->RequestListRefresh();
	ListView->AddScrollOffset(1.f , true);
}

void SEnemySpawnerEditor::OpenWindow(const TArray<TWeakObjectPtr<UObject>>& SelectedActors)
{
	TSoftObjectPtr<AEnemySpawner> EnemySpawnerTemp;
	// Example of how you might use the selected actors. This just logs their names.
	for (const TWeakObjectPtr<UObject>& Actor : SelectedActors)
	{
		if (Actor.IsValid())
		{
			UE_LOG(LogTemp, Log, TEXT("Selected Actor: %s"), *Actor->GetName());
			TSoftObjectPtr<AEnemySpawner> EnemySpawnerPtr = Cast<AEnemySpawner>(Actor);
			if(!EnemySpawnerPtr.IsValid())
			{
				//LOG_MISSING_COMPONENT("Opened Element In Outliner %s is not EnemySpawner blueprint instance !" , *Actor , *Actor->GetName());
				return;
			}
			EnemySpawnerTemp = EnemySpawnerPtr;
			EnemySpawnerPtr->Modify();
			break;
		}
	}

	Instance = SNew(SEnemySpawnerEditor).EnemySpawnerArg(TWeakObjectPtr<AEnemySpawner>(EnemySpawnerTemp.Get()));
	
    
	// Create the window
	TSharedPtr<SWindow> Window = SNew(SWindow)
		.Title(NSLOCTEXT("StandaloneEditorWindow", "WindowTitle", "Actor Editor"))
		.ClientSize(FVector2D(800, 600))
		.SupportsMaximize(false)
		.SupportsMinimize(false)
		[
			Instance.ToSharedRef()
		];

	// Add the window to the screen
	FSlateApplication::Get().AddWindow(Window.ToSharedRef());
	Window->SetOnWindowClosed(FOnWindowClosed::CreateLambda([](const TSharedRef<SWindow>& WindowClosed)
	{
		CloseWindow();
	}));
	EnemySpawnerEditorWindow = Window;
}

void SEnemySpawnerEditor::CloseWindow()
{
	auto ItemsCache = Instance.Get()->ListView->GetItems();
	for (size_t i = 0; i < ItemsCache.Num(); i++)
	{
		auto Binding = ItemsCache[i]->HolderBinding;
		if(!Binding.IsValid())
		{
			continue;;
		}
		ItemsCache[i]->HolderBinding->Dispose();
		Binding.Reset();
	}

	UPackage* Package = Instance.Get()->EnemySpawnerPtr->GetOutermost();
	if(Package)
	{
		Package->MarkPackageDirty();
	}

	GEditor->RedrawAllViewports();
}

void SEnemySpawnerEditor::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	ListView->RequestListRefresh();
}

TSharedPtr<SWindow> SEnemySpawnerEditor::EnemySpawnerEditorWindow = nullptr;
TSharedPtr<SEnemySpawnerEditor> SEnemySpawnerEditor::Instance = nullptr;

void SEnemySpawnerEditor::RefreshListSource()
{
	auto EnemySpawnDataSource = EnemySpawnerPtr.Get()->GetSpawnerDatas();
	for (size_t i = 0; i < EnemySpawnDataSource.Num(); i++)
	{
		FEnemySpawnData SpawnData = EnemySpawnDataSource[i];
		Items.Add(MakeShareable(new FEnemySpawnData_Slate(i, SpawnData.EnemyBP , SpawnData.EnemyCount , SpawnData.InBetweenSpawnDelay , SpawnData.DelayBeforeSpawning)));
	}
}

FReply SEnemySpawnerEditor::OnAddNewItem()
{
	UE_LOG(LogTemp , Log, TEXT("Adding new item in SEnemySpawnerEditor"));
	EnemySpawnerPtr.Get()->AddSpawnData();
	Items.Add(MakeShareable(new FEnemySpawnData_Slate(EnemySpawnerPtr.Get()->GetSpawnDatasCount() - 1)));
	ListView->RequestListRefresh();
	//ListView.Get()->SetItemsSource(&Items);
	
	// Logic for adding a new item to your list and refreshing the view
	return FReply::Handled();
}

FReply SEnemySpawnerEditor::OnDeleteItem()
{
	auto Binding = SelectedData.Get()->HolderBinding;
	if(!Binding.IsValid())
	{
		return FReply::Handled();
	}
	
	Binding.Get()->RemoveFromRoot();
	Binding.Get()->MarkAsGarbage();
	EnemySpawnerPtr.Get()->DeleteSpawnData(SelectedData->ID);
	Items.Remove(SelectedData);

	auto SpawnerDatas = EnemySpawnerPtr.Get()->GetSpawnerDatas();
	for (size_t i = SelectedData.Get()->ID; i < Items.Num(); i++)
	{
		Items[i]->ID = i;
		Items[i].Get()->HolderBinding.Get()->ID = i;
	}
	
	ListView->RequestListRefresh();
	// Logic for deleting an item from your list and refreshing the view
	return FReply::Handled();
}

void SEnemySpawnerEditor::OnItemSelected(TSharedPtr<FEnemySpawnData_Slate> Item, ESelectInfo::Type SelectInfo)
{
	// Logic for handling item selection, potentially updating a details panel
}

TSharedRef<ITableRow> SEnemySpawnerEditor::OnGenerateRowForList(TSharedPtr<FEnemySpawnData_Slate> Item, const TSharedRef<STableViewBase>& OwnerTable) {
	Item->HolderBinding = TStrongObjectPtr(NewObject<UUEnemyTypeSubclassHolder>());
	Item->HolderBinding->AddToRoot(); // Prevent garbage collection
	Item->HolderBinding->ID = Item->ID;
	Item->HolderBinding->EnemyBPHolder = Item->EnemyBP;
	Item->HolderBinding->EnemyCount = Item->EnemyCount;
	Item->HolderBinding->InBetweenSpawnDelay = Item->InBetweenSpawnDelay;
	Item->HolderBinding->DelayBeforeSpawning = Item->DelayBeforeSpawning;

	TSharedPtr<FEnemySpawnData> SpawnData = MakeShareable(&EnemySpawnerPtr.Get()->GetSpawnData(Item->ID)); 
	Item->HolderBinding.Get()->Init(SpawnData , TStrongObjectPtr<AEnemySpawner>(EnemySpawnerPtr.Get()));
	
	FAssetPickerConfig AssetPickerConfig;
	TSharedPtr<SWidget> ContentPicker;

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs Args;
	Args.bAllowSearch = true;
	Args.bLockable = false;
	Args.bUpdatesFromSelection = false;

	TSharedPtr<IDetailsView> DetailsView;

	DetailsView = PropertyModule.CreateDetailView(Args);
	DetailsView->SetObject(Item->HolderBinding.Get());
	//return ListTable.ToSharedRef();
	return SNew(STableRow<TSharedPtr<FEnemySpawnData>>, OwnerTable)
		.Content()
		[
			DetailsView->AsShared()
		];
}

void SEnemySpawnerEditor::OnListRowSelectionChanged(TSharedPtr<FEnemySpawnData_Slate> Item,
	ESelectInfo::Type SelectInfo)
{
	SelectedData = Item;
}


