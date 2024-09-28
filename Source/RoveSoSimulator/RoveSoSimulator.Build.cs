// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class RoveSoSimulator : ModuleRules
{
    public RoveSoSimulator(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bUseUnity = false;

        // Add public dependencies
        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
        });

        // Define libraries based on platform
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // RoveComm_CPP
            PublicDefinitions.Add("BS_THREAD_POOL_ENABLE_PAUSE=1");
            CMakeTarget.add(Target, this, "RoveComm_CPP", Path.Combine(this.ModuleDirectory, "../ThirdParty/RoveComm_CPP"), "-DBUILD_WIN=ON -D__ROVECOMM_LIBRARY_MODE__=0 -DBUILD_TESTS_MODE=OFF", true);
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            // RoveComm_CPP
            PublicDefinitions.Add("BS_THREAD_POOL_ENABLE_PAUSE=1");
            CMakeTarget.add(Target, this, "RoveComm_CPP", Path.Combine(this.ModuleDirectory, "../ThirdParty/RoveComm_CPP"), "-D__ROVECOMM_LIBRARY_MODE__=0 -DBUILD_TESTS_MODE=OFF", true);
        }
    }
}
