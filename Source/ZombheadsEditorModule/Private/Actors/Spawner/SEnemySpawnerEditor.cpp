// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#include "ZombheadsEditorModule/Public/Actors/Spawner/SEnemySpawnerEditor.h"

#include <string>

#include "Actors/Enemy/EnemyZombie.h"
#include "Actors/Spawner/UEnemyTypeSubclassHolder.h"
#include "Utility/DebugUtility.h"

void SEnemySpawnerEditor::Construct(const FArguments& InArgs)
{
	/*
	ChildSlot
	[
		// Example content, replace with your actual editor UI components
		SNew(SBorder)
		.BorderBackgroundColor(FLinearColor::White)
		.Padding(15)
		[
			SNew(STextBlock)
			.Text(NSLOCTEXT("StandaloneEditorWindow", "ExampleText", "Actor Details"))
		]
	];
	*/

	//SAssignNew(Parent, SOverlay);
	
	Items.Add(MakeShareable(new FEnemySpawnData_Slate));
	Items.Add(MakeShareable(new FEnemySpawnData_Slate));
	Items.Add(MakeShareable(new FEnemySpawnData_Slate));
	Items.Add(MakeShareable(new FEnemySpawnData_Slate));
	Items.Add(MakeShareable(new FEnemySpawnData_Slate));
	Items.Add(MakeShareable(new FEnemySpawnData_Slate));
	Items.Add(MakeShareable(new FEnemySpawnData_Slate));
	Items.Add(MakeShareable(new FEnemySpawnData_Slate));
	Items.Add(MakeShareable(new FEnemySpawnData_Slate));

	EnemySpawnerPtr = InArgs._EnemySpawnerArg;
	
	SAssignNew(ListView, SListView<TSharedPtr<FEnemySpawnData_Slate>>)
	.ListItemsSource(&Items)
	.OnGenerateRow(this, &SEnemySpawnerEditor::OnGenerateRowForList)
	.ItemHeight(150.f)
	.OnFinishedScrolling(FOnFinishedScrolling::CreateLambda([this](){OnFinishedScrolling();}))
	.ScrollbarVisibility(EVisibility::Visible);
	
	TSharedPtr<SVerticalBox> VerticalBox = SNew(SVerticalBox);
	//ChildSlot.AttachWidget(ListView.ToSharedRef());
	
	ChildSlot.AttachWidget(VerticalBox.ToSharedRef());
	
	SVerticalBox::FSlot* VerticalBox1Slot;
	SVerticalBox::FSlot* VerticalBox2Slot;
	SVerticalBox::FSlot* VerticalBox3Slot;
	//SVerticalBox::FSlot* VerticalBox15Slot;
	VerticalBox->AddSlot().Expose(VerticalBox1Slot);
	VerticalBox->AddSlot().Expose(VerticalBox2Slot);
	VerticalBox->AddSlot().Expose(VerticalBox3Slot);

	VerticalBox1Slot->SetAutoHeight();
	VerticalBox2Slot->SetAutoHeight();
	VerticalBox3Slot->SetAutoHeight();
	
	VerticalBox1Slot->AttachWidget(ListView.ToSharedRef());
	
	TSharedPtr<SButton> AddNewButton;
	TSharedPtr<SBox> ButtonAddContentBox;
	FOnClicked OnAddNewBtnClickedDelegate;

	TSharedPtr<STextBlock> AddBtnText = SNew(STextBlock);
	//TAttribute<FText> AddBtnText;
	//AddBtnText.Set(FText("Add New"));
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

	RefreshList();

	ListView->RequestListRefresh();
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
			//EditorWindow->EnemySpawnerPtr = EnemySpawnerPtr;
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
		auto Binding = Instance.Get()->Items[i].Get()->HolderBinding;
		if(!Binding.IsValid())
		{
			continue;;
		}
		Binding.Get()->RemoveFromRoot();
		Binding.Get()->MarkAsGarbage();
	}
}

TSharedPtr<SWindow> SEnemySpawnerEditor::EnemySpawnerEditorWindow = nullptr;
TSharedPtr<SEnemySpawnerEditor> SEnemySpawnerEditor::Instance = nullptr;

void SEnemySpawnerEditor::RefreshList()
{
	// Populate the Items array with your FEnemySpawnData instances
}

FReply SEnemySpawnerEditor::OnAddNewItem()
{
	
	UE_LOG(LogTemp , Log, TEXT("Adding new item in SEnemySpawnerEditor"));
	
	// Logic for adding a new item to your list and refreshing the view
	return FReply::Handled();
}

FReply SEnemySpawnerEditor::OnDeleteItem()
{
	// Logic for deleting an item from your list and refreshing the view
	return FReply::Handled();
}

void SEnemySpawnerEditor::OnItemSelected(TSharedPtr<FEnemySpawnData_Slate> Item, ESelectInfo::Type SelectInfo)
{
	// Logic for handling item selection, potentially updating a details panel
}

TSharedRef<ITableRow> SEnemySpawnerEditor::OnGenerateRowForList(TSharedPtr<FEnemySpawnData_Slate> Item, const TSharedRef<STableViewBase>& OwnerTable) {
	UUEnemyTypeSubclassHolder* MyHolder = NewObject<UUEnemyTypeSubclassHolder>();
	MyHolder->AddToRoot(); // Prevent garbage collection

	Item->HolderBinding = TWeakObjectPtr<UUEnemyTypeSubclassHolder>(MyHolder);
	
	FAssetPickerConfig AssetPickerConfig;
	TSharedPtr<SWidget> ContentPicker;

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs Args;
	Args.bAllowSearch = true;
	Args.bLockable = false;
	Args.bUpdatesFromSelection = false;

	TSharedPtr<IDetailsView> DetailsView;

	DetailsView = PropertyModule.CreateDetailView(Args);
	DetailsView->SetObject(MyHolder);

	//return ListTable.ToSharedRef();
	return SNew(STableRow<TSharedPtr<FEnemySpawnData>>, OwnerTable)
		.Content()
		[
			DetailsView->AsShared()
			/*
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[
				DetailsView->AsShared()
			]
			*/
		];
		
}

void SEnemySpawnerEditor::OnTableRowClicked_Custom(TSharedPtr<UUEnemyTypeSubclassHolder>) const
{
	auto s = 's';
	//return FReply::Handled();
}

void SEnemySpawnerEditor::OnFinishedScrolling()
{
	auto s = 's';
}


