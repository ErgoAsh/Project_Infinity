// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Framework : ModuleRules
{
	public Framework(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(
            new string[] { "Core", "CoreUObject", "Engine", "InputCore", "RHI", "RenderCore", "ShaderCore",
                "AnimGraph", "UnrealEd", "Kismet", "KismetWidgets", "KismetCompiler", "BlueprintGraph",
                "GraphEditor" });
    }
}
