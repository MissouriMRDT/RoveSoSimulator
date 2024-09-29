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

        // Configure Unreal Build Tool.
        // PublicSystemLibraries.Add("stdc++");
        // PublicSystemLibraries.Add("pthread");
        CppStandard = CppStandardVersion.Cpp20;
        // bUseRTTI = true;
        // bEnableExceptions = true;
        // PublicDefinitions.Add("_GLIBCXX_USE_CXX11_ABI=1");


        // Define libraries based on platform
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // RoveComm_CPP
            PublicDefinitions.Add("BS_THREAD_POOL_ENABLE_PAUSE=1");
            CMakeTarget.add(Target, this, "RoveComm_CPP", Path.Combine(this.ModuleDirectory, "../ThirdParty/RoveComm_CPP"), "-DBUILD_WIN=ON -D__ROVECOMM_LIBRARY_MODE__=0 -DBUILD_TESTS_MODE=OFF", true);
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            // Ensure we're using Clang and libc++ on Linux
            PublicSystemLibraries.Add("c++"); // This is the libc++ library
            PublicSystemLibraries.Add("pthread");

            // RoveComm_CPP
            PublicDefinitions.Add("BS_THREAD_POOL_ENABLE_PAUSE=1");
            CMakeTarget.add(Target, this, "RoveComm_CPP", Path.Combine(this.ModuleDirectory, "../ThirdParty/RoveComm_CPP"), "-D__ROVECOMM_LIBRARY_MODE__=0 -DBUILD_TESTS_MODE=OFF -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_FLAGS='-stdlib=libc++' -DCMAKE_EXE_LINKER_FLAGS='-stdlib=libc++ -lc++abi'", true);
        }
    }
}
