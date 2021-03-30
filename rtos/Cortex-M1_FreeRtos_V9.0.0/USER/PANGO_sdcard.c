#include "PANGO_sdcard.h"
#include "stdint.h"
#include "PANGO_M1.h"


int SD_Init()
{
	uint32_t init_status = (uint32_t)(SDCARD->INITIALISED);
	if(init_status== INITOK)
		return 1;
	else
		return 0;
}

int SD_Read(BYTE *buff,	LBA_t sector,	UINT count)
{
	uint32_t sd_status = (uint32_t)(SDCARD->STATUS);
	while ((sd_status & (uint32_t)17)!=(uint32_t)17)	//µÈ´ý¿É¶Á¿ÉÐ´×´Ì¬
	{
		
	}
	

}

int SD_Write(const BYTE *buff,	LBA_t sector,	UINT count)
{
	SDCARD->BASEADDR = sector;
//	for(uint32_t i = 0; i<
//	SDCARD->TRANSDATA


}