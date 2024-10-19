#include "RoveCommManifestWrapper.h"

// Function to retrieve the IP Address as a string for a specified board
FString URoveCommManifestWrapper::GetIPAddress(const FString& BoardName)
{
    const manifest::AddressEntry* addressEntry = nullptr;

    if (BoardName.Equals("Core", ESearchCase::IgnoreCase))
    {
        addressEntry = &manifest::Core::IP_ADDRESS;
    }
    else if (BoardName.Equals("PMS", ESearchCase::IgnoreCase))
    {
        addressEntry = &manifest::PMS::IP_ADDRESS;
    }
    else if (BoardName.Equals("Nav", ESearchCase::IgnoreCase))
    {
        addressEntry = &manifest::Nav::IP_ADDRESS;
    }

    if (addressEntry)
    {
        return FString::Printf(TEXT("%d.%d.%d.%d"), 
            addressEntry->FIRST_OCTET, 
            addressEntry->SECOND_OCTET, 
            addressEntry->THIRD_OCTET, 
            addressEntry->FOURTH_OCTET);
    }
    
    return TEXT("Invalid Board Name");
}

// Function to get command details for a specified board
bool URoveCommManifestWrapper::GetCommandDetails(const FString& BoardName, const FString& CommandName, int32& DataId, int32& DataCount, EManifestDataType& DataType)
{
    const std::map<std::string, manifest::ManifestEntry>* commands = nullptr;

    if (BoardName.Equals("Core", ESearchCase::IgnoreCase))
    {
        commands = &manifest::Core::COMMANDS;
    }
    else if (BoardName.Equals("PMS", ESearchCase::IgnoreCase))
    {
        commands = &manifest::PMS::COMMANDS;
    }
    else if (BoardName.Equals("Nav", ESearchCase::IgnoreCase))
    {
        commands = &manifest::Nav::COMMANDS;
    }
    else if (BoardName.Equals("Autonomy", ESearchCase::IgnoreCase))
    {
        commands = &manifest::Autonomy::COMMANDS;
    }

    if (commands)
    {
        auto it = commands->find(TCHAR_TO_UTF8(*CommandName));
        if (it != commands->end())
        {
            const manifest::ManifestEntry& entry = it->second;
            DataId = entry.DATA_ID;
            DataCount = entry.DATA_COUNT;
            DataType = static_cast<EManifestDataType>(entry.DATA_TYPE);
            return true;  // Command found
        }
    }
    return false;  // Command not found
}

// Function to get telemetry details for a specified board
bool URoveCommManifestWrapper::GetTelemetryDetails(const FString& BoardName, const FString& TelemetryName, int32& DataId, int32& DataCount, EManifestDataType& DataType)
{
    const std::map<std::string, manifest::ManifestEntry>* telemetry = nullptr;

    if (BoardName.Equals("Core", ESearchCase::IgnoreCase))
    {
        telemetry = &manifest::Core::TELEMETRY;
    }
    else if (BoardName.Equals("PMS", ESearchCase::IgnoreCase))
    {
        telemetry = &manifest::PMS::TELEMETRY;
    }
    else if (BoardName.Equals("Nav", ESearchCase::IgnoreCase))
    {
        telemetry = &manifest::Nav::TELEMETRY;
    }

    if (telemetry)
    {
        auto it = telemetry->find(TCHAR_TO_UTF8(*TelemetryName));
        if (it != telemetry->end())
        {
            const manifest::ManifestEntry& entry = it->second;
            DataId = entry.DATA_ID;
            DataCount = entry.DATA_COUNT;
            DataType = static_cast<EManifestDataType>(entry.DATA_TYPE);
            return true;  // Telemetry found
        }
    }
    return false;  // Telemetry not found
}
