// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DESTRUCTIBLE_MESH_16Target : TargetRules
{
	public DESTRUCTIBLE_MESH_16Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("DESTRUCTIBLE_MESH_16");
	}
}
