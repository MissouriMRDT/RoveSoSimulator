/******************************************************************************
 * @brief ExternalIncludes.h is a file that is included in the RoveComm library
 *        to include external dependencies that are not part of the library.
 *
 * @file ExternalIncludes.h
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-02-07
 *
 * @copyright Copyright Mars Rover Design Team 2024 - All Rights Reserved
 ******************************************************************************/

#ifndef EXTERNAL_INCLUDES_H
#define EXTERNAL_INCLUDES_H

/******************************************************************************
 * @brief Since this project is setup as a library sometimes we need to access
 *        our logger and globals from the host application and othertimes, in
 *        the case that we are testing directly within our stand-alone
 *        application we need to access our logger and globals from within
 *        the repository but not necissarily from within the library itself.
 *
 *        The macro, __ROVECOMM_LIBRARY_MODE__, is how we can detect within
 *        RoveComm for High Level C++ Applications which mode we are running
 *        in and will tell us what can be included.
 *
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2023-08-28
 ******************************************************************************/
#if defined(__ROVECOMM_LIBRARY_MODE__) && __ROVECOMM_LIBRARY_MODE__ == 1
#include "../../../../src/interfaces/AutonomyThread.hpp"
#else
#include "../interfaces/AutonomyThread.hpp"
#endif

#endif    // EXTERNAL_INCLUDES_H
