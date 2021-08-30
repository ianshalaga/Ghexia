// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE_Juego1Cpp : ModuleRules
{
	public UE_Juego1Cpp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG" });
	}
}
