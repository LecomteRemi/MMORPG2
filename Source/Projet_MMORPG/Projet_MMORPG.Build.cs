// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Projet_MMORPG : ModuleRules
{
	public Projet_MMORPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule", "UMG", "Slate", "SlateCore", "AIModule", "NavigationSystem", "GameplayTasks", "GameplayTags" });
	}
}
