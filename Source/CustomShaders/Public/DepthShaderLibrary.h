#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DepthShaderLibrary.generated.h"

/**
 * A Blueprint-accessible function library for executing depth read compute shader
 */
UCLASS()
class CUSTOMSHADERS_API UDepthShaderLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /**
     * Executes a compute shader to read depth data from an input render target and serialize it to a byte array.
     * @param InputRenderTarget - The render target containing depth data.
     * @param OutData - The byte array to which the shader will write serialized depth data.
     */
    UFUNCTION(BlueprintCallable, Category = "Rendering")
    static void ExecuteDepthShader(UTextureRenderTarget2D* InputRenderTarget, TArray<uint8>& OutData);
};