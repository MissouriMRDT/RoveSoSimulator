/******************************************************************************
 * @brief The RoveCommUDP class is used to send and receive data over a UDP
 *        connection.
 *
 * @file RoveCommUDP.h
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-02-06
 *
 * @copyright Copyright Mars Rover Design Team 2024 - All Rights Reserved
 ******************************************************************************/

#ifndef ROVECOMM_UDP_H
#define ROVECOMM_UDP_H

#include "ExternalIncludes.h"
#include "RoveCommConsts.h"
#include "RoveCommGlobals.h"
#include "RoveCommManifest.h"
#include "RoveCommPacket.h"

/// \cond
#include <atomic>
#include <csignal>
#include <cstring>
#include <functional>
#include <iostream>
#include <shared_mutex>
#include <unistd.h>
#include <unordered_set>
#include <vector>

/// \endcond

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
     * @brief The RoveCommUDP class is used to send and receive data over a UDP
     *        connection.
     *
     * @author Eli Byrd (edbgkk@mst.edu)
     * @date 2024-02-07
     ******************************************************************************/
    class RoveCommUDP : AutonomyThread<void>
    {
        private:
            // Private member variables
            std::atomic_int m_nUDPSocket;
            struct sockaddr_in m_saUDPServerAddr;
            std::vector<SubscriberInfo> vSubscribers;
            std::shared_mutex m_muCallbackMutex;

            // Packet processing functions
            template<typename T>
            void ProcessPacket(const RoveCommData& stData,
                               const std::vector<std::tuple<std::function<void(const RoveCommPacket<T>&, const sockaddr_in&)>, uint32_t>>& vCallbacks,
                               const sockaddr_in& saClientAddr);
            void ReceiveUDPPacketAndCallback();

            // Subscriber management functions
            void AddSubscriber(const std::string& szIPAddress, const int& nPort);
            void RemoveSubscriber(const std::string& szIPAddress, const int& nPort);

            // AutonomyThread member functions
            void ThreadedContinuousCode() override;
            void PooledLinearCode() override;

        public:
            // Constructor
            RoveCommUDP();
            // Destructor
            ~RoveCommUDP();

            // Initialization
            bool InitUDPSocket(int nPort);

            // Data transmission functions
            template<typename T>
            ssize_t SendUDPPacket(const RoveCommPacket<T>& stPacket, const char* cIPAddress, int nPort);

            // Callback management functions
            template<typename T>
            void AddUDPCallback(std::function<void(const RoveCommPacket<T>&, const sockaddr_in&)> fnCallback, const uint16_t& unCondition);

            template<typename T>
            void RemoveUDPCallback(std::function<void(const RoveCommPacket<T>&, const sockaddr_in&)> fnCallback);

            // Deinitialization
            void CloseUDPSocket();

            // Selectively make inherited method public so we can get RoveCommNode FPS.
            using AutonomyThread::GetIPS;

            // NOTE: These functions are for testing purposes only and should not be used in production code!
            template<typename T>
            void CallProcessPacket(const RoveCommData& stData,
                                   const std::vector<std::tuple<std::function<void(const RoveCommPacket<T>&, const sockaddr_in&)>, uint32_t>>& vCallbacks,
                                   const sockaddr_in& saClientAddr)
            {
                ProcessPacket(stData, vCallbacks, saClientAddr);
            }
    };

}    // namespace rovecomm

#endif    // ROVECOMM_UDP_H
