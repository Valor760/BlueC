#pragma once

#define LIBBLUEC_API __attribute__((visibility("default")))

typedef enum BlueCErrorCodes
{
	BLUEC_ERROR_NONE         =  0, // No errors
	BLUEC_ERROR_INTERNAL     = -1, // Generic internal error has occurred
	BLUEC_ERROR_ALREADY_INIT = -2, // Library is already initialized
	BLUEC_ERROR_NOT_INIT     = -3, // Library is NOT yet initialized
} BlueCErrorCodes;
