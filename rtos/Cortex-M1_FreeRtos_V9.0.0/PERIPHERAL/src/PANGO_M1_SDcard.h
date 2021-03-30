#include "stdint.h"
#include "PANGO_M1.h"
//typedef struct
//{
//	uint64_t sector_data_0;
//	uint64_t sector_data_1;
//	uint64_t sector_data_2;
//	uint64_t sector_data_3;
//	uint64_t sector_data_4;
//	uint64_t sector_data_5;
//	uint64_t sector_data_6;
//	uint64_t sector_data_7;
//}sector_data;
////////////////////////////////////////////////////////
//Block是文件系统上的概念，一般文件系统block大小为4K。//
//																										//
//Sector是磁介质硬盘最小单元，一般为512字节。					//
//																										//
//Block值一般与sector值是不相等的。										//
////////////////////////////////////////////////////////

/*--------------------------SD-Card-----------------------------*/
//typedef struct {
//	__IO uint32_t TRANSDATA[128];    /* Offset: 0x000-0x1FF (R/ ) Data Registers    */
//	__IO uint32_t BASEADDR;          /* Offset: 0x200 (R/W) Base Address Register   */
//	__IO uint32_t READEN;            /* Offset: 0x204 (R/W) Read Enable Register    */
//	__IO uint32_t INITIALISED;       /* Offset: 0x208 (R/ ) Initialization Register */
//}SDCard_TypeDef;
#ifdef SDCARD
	#undef SDCARD
	#define SDCARD            ((SDCard_TypeDef    *)BANK_RAM_BASE1
#else
	#define SDCARD            ((SDCard_TypeDef    *)BANK_RAM_BASE1
#endif
