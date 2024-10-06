#pragma once

#include "RoveCommManifestWrapper.h"
#include "RoveCommPacket.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RoveCommPacketWrapper.generated.h"

// Blueprint-friendly wrapper for RoveCommPacket
UCLASS(BlueprintType)
class ROVESOSIMULATOR_API URoveCommPacketWrapper : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, Category = "RoveComm Packet")
    int32 DataId;

    UPROPERTY(BlueprintReadWrite, Category = "RoveComm Packet")
    int32 DataCount;

    UPROPERTY(BlueprintReadWrite, Category = "RoveComm Packet")
    EManifestDataType DataType;

    UPROPERTY(BlueprintReadWrite, Category = "RoveComm Packet")
    TArray<float> FloatData;

    UPROPERTY(BlueprintReadWrite, Category = "RoveComm Packet")
    TArray<int32> IntData;

    UPROPERTY(BlueprintReadWrite, Category = "RoveComm Packet")
    TArray<double> DoubleData;

    // Blueprint-exposed function to clear the data
    UFUNCTION(BlueprintCallable, Category = "RoveComm Packet")
    void ClearData()
    {
        FloatData.Empty();
        IntData.Empty();
        DoubleData.Empty();
    }

    // Function to set the data type
    UFUNCTION(BlueprintCallable, Category = "RoveComm Packet")
    void SetDataType(EManifestDataType NewDataType)
    {
        DataType = NewDataType;
    }

    // Functions to add data depending on type
    UFUNCTION(BlueprintCallable, Category = "RoveComm Packet")
    void AddFloatData(float Value)
    {
        if (DataType == EManifestDataType::FLOAT)
        {
            FloatData.Add(Value);
            DataCount = FloatData.Num();
        }
    }

    UFUNCTION(BlueprintCallable, Category = "RoveComm Packet")
    void AddIntData(int32 Value)
    {
        if (DataType == EManifestDataType::INT32)
        {
            IntData.Add(Value);
            DataCount = IntData.Num();
        }
    }

    UFUNCTION(BlueprintCallable, Category = "RoveComm Packet")
    void AddDoubleData(double Value)
    {
        if (DataType == EManifestDataType::DOUBLE)
        {
            DoubleData.Add(Value);
            DataCount = DoubleData.Num();
        }
    }
};
