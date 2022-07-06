// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Ue5Lab : ModuleRules
{
    public Ue5Lab(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "MoviePlayer" });
    }
}
