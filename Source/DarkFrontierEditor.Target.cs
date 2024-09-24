// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class DarkFrontierEditorTarget : TargetRules
{
	public DarkFrontierEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;

		ExtraModuleNames.AddRange( new[] { "DarkFrontier" } );
	}
}
