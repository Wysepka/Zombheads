// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

#pragma once

#include "CoreMinimal.h"
#include "EditorStyleSet.h"

/**
 * 
 */
#define LOCTEXT_NAMESPACE "ZombheadsCommands"

class ZOMBHEADSEDITORMODULE_API FZombheadsCommands: public TCommands<FZombheadsCommands>
{
public:
	FZombheadsCommands()
		: TCommands<FZombheadsCommands>(TEXT("YourPlugin"), NSLOCTEXT("Contexts", "YourPlugin", "YourPlugin Commands"), NAME_None, FEditorStyle::GetStyleSetName())
	{
	}

	virtual void RegisterCommands() override
	{
		UI_COMMAND(OpenEnemySpawnDataEditor, "Enemy Spawn Editor", "Open the Enemy Spawn Data Editor.", EUserInterfaceActionType::Button, FInputChord());
	}

	TSharedPtr<FUICommandInfo> OpenEnemySpawnDataEditor;
};

#undef LOCTEXT_NAMESPACE