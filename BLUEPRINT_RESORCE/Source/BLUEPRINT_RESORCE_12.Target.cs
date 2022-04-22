// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BLUEPRINT_RESORCE_12Target : TargetRules
{
	public BLUEPRINT_RESORCE_12Target( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "BLUEPRINT_RESORCE_12" } );
	}
}
