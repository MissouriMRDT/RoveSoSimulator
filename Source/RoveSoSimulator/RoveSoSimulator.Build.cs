// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RoveSoSimulator : ModuleRules
{
    public RoveSoSimulator(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bUseUnity = false;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
        });
    }
}
