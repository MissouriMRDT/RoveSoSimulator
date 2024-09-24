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

        // Load RoveComm based on the platform
        LoadRoveComm(Target);
    }

    private void LoadRoveComm(ReadOnlyTargetRules Target)
    {
        // Define paths for both Windows and Linux libraries
        string BasePath = Path.Combine(ModuleDirectory, "ThirdParty");

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // Windows-specific paths
            string IncludePath = Path.Combine(BasePath, "RoveComm_CPP_WIN64", "include");
            string LibPath = Path.Combine(BasePath, "RoveComm_CPP_WIN64", "lib");

            PublicIncludePaths.Add(IncludePath);
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libRoveComm_CPP.a"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            // Linux-specific paths
            string IncludePath = Path.Combine(BasePath, "RoveComm_CPP_AMD64", "include");
            string LibPath = Path.Combine(BasePath, "RoveComm_CPP_AMD64", "lib");

            PublicIncludePaths.Add(IncludePath);
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libRoveComm_CPP.a"));
        }
    }
}
