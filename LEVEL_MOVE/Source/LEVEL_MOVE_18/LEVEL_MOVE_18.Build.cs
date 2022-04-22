// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LEVEL_MOVE_18 : ModuleRules
{
	public LEVEL_MOVE_18(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
