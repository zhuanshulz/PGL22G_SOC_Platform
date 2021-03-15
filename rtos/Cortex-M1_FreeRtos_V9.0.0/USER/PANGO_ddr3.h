#ifndef PANGO_DDR_H
#define PANGO_DDR_H

#ifdef __cplusplus
	extern "C" {
#endif

#include "PANGO_M1.h"


extern void DDR_Read_Data(uint32_t* pBuffer, uint32_t address, uint8_t burst_len);
extern void DDR_Write_Data(uint32_t* pBuffer, uint32_t address, uint8_t burst_len);
extern void DDR_Write_bytes(uint32_t data, uint32_t address, uint8_t burst_len);
		
		
#ifdef __cplusplus
}
#endif

#endif /* PANGO_DDR_H */

