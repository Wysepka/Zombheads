// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Zombheads : ModuleRules
{
	public Zombheads(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" , "EnhancedInput" , "Slate" , "UMG" , "SlateCore" , "AIModule", "NavigationSystem" });

		//PrivateDependencyModuleNames.AddRange(new string[] { "SlateCore" , "Slate" ,"InputCore"});
		PrivateDependencyModuleNames.AddRange(new string[] {});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
