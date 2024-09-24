/******************************************************************************
 * @brief RoveComm Manifest
 *
 *        NOTICE! This file is auto generated and will be overwritten if edited
 *                and committed. To make changes edit the manifest.json file or
 *                edit parser.py if it is a formatting issue.
 *
 * @file RoveCommManifest.h
 * @author Missouri S&T - Mars Rover Design Team
 * @date 2024-05-27
 *
 * @copyright Copyright Mars Rover Design Team 2024 - All Rights Reserved
 ******************************************************************************/

#ifndef MANIFEST_H
#define MANIFEST_H

#include <map>
#include <stdint.h>
#include <string>

namespace manifest
{
    /******************************************************************************
     * @brief Enumeration of Data Types to be used in RoveComm
     *
     * @author Missouri S&T - Mars Rover Design Team
     * @date 2024-05-27
     ******************************************************************************/
    enum DataTypes
    {
        INT8_T,
        UINT8_T,
        INT16_T,
        UINT16_T,
        INT32_T,
        UINT32_T,
        FLOAT_T,
        DOUBLE_T,
        CHAR
    };

    /******************************************************************************
     * @brief IP Address Object for RoveComm.
     *
     * @author Missouri S&T - Mars Rover Design Team
     * @date 2024-05-27
     ******************************************************************************/
    struct AddressEntry
    {
        public:
            int FIRST_OCTET;
            int SECOND_OCTET;
            int THIRD_OCTET;
            int FOURTH_OCTET;
            std::string IP_STR = std::to_string(FIRST_OCTET) + "." + std::to_string(SECOND_OCTET) + "." + std::to_string(THIRD_OCTET) + "." + std::to_string(FOURTH_OCTET);
    };

    /******************************************************************************
     * @brief Manifest Entry Object for RoveComm.
     *
     * @author Missouri S&T - Mars Rover Design Team
     * @date 2024-05-27
     ******************************************************************************/
    struct ManifestEntry
    {
        public:
            int DATA_ID;
            int DATA_COUNT;
            DataTypes DATA_TYPE;
    };

    /******************************************************************************
     * @brief Core Board IP Address, Commands, Telemetry, and Error Packet 
     *
     * @author Missouri S&T - Mars Rover Design Team
     * @date 2024-05-27
     ******************************************************************************/
    namespace Core
    {
        // IP Address
        const AddressEntry IP_ADDRESS{192, 168, 2, 110};

        // Commands
        const std::map<std::string, ManifestEntry> COMMANDS = {
            {"DRIVELEFTRIGHT", ManifestEntry{3000, 2, DataTypes::FLOAT_T}},
            {"DRIVEINDIVIDUAL", ManifestEntry{3001, 6, DataTypes::FLOAT_T}},
            {"WATCHDOGOVERRIDE", ManifestEntry{3002, 1, DataTypes::UINT8_T}},
            {"LEFTDRIVEGIMBALINCREMENT", ManifestEntry{3003, 1, DataTypes::INT16_T}},
            {"RIGHTDRIVEGIMBALINCREMENT", ManifestEntry{3004, 1, DataTypes::INT16_T}},
            {"LEFTMAINGIMBALINCREMENT", ManifestEntry{3005, 2, DataTypes::INT16_T}},
            {"RIGHTMAINGIMBALINCREMENT", ManifestEntry{3006, 2, DataTypes::INT16_T}},
            {"BACKDRIVEGIMBALINCREMENT", ManifestEntry{3007, 1, DataTypes::INT16_T}},
            {"LEDRGB", ManifestEntry{3008, 3, DataTypes::UINT8_T}},
            {"LEDPATTERNS", ManifestEntry{3009, 1, DataTypes::UINT8_T}},
            {"STATEDISPLAY", ManifestEntry{3010, 1, DataTypes::UINT8_T}},
            {"BRIGHTNESS", ManifestEntry{3011, 1, DataTypes::UINT8_T}},
            {"SETWATCHDOGMODE", ManifestEntry{3012, 1, DataTypes::UINT8_T}},
            {"LEDTEXT", ManifestEntry{3013, 256, DataTypes::CHAR}},
        };

        // Telemetry
        const std::map<std::string, ManifestEntry> TELEMETRY = {
            {"DRIVESPEEDS", ManifestEntry{3100, 6, DataTypes::FLOAT_T}},
            {"IMUDATA", ManifestEntry{3101, 3, DataTypes::FLOAT_T}},
            {"ACCELEROMETERDATA", ManifestEntry{3102, 3, DataTypes::FLOAT_T}},
        };

        // Error
        const std::map<std::string, ManifestEntry> ERROR = {};
        
        // Enums
        enum class DISPLAYSTATE
        {
            TELEOP,
            AUTONOMY,
            REACHED_GOAL
        }; 

        enum class PATTERNS
        {
            MRDT,
            BELGIUM,
            MERICA,
            DIRT,
            DOTA,
            MCD,
            WINDOWS
        }; 

    }    // namespace Core

    /******************************************************************************
     * @brief PMS Board IP Address, Commands, Telemetry, and Error Packet 
     *
     * @author Missouri S&T - Mars Rover Design Team
     * @date 2024-05-27
     ******************************************************************************/
    namespace PMS
    {
        // IP Address
        const AddressEntry IP_ADDRESS{192, 168, 2, 102};

        // Commands
        const std::map<std::string, ManifestEntry> COMMANDS = {
            {"ESTOP", ManifestEntry{4000, 1, DataTypes::UINT8_T}},
            {"SUICIDE", ManifestEntry{4001, 1, DataTypes::UINT8_T}},
            {"REBOOT", ManifestEntry{4002, 1, DataTypes::UINT8_T}},
            {"ENABLEBUS", ManifestEntry{4003, 1, DataTypes::UINT8_T}},
            {"DISABLEBUS", ManifestEntry{4004, 1, DataTypes::UINT8_T}},
            {"SETBUS", ManifestEntry{4005, 1, DataTypes::UINT8_T}},
        };

        // Telemetry
        const std::map<std::string, ManifestEntry> TELEMETRY = {
            {"PACKCURRENT", ManifestEntry{4100, 1, DataTypes::FLOAT_T}},
            {"PACKVOLTAGE", ManifestEntry{4101, 1, DataTypes::FLOAT_T}},
            {"CELLVOLTAGE", ManifestEntry{4102, 6, DataTypes::FLOAT_T}},
            {"AUXCURRENT", ManifestEntry{4103, 1, DataTypes::FLOAT_T}},
            {"MISCCURRENT", ManifestEntry{4104, 3, DataTypes::FLOAT_T}},
            {"BUSSTATUS", ManifestEntry{4105, 1, DataTypes::UINT8_T}},
        };

        // Error
        const std::map<std::string, ManifestEntry> ERROR = {
            {"PACKOVERCURRENT", ManifestEntry{4200, 1, DataTypes::UINT8_T}},
            {"CELLUNDERVOLTAGE", ManifestEntry{4201, 1, DataTypes::UINT8_T}},
            {"CELLCRITICAL", ManifestEntry{4202, 1, DataTypes::UINT8_T}},
            {"AUXOVERCURRENT", ManifestEntry{4203, 1, DataTypes::UINT8_T}},
        };
    }    // namespace PMS

    /******************************************************************************
     * @brief Nav Board IP Address, Commands, Telemetry, and Error Packet 
     *
     * @author Missouri S&T - Mars Rover Design Team
     * @date 2024-05-27
     ******************************************************************************/
    namespace Nav
    {
        // IP Address
        const AddressEntry IP_ADDRESS{192, 168, 2, 104};

        // Commands
        const std::map<std::string, ManifestEntry> COMMANDS = {};
        // Telemetry
        const std::map<std::string, ManifestEntry> TELEMETRY = {
            {"GPSLATLONALT", ManifestEntry{6100, 3, DataTypes::DOUBLE_T}},
            {"IMUDATA", ManifestEntry{6101, 3, DataTypes::FLOAT_T}},
            {"COMPASSDATA", ManifestEntry{6102, 1, DataTypes::FLOAT_T}},
            {"SATELLITECOUNTDATA", ManifestEntry{6103, 1, DataTypes::UINT8_T}},
            {"ACCELEROMETERDATA", ManifestEntry{6104, 3, DataTypes::FLOAT_T}},
            {"ACCURACYDATA", ManifestEntry{6105, 5, DataTypes::FLOAT_T}},
        };

        // Error
        const std::map<std::string, ManifestEntry> ERROR = {
            {"GPSLOCKERROR", ManifestEntry{6200, 1, DataTypes::UINT8_T}},
        };
    }    // namespace Nav

    /******************************************************************************
     * @brief BaseStationNav Board IP Address, Commands, Telemetry, and Error 
     *
     * @author Missouri S&T - Mars Rover Design Team
     * @date 2024-05-27
     ******************************************************************************/
    namespace BaseStationNav
    {
        // IP Address
        const AddressEntry IP_ADDRESS{192, 168, 100, 112};

        // Commands
        const std::map<std::string, ManifestEntry> COMMANDS = {};
        // Telemetry
        const std::map<std::string, ManifestEntry> TELEMETRY = {};
        // Error
        const std::map<std::string, ManifestEntry> ERROR = {};
    }    // namespace BaseStationNav

    /******************************************************************************
     * @brief SignalStack Board IP Address, Commands, Telemetry, and Error Packet 
     *
     * @author Missouri S&T - Mars Rover Design Team
     * @date 2024-05-27
     ******************************************************************************/
    namespace SignalStack
    {
        // IP Address
        const AddressEntry IP_ADDRESS{192, 168, 100, 101};

        // Commands
        const std::map<std::string, ManifestEntry> COMMANDS = {
            {"OPENLOOP", ManifestEntry{7000, 1, DataTypes::INT16_T}},
            {"SETANGLETARGET", ManifestEntry{7001, 1, DataTypes::FLOAT_T}},
            {"SETGPSTARGET", ManifestEntry{7002, 4, DataTypes::DOUBLE_T}},
            {"WATCHDOGOVERRIDE", ManifestEntry{7003, 1, DataTypes::UINT8_T}},
        };

        // Telemetry
        const std::map<std::string, ManifestEntry> TELEMETRY = {
            {"COMPASSANGLE", ManifestEntry{7100, 1, DataTypes::FLOAT_T}},
        };

        // Error
        const std::map<std::string, ManifestEntry> ERROR = {
            {"WATCHDOGSTATUS", ManifestEntry{7200, 1, DataTypes::UINT8_T}},
        };
    }    // namespace SignalStack

    /******************************************************************************
     * @brief Arm Board IP Address, Commands, Telemetry, and Error Packet 
     *
     * @author Missouri S&T - Mars Rover Design Team
     * @date 2024-05-27
     ******************************************************************************/
    namespace Arm
    {
        // IP Address
        const AddressEntry IP_ADDRESS{192, 168, 2, 107};

        // Commands
        const std::map<std::string, ManifestEntry> COMMANDS = {
            {"OPENLOOP", ManifestEntry{8000, 6, DataTypes::INT16_T}},
            {"SETPOSITION", ManifestEntry{8001, 6, DataTypes::FLOAT_T}},
            {"INCREMENTPOSITION", ManifestEntry{8002, 5, DataTypes::FLOAT_T}},
            {"SETIK", ManifestEntry{8003, 5, DataTypes::FLOAT_T}},
            {"INCREMENTIK_ROVERRELATIVE", ManifestEntry{8004, 5, DataTypes::FLOAT_T}},
            {"INCREMENTIK_WRISTRELATIVE", ManifestEntry{8005, 5, DataTypes::FLOAT_T}},
            {"LASER", ManifestEntry{8006, 1, DataTypes::UINT8_T}},
            {"SOLENOID", ManifestEntry{8007, 1, DataTypes::UINT8_T}},
            {"GRIPPER", ManifestEntry{8008, 1, DataTypes::INT16_T}},
            {"WATCHDOGOVERRIDE", ManifestEntry{8009, 1, DataTypes::UINT8_T}},
            {"LIMITSWITCHOVERRIDE", ManifestEntry{8010, 1, DataTypes::UINT16_T}},
            {"CALIBRATEENCODER", ManifestEntry{8011, 1, DataTypes::UINT8_T}},
            {"SELECTGRIPPER", ManifestEntry{8012, 1, DataTypes::UINT8_T}},
            {"SOFTLIMITOVERRIDE", ManifestEntry{8013, 1, DataTypes::UINT8_T}},
        };

        // Telemetry
        const std::map<std::string, ManifestEntry> TELEMETRY = {
            {"POSITIONS", ManifestEntry{8100, 7, DataTypes::FLOAT_T}},
            {"COORDINATES", ManifestEntry{8101, 5, DataTypes::FLOAT_T}},
            {"LIMITSWITCHTRIGGERED", ManifestEntry{8102, 1, DataTypes::UINT16_T}},
        };

        // Error
        const std::map<std::string, ManifestEntry> ERROR = {
            {"WATCHDOGSTATUS", ManifestEntry{8200, 1, DataTypes::UINT8_T}},
        };
    }    // namespace Arm

    /******************************************************************************
     * @brief ScienceActuation Board IP Address, Commands, Telemetry, and Error 
     *
     * @author Missouri S&T - Mars Rover Design Team
     * @date 2024-05-27
     ******************************************************************************/
    namespace ScienceActuation
    {
        // IP Address
        const AddressEntry IP_ADDRESS{192, 168, 2, 108};

        // Commands
        const std::map<std::string, ManifestEntry> COMMANDS = {
            {"SCOOPAXIS_OPENLOOP", ManifestEntry{9000, 1, DataTypes::INT16_T}},
            {"SENSORAXIS_OPENLOOP", ManifestEntry{9001, 1, DataTypes::INT16_T}},
            {"SCOOPAXIS_SETPOSITION", ManifestEntry{9002, 1, DataTypes::FLOAT_T}},
            {"SENSORAXIS_SETPOSITION", ManifestEntry{9003, 1, DataTypes::FLOAT_T}},
            {"SCOOPAXIS_INCREMENTPOSITION", ManifestEntry{9004, 1, DataTypes::FLOAT_T}},
            {"SENSORAXIS_INCREMENTPOSITION", ManifestEntry{9005, 1, DataTypes::FLOAT_T}},
            {"LIMITSWITCHOVERRIDE", ManifestEntry{9006, 1, DataTypes::UINT8_T}},
            {"AUGER", ManifestEntry{9007, 1, DataTypes::INT16_T}},
            {"MICROSCOPE", ManifestEntry{9008, 1, DataTypes::UINT8_T}},
            {"WATCHDOGOVERRIDE", ManifestEntry{9010, 1, DataTypes::UINT8_T}},
            {"CALIBRATEENCODER", ManifestEntry{9011, 1, DataTypes::UINT8_T}},
            {"REQUESTHUMIDITY", ManifestEntry{9012, 1, DataTypes::UINT8_T}},
            {"AUGERGIMBALINCREMENT", ManifestEntry{9013, 2, DataTypes::INT16_T}},
        };

        // Telemetry
        const std::map<std::string, ManifestEntry> TELEMETRY = {
            {"POSITIONS", ManifestEntry{9100, 2, DataTypes::FLOAT_T}},
            {"LIMITSWITCHTRIGGERED", ManifestEntry{9101, 1, DataTypes::UINT8_T}},
            {"HUMIDITY", ManifestEntry{9102, 1, DataTypes::FLOAT_T}},
            {"AUGERSPEED", ManifestEntry{9103, 1, DataTypes::FLOAT_T}},
        };

        // Error
        const std::map<std::string, ManifestEntry> ERROR = {
            {"WATCHDOGSTATUS", ManifestEntry{9200, 1, DataTypes::UINT8_T}},
            {"AUGERSTALLED", ManifestEntry{9201, 1, DataTypes::UINT8_T}},
        };
    }    // namespace ScienceActuation

    /******************************************************************************
     * @brief Autonomy Board IP Address, Commands, Telemetry, and Error Packet 
     *
     * @author Missouri S&T - Mars Rover Design Team
     * @date 2024-05-27
     ******************************************************************************/
    namespace Autonomy
    {
        // IP Address
        const AddressEntry IP_ADDRESS{192, 168, 3, 100};

        // Commands
        const std::map<std::string, ManifestEntry> COMMANDS = {
            {"STARTAUTONOMY", ManifestEntry{11000, 1, DataTypes::UINT8_T}},
            {"DISABLEAUTONOMY", ManifestEntry{11001, 1, DataTypes::UINT8_T}},
            {"ADDPOSITIONLEG", ManifestEntry{11002, 2, DataTypes::DOUBLE_T}},
            {"ADDMARKERLEG", ManifestEntry{11003, 2, DataTypes::DOUBLE_T}},
            {"ADDOBJECTLEG", ManifestEntry{11004, 2, DataTypes::DOUBLE_T}},
            {"CLEARWAYPOINTS", ManifestEntry{11005, 1, DataTypes::UINT8_T}},
            {"SETMAXSPEED", ManifestEntry{11006, 1, DataTypes::FLOAT_T}},
            {"SETLOGGINGLEVELS", ManifestEntry{11007, 3, DataTypes::UINT8_T}},
        };

        // Telemetry
        const std::map<std::string, ManifestEntry> TELEMETRY = {
            {"CURRENTSTATE", ManifestEntry{11100, 1, DataTypes::UINT8_T}},
            {"REACHEDGOAL", ManifestEntry{11101, 1, DataTypes::UINT8_T}},
            {"CURRENTLOG", ManifestEntry{11102, 255, DataTypes::CHAR}},
        };

        // Error
        const std::map<std::string, ManifestEntry> ERROR = {};
        
        // Enums
        enum class AUTONOMYSTATE
        {
            IDLE,
            NAVIGATING,
            SEARCHPATTERN,
            APPROACHINGMARKER,
            APPROACHINGOBJECT,
            VERIFYINGGPS,
            VERIFYINGMARKER,
            VERIFYINGOBJECT,
            AVOIDANCE,
            REVERSING,
            STUCK
        }; 

        enum class AUTONOMYLOG
        {
            TRACEL3,
            TRACEL2,
            TRACEL1,
            DEBUG,
            INFO,
            WARNING,
            ERROR,
            CRITICAL
        }; 

    }    // namespace Autonomy

    /******************************************************************************
     * @brief Camera1 Board IP Address, Commands, Telemetry, and Error Packet 
     *
     * @author Missouri S&T - Mars Rover Design Team
     * @date 2024-05-27
     ******************************************************************************/
    namespace Camera1
    {
        // IP Address
        const AddressEntry IP_ADDRESS{192, 168, 4, 100};

        // Commands
        const std::map<std::string, ManifestEntry> COMMANDS = {
            {"CHANGECAMERAS", ManifestEntry{12000, 2, DataTypes::UINT8_T}},
            {"TAKEPICTURE", ManifestEntry{12001, 2, DataTypes::UINT8_T}},
            {"TOGGLESTREAM1", ManifestEntry{12002, 2, DataTypes::UINT8_T}},
        };

        // Telemetry
        const std::map<std::string, ManifestEntry> TELEMETRY = {
            {"AVAILABLECAMERAS", ManifestEntry{12100, 1, DataTypes::UINT8_T}},
            {"STREAMINGCAMERAS", ManifestEntry{12101, 4, DataTypes::UINT8_T}},
            {"PICTURETAKEN1", ManifestEntry{12102, 1, DataTypes::UINT8_T}},
        };

        // Error
        const std::map<std::string, ManifestEntry> ERROR = {
            {"CAMERAUNAVAILABLE", ManifestEntry{12200, 1, DataTypes::UINT8_T}},
        };
    }    // namespace Camera1

    /******************************************************************************
     * @brief Camera2 Board IP Address, Commands, Telemetry, and Error Packet 
     *
     * @author Missouri S&T - Mars Rover Design Team
     * @date 2024-05-27
     ******************************************************************************/
    namespace Camera2
    {
        // IP Address
        const AddressEntry IP_ADDRESS{192, 168, 4, 101};

        // Commands
        const std::map<std::string, ManifestEntry> COMMANDS = {
            {"TAKEPICTURE", ManifestEntry{13001, 1, DataTypes::UINT8_T}},
            {"TOGGLESTREAM2", ManifestEntry{13002, 2, DataTypes::UINT8_T}},
        };

        // Telemetry
        const std::map<std::string, ManifestEntry> TELEMETRY = {
            {"PICTURETAKEN2", ManifestEntry{13100, 1, DataTypes::UINT8_T}},
        };

        // Error
        const std::map<std::string, ManifestEntry> ERROR = {};
    }    // namespace Camera2

    /******************************************************************************
     * @brief IRSpectrometer Board IP Address, Commands, Telemetry, and Error 
     *
     * @author Missouri S&T - Mars Rover Design Team
     * @date 2024-05-27
     ******************************************************************************/
    namespace IRSpectrometer
    {
        // IP Address
        const AddressEntry IP_ADDRESS{192, 168, 3, 104};

        // Commands
        const std::map<std::string, ManifestEntry> COMMANDS = {};
        // Telemetry
        const std::map<std::string, ManifestEntry> TELEMETRY = {};
        // Error
        const std::map<std::string, ManifestEntry> ERROR = {};
    }    // namespace IRSpectrometer

    /******************************************************************************
     * @brief Instruments Board IP Address, Commands, Telemetry, and Error Packet 
     *
     * @author Missouri S&T - Mars Rover Design Team
     * @date 2024-05-27
     ******************************************************************************/
    namespace Instruments
    {
        // IP Address
        const AddressEntry IP_ADDRESS{192, 168, 3, 105};

        // Commands
        const std::map<std::string, ManifestEntry> COMMANDS = {
            {"ENABLELEDS", ManifestEntry{16000, 1, DataTypes::UINT8_T}},
            {"REQUESTRAMANREADING", ManifestEntry{16001, 1, DataTypes::UINT32_T}},
            {"REQUESTREFLECTANCEREADING", ManifestEntry{16002, 1, DataTypes::UINT32_T}},
            {"REQUESTTEMPERATURE", ManifestEntry{16003, 1, DataTypes::UINT8_T}},
        };

        // Telemetry
        const std::map<std::string, ManifestEntry> TELEMETRY = {
            {"RAMANREADING_PART1", ManifestEntry{16100, 500, DataTypes::UINT16_T}},
            {"RAMANREADING_PART2", ManifestEntry{16101, 500, DataTypes::UINT16_T}},
            {"RAMANREADING_PART3", ManifestEntry{16102, 500, DataTypes::UINT16_T}},
            {"RAMANREADING_PART4", ManifestEntry{16103, 500, DataTypes::UINT16_T}},
            {"RAMANREADING_PART5", ManifestEntry{16104, 48, DataTypes::UINT16_T}},
            {"REFLECTANCEREADING", ManifestEntry{16105, 288, DataTypes::UINT8_T}},
            {"TEMPERATURE", ManifestEntry{16106, 1, DataTypes::INT8_T}},
        };

        // Error
        const std::map<std::string, ManifestEntry> ERROR = {};
    }    // namespace Instruments

    /******************************************************************************
     * @brief RoveComm General Information
     *
     * @author Missouri S&T - Mars Rover Design Team
     * @date 2024-05-27
     ******************************************************************************/
    namespace General
    {
        const int UPDATE_RATE            = 100;
        const int ETHERNET_UDP_PORT      = 11000;
        const int ETHERNET_TCP_PORT      = 12000;
        const int SUBNET_MAC_FIRST_BYTE  = 222;
        const int SUBNET_MAC_SECOND_BYTE = 173;
    }    // namespace General

    /******************************************************************************
     * @brief RoveComm System Information
     *
     * @author Missouri S&T - Mars Rover Design Team
     * @date 2024-05-27
     ******************************************************************************/
    namespace System
    {
        const int PING_DATA_ID            = 1;
        const int PING_REPLY_DATA_ID      = 2;
        const int SUBSCRIBE_DATA_ID       = 3;
        const int UNSUBSCRIBE_DATA_ID     = 4;
        const int INVALID_VERSION_DATA_ID = 5;
        const int NO_DATA_DATA_ID         = 6;
    }    // namespace System
        
    /******************************************************************************
     * @brief RoveComm Helper Functions
     *
     * @author Missouri S&T - Mars Rover Design Team
     * @date 2024-05-27
     ******************************************************************************/
    namespace Helpers
    {
        inline DataTypes GetDataTypeFromMap(const std::map<std::string, ManifestEntry>& dataMap, uint16_t dataId)
        {
            for (const auto& entry : dataMap)
            {
                if (entry.second.DATA_ID == dataId)
                {
                    return entry.second.DATA_TYPE;
                }
            }
            return DataTypes::CHAR;    // Default return value if dataId not found
        }
        
        inline DataTypes GetDataTypeFromId(uint16_t dataId)
        {
            int boardId      = dataId / 1000;          // Determine board ID based on thousands place
            int dataTypeCode = (dataId / 100) % 10;    // Determine data type code based on hundreds place
            
            // Determine the board namespace based on boardId
            switch (boardId)
            {
                case 3:    // Core Board
                    if (dataTypeCode == 0)
                    {
                        return GetDataTypeFromMap(Core::COMMANDS, dataId);
                    }
                    else if (dataTypeCode == 1)
                    {
                        return GetDataTypeFromMap(Core::TELEMETRY, dataId);
                    }
                    else if (dataTypeCode == 2)
                    {
                        return GetDataTypeFromMap(Core::ERROR, dataId);
                    }
                    break;
                case 4:    // PMS Board
                    if (dataTypeCode == 0)
                    {
                        return GetDataTypeFromMap(PMS::COMMANDS, dataId);
                    }
                    else if (dataTypeCode == 1)
                    {
                        return GetDataTypeFromMap(PMS::TELEMETRY, dataId);
                    }
                    else if (dataTypeCode == 2)
                    {
                        return GetDataTypeFromMap(PMS::ERROR, dataId);
                    }
                    break;
                case 6:    // Nav Board
                    if (dataTypeCode == 0)
                    {
                        return GetDataTypeFromMap(Nav::COMMANDS, dataId);
                    }
                    else if (dataTypeCode == 1)
                    {
                        return GetDataTypeFromMap(Nav::TELEMETRY, dataId);
                    }
                    else if (dataTypeCode == 2)
                    {
                        return GetDataTypeFromMap(Nav::ERROR, dataId);
                    }
                    break;
                case 7:    // SignalStack Board
                    if (dataTypeCode == 0)
                    {
                        return GetDataTypeFromMap(SignalStack::COMMANDS, dataId);
                    }
                    else if (dataTypeCode == 1)
                    {
                        return GetDataTypeFromMap(SignalStack::TELEMETRY, dataId);
                    }
                    else if (dataTypeCode == 2)
                    {
                        return GetDataTypeFromMap(SignalStack::ERROR, dataId);
                    }
                    break;
                case 8:    // Arm Board
                    if (dataTypeCode == 0)
                    {
                        return GetDataTypeFromMap(Arm::COMMANDS, dataId);
                    }
                    else if (dataTypeCode == 1)
                    {
                        return GetDataTypeFromMap(Arm::TELEMETRY, dataId);
                    }
                    else if (dataTypeCode == 2)
                    {
                        return GetDataTypeFromMap(Arm::ERROR, dataId);
                    }
                    break;
                case 9:    // ScienceActuation Board
                    if (dataTypeCode == 0)
                    {
                        return GetDataTypeFromMap(ScienceActuation::COMMANDS, dataId);
                    }
                    else if (dataTypeCode == 1)
                    {
                        return GetDataTypeFromMap(ScienceActuation::TELEMETRY, dataId);
                    }
                    else if (dataTypeCode == 2)
                    {
                        return GetDataTypeFromMap(ScienceActuation::ERROR, dataId);
                    }
                    break;
                case 11:    // Autonomy Board
                    if (dataTypeCode == 0)
                    {
                        return GetDataTypeFromMap(Autonomy::COMMANDS, dataId);
                    }
                    else if (dataTypeCode == 1)
                    {
                        return GetDataTypeFromMap(Autonomy::TELEMETRY, dataId);
                    }
                    else if (dataTypeCode == 2)
                    {
                        return GetDataTypeFromMap(Autonomy::ERROR, dataId);
                    }
                    break;
                case 12:    // Camera1 Board
                    if (dataTypeCode == 0)
                    {
                        return GetDataTypeFromMap(Camera1::COMMANDS, dataId);
                    }
                    else if (dataTypeCode == 1)
                    {
                        return GetDataTypeFromMap(Camera1::TELEMETRY, dataId);
                    }
                    else if (dataTypeCode == 2)
                    {
                        return GetDataTypeFromMap(Camera1::ERROR, dataId);
                    }
                    break;
                case 13:    // Camera2 Board
                    if (dataTypeCode == 0)
                    {
                        return GetDataTypeFromMap(Camera2::COMMANDS, dataId);
                    }
                    else if (dataTypeCode == 1)
                    {
                        return GetDataTypeFromMap(Camera2::TELEMETRY, dataId);
                    }
                    else if (dataTypeCode == 2)
                    {
                        return GetDataTypeFromMap(Camera2::ERROR, dataId);
                    }
                    break;
                case 16:    // Instruments Board
                    if (dataTypeCode == 0)
                    {
                        return GetDataTypeFromMap(Instruments::COMMANDS, dataId);
                    }
                    else if (dataTypeCode == 1)
                    {
                        return GetDataTypeFromMap(Instruments::TELEMETRY, dataId);
                    }
                    else if (dataTypeCode == 2)
                    {
                        return GetDataTypeFromMap(Instruments::ERROR, dataId);
                    }
                    break;
                default:
                    // Invalid Board ID
                    break;
            }
            
            // If dataId is not found in any namespace, return a default type
            return DataTypes::CHAR;
        }
    }    // namespace Helpers

}    // namespace manifest

#endif    // MANIFEST_H
