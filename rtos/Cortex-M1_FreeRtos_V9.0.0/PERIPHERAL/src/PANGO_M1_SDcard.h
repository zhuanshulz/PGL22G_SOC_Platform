#include "stdint.h"

typedef struct
{
	uint64_t sector_data_0;
	uint64_t sector_data_1;
	uint64_t sector_data_2;
	uint64_t sector_data_3;
	uint64_t sector_data_4;
	uint64_t sector_data_5;
	uint64_t sector_data_6;
	uint64_t sector_data_7;
}sector_data;
////////////////////////////////////////////////////////
//Block是文件系统上的概念，一般文件系统block大小为4K。
//
//Sector是磁介质硬盘最小单元，一般为512字节。
//
//Block值一般与sector值是不相等的。
////////////////////////////////////////////////////////
typedef struct
{
	volatile uint8_t card_status;					//SD卡的状态信息
	/*
	|															status register																			|
	|	7	|	6	|	5	|	4	|	3	|					2						|				1							|				0					|
	|		|		|		|		|		|		writing status		|	reading status			|		init status		|
	|		|		|		|		|		|		0 for finished		|	0 for finished			|	0 for not init	|
	|		|		|		|		|		|	1 for not finished	|	1 for not finished	|	1 for inited		|
	*/
	volatile uint8_t card_command;				//给SD卡的命令
	volatile uint32_t read_sector;				//读取扇区的地址
	volatile uint32_t addr_sector; 				//写/读扇区的地址
	volatile uint8_t spi_clock_level;			//spi总线的时钟等级
	volatile sector_data readout_sector;				//读出的512位扇区数据。
}SD_Card;