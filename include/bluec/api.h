#ifndef __LIB_BLUEZ_API
#define __LIB_BLUEZ_API

#define LIBAPI __attribute__((visibility("default")))

LIBAPI int bluez_Init();
LIBAPI void bluez_DeInit();

#undef LIBAPI

#endif /* __LIB_BLUEZ_SIMPLE_API */