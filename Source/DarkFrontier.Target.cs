// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class DarkFrontierTarget : TargetRules
{
	public DarkFrontierTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;

		ExtraModuleNames.AddRange( new[] { "DarkFrontier" } );
	}
}
