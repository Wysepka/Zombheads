using UnrealBuildTool;

public class ZombheadsUIModuleTarget : TargetRules
{
	public ZombheadsUIModuleTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ZombheadsUIModule" , "Zombheads" } );
	}
}