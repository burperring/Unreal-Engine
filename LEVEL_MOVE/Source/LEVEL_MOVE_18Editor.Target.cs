// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class LEVEL_MOVE_18EditorTarget : TargetRules
{
	public LEVEL_MOVE_18EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("LEVEL_MOVE_18");
	}
}
