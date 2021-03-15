#ifndef PANGO_M1_MEMORY_H
#define PANGO_M1_MEMORY_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "PANGO_M1.h"

extern void Memory_Write_Bytes(uint32_t address, uint32_t data);
extern uint32_t Memory_Read_Bytes(uint32_t address);

#ifdef __cplusplus
}
#endif

#endif  /* PANGO_M1_MEMORY_H */


