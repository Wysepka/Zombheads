using UnrealBuildTool;

public class ZombheadsUIModule : ModuleRules
{
	public ZombheadsUIModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"Zombheads",
			"UMGEditor",
		});
		PrivateDependencyModuleNames.AddRange(new string[] {});
	}
}