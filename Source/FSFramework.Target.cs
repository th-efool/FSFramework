// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FSFrameworkTarget : TargetRules
{
	public FSFrameworkTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
		ExtraModuleNames.Add("FSFramework");
	}
}