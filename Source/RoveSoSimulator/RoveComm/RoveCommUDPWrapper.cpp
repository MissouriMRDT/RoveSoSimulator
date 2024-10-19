#include "RoveCommUDPWrapper.h"
#include "RoveCommUDP.h"  // Include your RoveCommUDP class definition

// Constructor
URoveCommUDPWrapper::URoveCommUDPWrapper()
{
    // Instantiate the RoveCommUDP instance
    RoveCommUDPInstance = new rovecomm::RoveCommUDP();

    // Initialize DrivePowers and LEDPanelRGBColors
    DrivePowers.Init(0.0f, 2);
    LEDPanelRGBColors.Init(0, 3);
}

// Destructor
URoveCommUDPWrapper::~URoveCommUDPWrapper()
{
    // Cleanup the RoveCommUDP instance
    if (RoveCommUDPInstance)
    {
        RoveCommUDPInstance->CloseUDPSocket();
        delete RoveCommUDPInstance;
        RoveCommUDPInstance = nullptr;
        this->ConditionalBeginDestroy();
    }
}

bool URoveCommUDPWrapper::InitUDPSocket(int32 Port)
{
    if (RoveCommUDPInstance)
    {
        // Init RoveCommUDP socket.
        bool bInitialized = RoveCommUDPInstance->InitUDPSocket(Port);
        // Add the callback functions.
        RoveCommUDPInstance->AddUDPCallback(ProcessDriveData, manifest::Core::COMMANDS.find("DRIVELEFTRIGHT")->second.DATA_ID);
        RoveCommUDPInstance->AddUDPCallback(ProcessRGBData, manifest::Core::COMMANDS.find("LEDRGB")->second.DATA_ID);
        RoveCommUDPInstance->AddUDPCallback(ProcessStateDisplayData, manifest::Core::COMMANDS.find("STATEDISPLAY")->second.DATA_ID);

        return bInitialized;
    }
    return false;
}

bool URoveCommUDPWrapper::SendPacket(URoveCommPacketWrapper* Packet, const FString& IPAddress, int32 Port)
{
    if (RoveCommUDPInstance && Packet)
    {
        std::string IPAddressStd = TCHAR_TO_UTF8(*IPAddress);

        // Switch based on the data type of the packet
        switch (Packet->DataType)
        {
            case EManifestDataType::FLOAT:
            {
                rovecomm::RoveCommPacket<float> stPacket;
                stPacket.unDataId = Packet->DataId;
                stPacket.unDataCount = Packet->DataCount;
                stPacket.eDataType = manifest::DataTypes::FLOAT_T;
                stPacket.vData = std::vector<float>(Packet->FloatData.GetData(), Packet->FloatData.GetData() + Packet->FloatData.Num());
                ssize_t Result = RoveCommUDPInstance->SendUDPPacket(stPacket, IPAddressStd.c_str(), Port);
                return (Result != -1);
            }
            case EManifestDataType::UINT8:
            {
                rovecomm::RoveCommPacket<uint8> stPacket;
                stPacket.unDataId = Packet->DataId;
                stPacket.unDataCount = Packet->DataCount;
                stPacket.eDataType = manifest::DataTypes::UINT8_T;
                stPacket.vData = std::vector<uint8>(Packet->Uint8Data.GetData(), Packet->Uint8Data.GetData() + Packet->Uint8Data.Num());
                ssize_t Result = RoveCommUDPInstance->SendUDPPacket(stPacket, IPAddressStd.c_str(), Port);
                return (Result != -1);
            }
            case EManifestDataType::INT32:
            {
                rovecomm::RoveCommPacket<int32> stPacket;
                stPacket.unDataId = Packet->DataId;
                stPacket.unDataCount = Packet->DataCount;
                stPacket.eDataType = manifest::DataTypes::INT32_T;
                stPacket.vData = std::vector<int32>(Packet->IntData.GetData(), Packet->IntData.GetData() + Packet->IntData.Num());
                ssize_t Result = RoveCommUDPInstance->SendUDPPacket(stPacket, IPAddressStd.c_str(), Port);
                return (Result != -1);
            }
            case EManifestDataType::DOUBLE:
            {
                rovecomm::RoveCommPacket<double> stPacket;
                stPacket.unDataId = Packet->DataId;
                stPacket.unDataCount = Packet->DataCount;
                stPacket.eDataType = manifest::DataTypes::DOUBLE_T;
                stPacket.vData = std::vector<double>(Packet->DoubleData.GetData(), Packet->DoubleData.GetData() + Packet->DoubleData.Num());
                ssize_t Result = RoveCommUDPInstance->SendUDPPacket(stPacket, IPAddressStd.c_str(), Port);
                return (Result != -1);
            }
            default:
                UE_LOG(LogTemp, Warning, TEXT("Unsupported data type"));
                return false;
        }
    }

    return false;
}


void URoveCommUDPWrapper::CloseUDPSocket()
{
    if (RoveCommUDPInstance)
    {
        RoveCommUDPInstance->CloseUDPSocket();
    }
}

// Getter methods for RoveComm data with shared lock and deep copy using FMemory::Memcpy.
TArray<float> URoveCommUDPWrapper::GetDrivePowersCopy()
{
    std::shared_lock<std::shared_mutex> lock(DrivePowersMutex);
    TArray<float> DeepCopy;
    // Check if DrivePowers is empty. If is empty, return a TArray with 0.0f, 0.0f.
    if (DrivePowers.Num() == 0)
    {
        DeepCopy.Init(0.0f, 2);
        return DeepCopy;
    }
    DeepCopy.AddUninitialized(DrivePowers.Num());
    FMemory::Memcpy(DeepCopy.GetData(), DrivePowers.GetData(), DrivePowers.Num() * sizeof(float));
    return DeepCopy;
}

TArray<uint8> URoveCommUDPWrapper::GetLEDPanelRGBColorsCopy()
{
    std::shared_lock<std::shared_mutex> lock(LEDPanelRGBColorsMutex);
    TArray<uint8> DeepCopy;
    // Check if LEDPanelRGBColors is empty. If is empty, return a TArray with 0, 0, 0.
    if (LEDPanelRGBColors.Num() == 0)
    {
        DeepCopy.Init(0, 3);
        return DeepCopy;
    }
    DeepCopy.AddUninitialized(LEDPanelRGBColors.Num());
    FMemory::Memcpy(DeepCopy.GetData(), LEDPanelRGBColors.GetData(), LEDPanelRGBColors.Num() * sizeof(uint8));
    return DeepCopy;
}

// Getter methods for RoveComm FPS.
int32 URoveCommUDPWrapper::GetRoveCommFPS()
{
    if (RoveCommUDPInstance)
    {
        return static_cast<int32>(RoveCommUDPInstance->GetIPS().GetExactIPS());
    }
    return 0;
}
