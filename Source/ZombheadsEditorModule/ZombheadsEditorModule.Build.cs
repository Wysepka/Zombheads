using UnrealBuildTool;

public class ZombheadsEditorModule: ModuleRules
{
	public ZombheadsEditorModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "EditorStyle" , "InputCore" , "PropertyEditor" });
		PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "Zombheads" , "Slate", "SlateCore" , "UnrealEd" , "ContentBrowser"});

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(new string[] {"UMG"});
		}
	}
}