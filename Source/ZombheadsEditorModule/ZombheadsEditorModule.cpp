//#if WITH_EDITOR
#include "ZombheadsEditorModule.h"

#include "PropertyEditorModule.h"
#include "Extensions/FCustomEnemySpawnerExtension.h"

IMPLEMENT_MODULE(FZombheadsEditorModule, ZombheadsEditorModule);

void FZombheadsEditorModule::StartupModule()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

		
		// Register the custom details panel extension here
		PropertyEditorModule.RegisterCustomClassLayout(
			"EnemySpawner", // Replace "YourActorClass" with the actual class name of your actor
			FOnGetDetailCustomizationInstance::CreateStatic(&FCustomEnemySpawnerExtension::MakeInstance)
		
		);
		
		PropertyEditorModule.NotifyCustomizationModuleChanged();
	}
	/*
	FZombheadsCommands::Register();

	// Other initialization code...

	// Add menu item
	AddMenuItem();
	*/
}

void FZombheadsEditorModule::AddMenuItem()
{

	/*
	// Register to add menu items
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	{
		TSharedPtr<FUICommandList> CommandList = MakeShareable(new FUICommandList);
		
		CommandList->MapAction(
			FZombheadsCommands::Get().OpenEnemySpawnDataEditor,
			FExecuteAction::CreateRaw(this, &FZombheadsCommands::OpenEnemySpawnDataEditor),
			FCanExecuteAction());
		
		LevelEditorModule.GetMenuExtensibilityManager()->GetAllExtensibilityPoints()[0]->AddMenuItem(
			FMenuBuilder(true, CommandList)
			.AddMenuEntry(FZombheadsCommands::Get().OpenEnemySpawnDataEditor)
			.ToSharedRef());
		
	}
	*/
}

void FZombheadsEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

		// Unregister the custom details panel extension here
		PropertyEditorModule.UnregisterCustomClassLayout("EnemySpawner"); // Again, replace "YourActorClass"
	}
}
//#endif