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
//Block���ļ�ϵͳ�ϵĸ��һ���ļ�ϵͳblock��СΪ4K��//
//																										//
//Sector�ǴŽ���Ӳ����С��Ԫ��һ��Ϊ512�ֽڡ�					//
//																										//
//Blockֵһ����sectorֵ�ǲ���ȵġ�										//
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
