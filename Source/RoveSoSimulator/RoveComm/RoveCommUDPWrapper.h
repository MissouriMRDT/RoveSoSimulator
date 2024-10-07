#pragma once

#include "CoreMinimal.h"
#include <shared_mutex>
#include "RoveCommPacketWrapper.h"
#include "UObject/NoExportTypes.h"
#include "RoveCommUDPWrapper.generated.h"

// Forward declaration of your RoveCommUDP class from the RoveComm library
namespace rovecomm {
    class RoveCommUDP;
}

// Create events for when a packet is received.
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDriveDataReceived);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLEDPanelDataReceived);

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

    // Getter methods with shared lock
    UFUNCTION(BlueprintCallable, Category = "RoveComm UDP")
    TArray<float> GetDrivePowersCopy();
    UFUNCTION(BlueprintCallable, Category = "RoveComm UDP")
    TArray<uint8> GetLEDPanelRGBColorsCopy();

    // Getter method for RoveComm FPS.
    UFUNCTION(BlueprintCallable, Category = "RoveComm UDP")
    int32 GetRoveCommFPS();

    // Delegates.
    UPROPERTY(BlueprintAssignable, Category = "RoveComm UDP")
    FDriveDataReceived OnDriveDataReceived;
    UPROPERTY(BlueprintAssignable, Category = "RoveComm UDP")
    FLEDPanelDataReceived OnLEDPanelDataReceived;

protected:
    // Instance of the RoveCommUDP class
    rovecomm::RoveCommUDP* RoveCommUDPInstance;

private:
        // Declare member variables for drive powers and LED panel.
        TArray<float> DrivePowers;
        TArray<uint8> LEDPanelRGBColors;

        // Mutexes for the member variables. These are needed because the RoveComm callbacks run on a separate thread.
        std::shared_mutex DrivePowersMutex;
        std::shared_mutex LEDPanelRGBColorsMutex;

        /////////////////////////////////////////
        // RoveComm Callbacks.
        /////////////////////////////////////////
        
        /******************************************************************************
         * @brief Callback function that is called whenever RoveComm receives new Accuracy data.
         *
         *
         * @author clayjay3 (claytonraycowen@gmail.com)
         * @date 2024-03-03
         ******************************************************************************/
        const std::function<void(const rovecomm::RoveCommPacket<float>&, const sockaddr_in&)> ProcessDriveData =
            [this](const rovecomm::RoveCommPacket<float>& stPacket, const sockaddr_in& stdAddr)
        {
            // Not using this.
            (void) stdAddr;

            // Assuming stPacket.vData contains two elements: left and right drive power
            if (stPacket.vData.size() >= 2)
            {
                // Lock the mutex.
                std::unique_lock<std::shared_mutex> Lock(DrivePowersMutex);
                // Clear the drive powers.
                DrivePowers.Empty();
                // Add the new drive powers.
                DrivePowers.Add(stPacket.vData[0]);
                DrivePowers.Add(stPacket.vData[1]);
            }

            // Trigger the OnDriveDataReceived event on the game thread.
            AsyncTask(ENamedThreads::GameThread, [this]()
            {
                OnDriveDataReceived.Broadcast();
            });
        };
        
        /******************************************************************************
         * @brief Callback function that is called whenever RoveComm receives new RGB data.
         *
         *
         * @author clayjay3 (claytonraycowen@gmail.com)
         * @date 2024-03-03
         ******************************************************************************/
        const std::function<void(const rovecomm::RoveCommPacket<uint8_t>&, const sockaddr_in&)> ProcessRGBData =
            [this](const rovecomm::RoveCommPacket<uint8_t>& stPacket, const sockaddr_in& stdAddr)
        {
            // Not using this.
            (void) stdAddr;

            // Trigger the OnLEDPanelDataReceived event.
            // OnLEDPanelDataReceived.Broadcast();
        };
        
        /******************************************************************************
         * @brief Callback function that is called whenever RoveComm receives new StateDisplay data.
         *
         *
         * @author clayjay3 (claytonraycowen@gmail.com)
         * @date 2024-03-03
         ******************************************************************************/
        const std::function<void(const rovecomm::RoveCommPacket<uint8_t>&, const sockaddr_in&)> ProcessStateDisplayData =
            [this](const rovecomm::RoveCommPacket<uint8_t>& stPacket, const sockaddr_in& stdAddr)
        {
            // Not using this.
            (void) stdAddr;

            // // Determine display state.
            // switch (stPacket.vData[0])
            // {
            //     case 0:
            //     {
            //         // Teleop Blue
                    
            //         break;
            //     }
            //     case 1:
            //     {
            //         // Autonomy Red
                    
            //         break;
            //     }
            //     case 2:
            //     {
            //         // Goal Green
                    
            //         break;
            //     }
            //     default:
            //         break;
            // }

            // Trigger the OnLEDPanelDataReceived event on the game thread.
            // AsyncTask(ENamedThreads::GameThread, [this]()
            // {
            //     OnLEDPanelDataReceived.Broadcast();
            // });
        };
};
