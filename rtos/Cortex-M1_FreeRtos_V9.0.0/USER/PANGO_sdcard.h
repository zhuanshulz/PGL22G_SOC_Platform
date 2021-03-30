#include "ff.h"
#define INITOK (uint32_t)1
int SD_Init();
int SD_Read(BYTE *buff,	LBA_t sector,	UINT count);
int SD_Write(const BYTE *buff,	LBA_t sector,	UINT count);
