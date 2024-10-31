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
     * Blueprint Callable Function to get depth data from a render target as a byte array.
     * @param RenderTarget - The Render Target to read data from.
     * @param OutByteArray - Output byte array of depth data.
     * @return - True if the data was successfully retrieved, false otherwise.
     */
    UFUNCTION(BlueprintCallable, Category = "Render Target")
    static bool GetRenderTargetData(UTextureRenderTarget2D* RenderTarget, TArray<uint8>& OutByteArray);
};