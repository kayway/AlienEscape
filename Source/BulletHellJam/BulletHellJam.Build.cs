// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BulletHellJam : ModuleRules
{
	public BulletHellJam(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[] { 
				"Core", 
				"CoreUObject", 
				"Engine", 
				"InputCore" ,
				"AIModule",
				"GameplayTasks",
				"NavigationSystem",
			}
		);
	}
}
