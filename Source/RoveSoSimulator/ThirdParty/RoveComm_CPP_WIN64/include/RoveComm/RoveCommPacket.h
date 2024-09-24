/******************************************************************************
 * @brief RoveComm Packet Definition.
 *
 * @file RoveCommPacket.h
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-02-05
 *
 * @copyright Copyright Mars Rover Design Team 2024 - All Rights Reserved
 ******************************************************************************/

#ifndef ROVECOMM_PACKET_H
#define ROVECOMM_PACKET_H

#include "./RoveCommConsts.h"
#include "./RoveCommManifest.h"

/// \cond
#include <cstdint>
#include <cstring>
#include <vector>

#if defined(__ROVECOMM_WINDOWS_MODE__) && __ROVECOMM_WINDOWS_MODE__ == 1
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#elif _WIN32_WINNT < 0x0600
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

/// \endcond

// These are used to convert 64-bit doubles to network bit order and back.
#define htonll(x) ((1 == htonl(1)) ? (x) : (((uint64_t) htonl((x) & 0xFFFFFFFFUL)) << 32) | htonl((uint32_t) ((x) >> 32)))
#define ntohll(x) ((1 == ntohl(1)) ? (x) : (((uint64_t) ntohl((x) & 0xFFFFFFFFUL)) << 32) | ntohl((uint32_t) ((x) >> 32)))

/******************************************************************************
 * @brief The RoveComm namespace contains all of the functionality for the
 *        RoveComm library. This includes the packet structure and the
 *        functions for packing and unpacking data.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-02-07
 ******************************************************************************/
namespace rovecomm
{
    /******************************************************************************
     * @brief The RoveCommPacket struct is used to store data in a packet format
     *        for transmission over a network. This struct is used to store the
     *        data ID, data count, data type, and the data itself. The data is
     *        stored in a vector of the specified data type.
     *
     * @tparam T - The data type of the data to be stored in the packet.
     *             This can be any of the data types defined in the manifest.
     *
     * @author Eli Byrd (edbgkk@mst.edu)
     * @date 2024-02-07
     ******************************************************************************/
    template<typename T>
    struct RoveCommPacket
    {
        public:
            uint16_t unDataId;
            uint16_t unDataCount;
            manifest::DataTypes eDataType;
            std::vector<T> vData;
    };

    /******************************************************************************
     * @brief The RoveCommData struct is used to store data in a packet format
     *        for transmission over a network. This struct is used to store the
     *        data in a byte array for transmission. The data is stored in a byte
     *        array with the packet header and data.
     *
     * @author Eli Byrd (edbgkk@mst.edu)
     * @date 2024-02-07
     ******************************************************************************/
    struct RoveCommData
    {
        public:
            uint8_t unBytes[ROVECOMM_PACKET_HEADER_SIZE + sizeof(uint8_t) * ROVECOMM_PACKET_MAX_DATA_COUNT / 2];
    };

    // RoveCommPacket and RoveCommData packing and unpacking functions
    template<typename T>
    RoveCommData PackPacket(const RoveCommPacket<T>& stPacket);

    template<typename T>
    RoveCommPacket<T> UnpackData(const RoveCommData& stData);
}    // namespace rovecomm

#endif    // ROVECOMM_PACKET_H
