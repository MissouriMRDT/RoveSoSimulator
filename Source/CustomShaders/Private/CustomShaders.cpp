// CustomShaders/Private/CustomShaders.cpp

#include "CustomShaders.h"

void FCustomShaders::StartupModule() {
	FString BaseDir = FPaths::Combine(FPaths::GameSourceDir(), TEXT("CustomShaders"));
	FString ModuleShaderDir = FPaths::Combine(BaseDir, TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/CustomShaders"), ModuleShaderDir);
}

IMPLEMENT_MODULE(FCustomShaders, CustomShaders)