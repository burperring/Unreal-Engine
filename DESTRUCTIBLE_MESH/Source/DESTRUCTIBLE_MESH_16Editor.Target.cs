// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DESTRUCTIBLE_MESH_16EditorTarget : TargetRules
{
	public DESTRUCTIBLE_MESH_16EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("DESTRUCTIBLE_MESH_16");
	}
}
