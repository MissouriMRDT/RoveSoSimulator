#include "DepthShaderLibrary.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "RHICommandList.h"
#include "ShaderParameterUtils.h"
#include "RenderGraphUtils.h"
#include "RenderGraphResources.h"
#include "GlobalShader.h"
#include "ShaderParameterStruct.h"
#include "RenderGraphBuilder.h"
#include "RHIStaticStates.h"
#include "RHIUtilities.h"
#include "RHIGPUReadback.h"
#include "RHI.h"

// Define the compute shader class
class FDepthReadCS : public FGlobalShader
{
    DECLARE_GLOBAL_SHADER(FDepthReadCS);
    SHADER_USE_PARAMETER_STRUCT(FDepthReadCS, FGlobalShader);

    BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
        SHADER_PARAMETER_RDG_TEXTURE(Texture2D<float>, InputTexture)
        SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, OutputBuffer)
    END_SHADER_PARAMETER_STRUCT()
};

IMPLEMENT_SHADER_TYPE(, FDepthReadCS, TEXT("/CustomShaders/DepthShader.usf"), TEXT("MainCS"), SF_Compute);

void UDepthShaderLibrary::ExecuteDepthShader(UTextureRenderTarget2D* InputRenderTarget, TArray<uint8>& OutData)
{
    
}

bool UDepthShaderLibrary::GetRenderTargetDepthData(UTextureRenderTarget2D* RenderTarget, TArray<uint8>& OutByteArray)
{
    if (!RenderTarget)
    {
        UE_LOG(LogTemp, Warning, TEXT("RenderTarget is null"));
        return false;
    }

    // Get the render target resource
    FTextureRenderTargetResource* RenderTargetResource = RenderTarget->GameThread_GetRenderTargetResource();
    if (!RenderTargetResource)
    {
        UE_LOG(LogTemp, Warning, TEXT("RenderTarget resource is null"));
        return false;
    }

    // Read the depth data as an array of FFloat16Color
    TArray<FFloat16Color> DepthData;
    RenderTargetResource->ReadFloat16Pixels(DepthData);

    // Clear the output byte array
    OutByteArray.Empty();

    // Reserve enough space in the byte array (4 bytes per pixel)
    OutByteArray.Reserve(DepthData.Num() * sizeof(float));

    // Convert depth data to a byte array
    for (const FFloat16Color& Pixel : DepthData)
    {
        // Depth is typically stored in the red channel when Capture Source is set to Scene Depth
        float DepthValue = Pixel.R;

        // Convert float to byte array (4 bytes)
        uint8* DepthBytes = reinterpret_cast<uint8*>(&DepthValue);
        OutByteArray.Append(DepthBytes, sizeof(float));
    }

    return true;
}
