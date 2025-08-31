#pragma once

#include <time.h>
#include <arch.h>
#define LWIP_PLATFORM_ASSERT(x)  do {printf("Assertion \"%s\" failed at line %d in %s\n", \
                                     x, __LINE__, __FILE__); abort();} while(0)

extern __attribute__((section(".ExtSRAM"))) uint8_t memp_memory_PBUF_POOL_base[];
#ifdef __ICCARM__
#define PACK_STRUCT_BEGIN __packed
#endif

