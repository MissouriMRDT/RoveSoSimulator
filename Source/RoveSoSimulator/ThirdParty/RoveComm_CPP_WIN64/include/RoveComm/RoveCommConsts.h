/******************************************************************************
 * @brief Defines Global Constants within RoveComm C++
 *
 * @file RoveCommConsts.h
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2023-07-29
 *
 * @copyright Copyright Mars Rover Design Team 2024 - All Rights Reserved
 ******************************************************************************/

#ifndef ROVECOMM_CONSTS_H
#define ROVECOMM_CONSTS_H

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
#define ROVECOMM_ETHERNET_UDP_MAX_SUBSCRIBERS 10
#define ROVECOMM_PACKET_MAX_DATA_COUNT        65535
#define ROVECOMM_PACKET_HEADER_SIZE           6
#define ROVECOMM_VERSION                      3

    // Server constants.
    const int ROVECOMM_THREAD_MAX_IPS = 120;
}    // namespace rovecomm
#endif    // ROVECOMM_CONSTS_H
