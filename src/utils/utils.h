#pragma once

#include "log.h"
#include <bluec/bluec.h>

#include <cassert>

#define MAKE_INTERNAL_CALL(internalFunc)              \
	do {                                              \
		try {                                         \
			return internalFunc;                      \
		}                                             \
		catch(BlueCErrorCodes err) {                  \
			LOG_ERROR("Caught BlueC error: %d", err); \
			return err;                               \
		}                                             \
		catch(...) {                                  \
			LOG_ERROR("Caught unknown exception");    \
			return BLUEC_ERROR_INTERNAL;              \
		}                                             \
	} while(false)

// TODO: Disable in non-debug build
// TODO: Maybe provide string, but is it needed?
#define BLUEC_ASSERT(expression) assert(expression)
