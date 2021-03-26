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
//Block���ļ�ϵͳ�ϵĸ��һ���ļ�ϵͳblock��СΪ4K��
//
//Sector�ǴŽ���Ӳ����С��Ԫ��һ��Ϊ512�ֽڡ�
//
//Blockֵһ����sectorֵ�ǲ���ȵġ�
////////////////////////////////////////////////////////
typedef struct
{
	volatile uint8_t card_status;					//SD����״̬��Ϣ
	/*
	|															status register																			|
	|	7	|	6	|	5	|	4	|	3	|					2						|				1							|				0					|
	|		|		|		|		|		|		writing status		|	reading status			|		init status		|
	|		|		|		|		|		|		0 for finished		|	0 for finished			|	0 for not init	|
	|		|		|		|		|		|	1 for not finished	|	1 for not finished	|	1 for inited		|
	*/
	volatile uint8_t card_command;				//��SD��������
	volatile uint32_t read_sector;				//��ȡ�����ĵ�ַ
	volatile uint32_t addr_sector; 				//д/�������ĵ�ַ
	volatile uint8_t spi_clock_level;			//spi���ߵ�ʱ�ӵȼ�
	volatile sector_data readout_sector;				//������512λ�������ݡ�
}SD_Card;