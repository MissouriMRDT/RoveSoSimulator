// CustomShaders/CustomShaders.Build.cs

using UnrealBuildTool;
using System.Collections.Generic;
using System.IO;
public class CustomShaders : ModuleRules {
    public CustomShaders(ReadOnlyTargetRules Target) : base(Target) {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "Renderer", "RenderCore", "RHI"});

        string EnginePath = Path.GetFullPath(Target.RelativeEnginePath);
        PublicIncludePaths.Add(EnginePath + "Source/Runtime/Renderer/Private");
    }
}