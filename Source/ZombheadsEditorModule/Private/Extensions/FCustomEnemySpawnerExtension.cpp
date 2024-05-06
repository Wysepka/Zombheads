// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:


#include "Extensions/FCustomEnemySpawnerExtension.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "Actors/Spawner/SEnemySpawnerEditor.h"

TSharedRef<IDetailCustomization> FCustomEnemySpawnerExtension::MakeInstance()
{
	return MakeShareable(new FCustomEnemySpawnerExtension);
}

void FCustomEnemySpawnerExtension::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	DetailBuilderRef = &DetailBuilder;

	UE_LOG(LogTemp, Warning, TEXT("CustomizeDetails is being called."));
	
	// Add a new category or find an existing one where you want to add the button
	IDetailCategoryBuilder& CustomCategory = DetailBuilder.EditCategory("CustomCategory", FText::FromString("My Custom Category"), ECategoryPriority::Important);

	CustomCategory.AddCustomRow(FText::FromString("Open Editor"))
		.ValueContent()
		// Provide enough space for the button
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.MaxDesiredWidth(250)
		[
			SNew(SButton)
			.Text(FText::FromString("Open Standalone Editor"))
			.ToolTipText(FText::FromString("Click to open the standalone editor window for this actor."))
			.OnClicked(this, &FCustomEnemySpawnerExtension::OnStandaloneEditorButtonClick)
		];

	CustomCategory.AddCustomRow(FText::FromString("Clear Data"))
	.ValueContent()
	// Provide enough space for the button
	.HAlign(HAlign_Left)
	.VAlign(VAlign_Center)
	.MaxDesiredWidth(250)
	[
		SNew(SButton)
		.Text(FText::FromString("Clear Spawner Datas"))
		.ToolTipText(FText::FromString("Click to clear Spawner Datas in EnemySpawner."))
		.OnClicked(this, &FCustomEnemySpawnerExtension::OnClearSpawnDatasButtonClick)
	];
}

FReply FCustomEnemySpawnerExtension::OnStandaloneEditorButtonClick()
{
	// Logic to open the standalone editor window goes here
	// For now, we'll just print a log message
	UE_LOG(LogTemp, Warning, TEXT("Button Clicked! Implement window opening logic here."));

	//SEnemySpawnerEditor::OpenWindow(DetailBuilderRef->GetSelectedObjects());
	SEnemySpawnerEditor::OpenWindow(DetailBuilderRef->GetSelectedObjects());
	
	return FReply::Handled();
}

FReply FCustomEnemySpawnerExtension::OnClearSpawnDatasButtonClick()
{
	for (const TWeakObjectPtr<UObject>& Actor : DetailBuilderRef->GetSelectedObjects())
	{
		if (Actor.IsValid())
		{
			UE_LOG(LogTemp, Log, TEXT("Selected Actor: %s"), *Actor->GetName());
			TSoftObjectPtr<AEnemySpawner> EnemySpawnerPtr = Cast<AEnemySpawner>(Actor);
			if(!EnemySpawnerPtr.IsValid())
			{
				//LOG_MISSING_COMPONENT("Opened Element In Outliner %s is not EnemySpawner blueprint instance !" , *Actor , *Actor->GetName());
				return FReply::Handled();
			}
			EnemySpawnerPtr.Get()->ClearSpawnerDatas();
			return FReply::Handled();
			//EditorWindow->EnemySpawnerPtr = EnemySpawnerPtr;
		}
	}
	return FReply::Handled();
}
