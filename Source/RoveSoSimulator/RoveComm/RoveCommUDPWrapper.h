#pragma once

#include "CoreMinimal.h"
#include "RoveCommPacketWrapper.h"
#include "UObject/NoExportTypes.h"
#include "RoveCommUDPWrapper.generated.h"

// Forward declaration of your RoveCommUDP class from the RoveComm library
namespace rovecomm {
    class RoveCommUDP;
}

/**
 * @brief Blueprintable wrapper class for RoveCommUDP to allow usage in Unreal Engine Blueprints.
 */
UCLASS(Blueprintable, BlueprintType)
class ROVESOSIMULATOR_API URoveCommUDPWrapper : public UObject
{
    GENERATED_BODY()

public:
    // Constructor
    URoveCommUDPWrapper();

    // Destructor
    virtual ~URoveCommUDPWrapper();

    // Initialize the RoveComm UDP connection on a specified port
    UFUNCTION(BlueprintCallable, Category = "RoveComm UDP")
    bool InitUDPSocket(int32 Port);

    // Send a UDP packet
    UFUNCTION(BlueprintCallable, Category = "RoveComm UDP")
    bool SendPacket(URoveCommPacketWrapper* Packet, const FString& IPAddress, int32 Port);

    // Close the UDP socket
    UFUNCTION(BlueprintCallable, Category = "RoveComm UDP")
    void CloseUDPSocket();

protected:
    // Instance of the RoveCommUDP class
    rovecomm::RoveCommUDP* RoveCommUDPInstance;
};
