#pragma once

#include <map>
#include "RoveCommManifest.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RoveCommManifestWrapper.generated.h"


// Enum to represent data types in Blueprints
UENUM(BlueprintType)
enum class EManifestDataType : uint8
{
    INT8 UMETA(DisplayName = "Int8"),
    UINT8 UMETA(DisplayName = "Uint8"),
    INT16 UMETA(DisplayName = "Int16"),
    UINT16 UMETA(DisplayName = "Uint16"),
    INT32 UMETA(DisplayName = "Int32"),
    UINT32 UMETA(DisplayName = "Uint32"),
    FLOAT UMETA(DisplayName = "Float"),
    DOUBLE UMETA(DisplayName = "Double"),
    CHAR UMETA(DisplayName = "Char"),
};

UCLASS(Blueprintable)
class ROVESOSIMULATOR_API URoveCommManifestWrapper : public UObject
{
    GENERATED_BODY()

public:
    // Blueprint callable function to get IP address for a specific board
    UFUNCTION(BlueprintCallable, Category = "RoveComm Manifest")
    FString GetIPAddress(const FString& BoardName);

    // Blueprint callable function to get command details for a specific board
    UFUNCTION(BlueprintCallable, Category = "RoveComm Manifest")
    bool GetCommandDetails(const FString& BoardName, const FString& CommandName, int32& DataId, int32& DataCount, EManifestDataType& DataType);

    // Blueprint callable function to get telemetry details for a specific board
    UFUNCTION(BlueprintCallable, Category = "RoveComm Manifest")
    bool GetTelemetryDetails(const FString& BoardName, const FString& TelemetryName, int32& DataId, int32& DataCount, EManifestDataType& DataType);
};
