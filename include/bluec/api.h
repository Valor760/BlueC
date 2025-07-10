#pragma once

#include <bluec/types.h>

/**
 * @brief Init function to initialize library internals
 * 
 * @param runMainLoop Set to TRUE if your application is not using Glib::MainLoop
 * @return See error codes
 */
LIBBLUEC_API BlueCErrorCodes bluec_Init(bool runMainLoop);

/**
 * @brief Library deinitialization. Call to perform cleanup.
 * 
 * @return See error codes
 */
LIBBLUEC_API BlueCErrorCodes bluec_DeInit();
