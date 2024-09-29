#include "RoveCommUDPWrapper.h"
#include "RoveCommUDP.h"  // Include your RoveCommUDP class definition

// Constructor
URoveCommUDPWrapper::URoveCommUDPWrapper()
{
    // Instantiate the RoveCommUDP instance
    RoveCommUDPInstance = new rovecomm::RoveCommUDP();
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
    }
}

bool URoveCommUDPWrapper::InitUDPSocket(int32 Port)
{
    if (RoveCommUDPInstance)
    {
        return RoveCommUDPInstance->InitUDPSocket(Port);
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
