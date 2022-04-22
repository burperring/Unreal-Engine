// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DESTRUCTIBLE_MESH_16 : ModuleRules
{
	public DESTRUCTIBLE_MESH_16(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
