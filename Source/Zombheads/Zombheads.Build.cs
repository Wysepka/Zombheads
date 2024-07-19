// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Zombheads : ModuleRules
{
	public Zombheads(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" , "EnhancedInput" , "Slate" , "SlateCore" , "AIModule", "NavigationSystem" , "UMG"});
		PrivateDependencyModuleNames.AddRange(new string[] {});

		if (Target.bBuildEditor)
		{
			//PublicDependencyModuleNames.AddRange(new string[] {"UMG"});
		}
	}
}
