#pragma once
//#if WITH_EDITOR
// editor code that uses unrealed module here
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "LevelEditor.h"
#include "Commands/FZombheadsCommands.h"

class FZombheadsEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	void AddMenuItem();
	virtual void ShutdownModule() override;
};
//#endif