#include "DepthShaderLibrary.h"
#include "Engine/TextureRenderTarget2D.h"
#include "RHICommandList.h"
#include "ShaderParameterUtils.h"
#include "RenderGraphUtils.h"
#include "RenderGraphResources.h"
#include "GlobalShader.h"
#include "ShaderParameterStruct.h"
#include "RenderGraphBuilder.h"
#include "RHIStaticStates.h"
#include "RHIUtilities.h"
#include "RHIGPUReadback.h" // Include this header for FRHIGPUBufferReadback

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

// Register the shader with the engine
IMPLEMENT_SHADER_TYPE(, FDepthReadCS, TEXT("/CustomShaders/DepthShader.usf"), TEXT("MainCS"), SF_Compute);

void UDepthShaderLibrary::ExecuteDepthShader(UTextureRenderTarget2D* InputRenderTarget, TArray<uint8>& OutData)
{
    if (!InputRenderTarget)
    {
        UE_LOG(LogTemp, Warning, TEXT("ExecuteDepthShader: Invalid render target provided"));
        return;
    }

    // Ensure the render target resource is accessed within the game thread
    FTextureRenderTargetResource* RenderTargetResource = InputRenderTarget->GameThread_GetRenderTargetResource();
    FTexture2DRHIRef InputTextureRHI = RenderTargetResource->TextureRHI;

    // Enqueue the render command
    ENQUEUE_RENDER_COMMAND(CaptureCommand)(
        [InputTextureRHI, &OutData](FRHICommandListImmediate& RHICmdList)
        {
            // Initialize the Render Graph
            FRDGBuilder GraphBuilder(RHICmdList);

            // Convert the RHI texture to RDG texture for the Render Graph
            FRDGTextureRef InputTexture = GraphBuilder.RegisterExternalTexture(CreateRenderTarget(InputTextureRHI, TEXT("InputTexture")));

            // Create an RDG buffer for the output
            FRDGBufferRef OutputBuffer = GraphBuilder.CreateBuffer(FRDGBufferDesc::CreateBufferDesc(sizeof(float), 1280 * 720), TEXT("OutputBuffer"));
            FRDGBufferUAVRef OutputBufferUAV = GraphBuilder.CreateUAV(OutputBuffer);

            // Set up shader parameters
            FDepthReadCS::FParameters* PassParameters = GraphBuilder.AllocParameters<FDepthReadCS::FParameters>();
            PassParameters->InputTexture = InputTexture;
            PassParameters->OutputBuffer = OutputBufferUAV;

            // Bind and dispatch the compute shader
            TShaderMapRef<FDepthReadCS> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
            
            const int32 GroupSizeX = FMath::DivideAndRoundUp(1280, 16);
            const int32 GroupSizeY = FMath::DivideAndRoundUp(720, 16);
            FComputeShaderUtils::AddPass(GraphBuilder, RDG_EVENT_NAME("ExecuteDepthShader"), ComputeShader, PassParameters, FIntVector(GroupSizeX, GroupSizeY, 1));

            // Execute the Render Graph
            GraphBuilder.Execute();

            // Read back the data from the GPU
            FRHIGPUBufferReadback ReadbackBuffer(TEXT("DepthReadback"));
            ReadbackBuffer.EnqueueCopy(RHICmdList, OutputBuffer->GetRHI());

            // Wait for the GPU to finish the readback
            RHICmdList.SubmitCommandsAndFlushGPU();
            RHICmdList.BlockUntilGPUIdle();

            // Map the readback buffer and copy the data
            void* BufferData = ReadbackBuffer.Lock(1280 * 720 * sizeof(float));
            TArray<float> DepthData;
            DepthData.SetNumUninitialized(1280 * 720);
            FMemory::Memcpy(DepthData.GetData(), BufferData, 1280 * 720 * sizeof(float));
            ReadbackBuffer.Unlock();

            // Serialize the data to a byte array
            OutData.SetNumUninitialized(DepthData.Num() * sizeof(float));
            FMemory::Memcpy(OutData.GetData(), DepthData.GetData(), OutData.Num());
        });
}