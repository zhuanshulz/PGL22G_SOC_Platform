/*
 * ***************************************************************************************** 		
 * 文件名称：PANGO_ddr3.c
 * 功能描述：DDR3应用驱动库函数
 ******************************************************************************************
 */

#include "PANGO_ddr3.h"

/********************************************************************
 ** 函数名称：DDR_Read_Data
 ** 函数功能：DDR读数据
 ** 输入参数：pBuffer:读数据缓存
 **           address:读数据起始地址
 **           burst_len:突发长度
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void DDR_Read_Data(uint32_t* pBuffer, uint32_t address, uint8_t burst_len)
{
	DDR_Set_Read_Addr(DDR_DATA_BASE + address);
	DDR_Read_Command();
	for(int i = 0; i < burst_len; i++)
	{
		*(pBuffer + i*4 ) = (*(__IO uint32_t*)(DDR_DATA_BASE + address));
		*(pBuffer + i*4 + 1) = (*(__IO uint32_t*)(DDR_DATA_BASE + address));
		*(pBuffer + i*4 + 2) = (*(__IO uint32_t*)(DDR_DATA_BASE + address));
		*(pBuffer + i*4 + 3) = (*(__IO uint32_t*)(DDR_DATA_BASE + address));
	}
}

/********************************************************************
 ** 函数名称：DDR_Write_Data
 ** 函数功能：DDR写数据
 ** 输入参数：pBuffer:写数据缓存
 **           address:写数据起始地址
 **           burst_len:突发长度
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void DDR_Write_Data(uint32_t* pBuffer, uint32_t address, uint8_t burst_len)
{
	for(int i = 0; i < burst_len; i++)
	{
		(*(__IO uint32_t*)(DDR_DATA_BASE + address)) = *(pBuffer + i*4 );
		(*(__IO uint32_t*)(DDR_DATA_BASE + address)) = *(pBuffer + i*4 + 1);
		(*(__IO uint32_t*)(DDR_DATA_BASE + address)) = *(pBuffer + i*4 + 2);
		(*(__IO uint32_t*)(DDR_DATA_BASE + address)) = *(pBuffer + i*4 + 3);
	}
	DDR_Write_Command();
}

/********************************************************************
 ** 函数名称：DDR_Write_bytes
 ** 函数功能：DDR写数据(4bytes)
 ** 输入参数：data:写入数据
 **           address:写数据起始地址
 **           burst_len:突发长度
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void DDR_Write_bytes(uint32_t data, uint32_t address, uint8_t burst_len)
{
	uint32_t data_buf[burst_len*4];
	DDR_Set_Read_Addr(DDR_DATA_BASE + address);
	DDR_Read_Command();
	for(int i = 0; i < burst_len; i++)									//必须要操作突发长度的数据
	{
		data_buf[i*4] = (*(__IO uint32_t*)(DDR_DATA_BASE + address));
		data_buf[i*4 + 1] = (*(__IO uint32_t*)(DDR_DATA_BASE + address));
		data_buf[i*4 + 2] = (*(__IO uint32_t*)(DDR_DATA_BASE + address));
		data_buf[i*4 + 3] = (*(__IO uint32_t*)(DDR_DATA_BASE + address));
	}
	data_buf[0] = data;
	for(int i = 0; i < burst_len; i++)
	{
		(*(__IO uint32_t*)(DDR_DATA_BASE + address)) = data_buf[i*4];
		(*(__IO uint32_t*)(DDR_DATA_BASE + address)) = data_buf[i*4 + 1];
		(*(__IO uint32_t*)(DDR_DATA_BASE + address)) = data_buf[i*4 + 2];
		(*(__IO uint32_t*)(DDR_DATA_BASE + address)) = data_buf[i*4 + 3];
	}
	DDR_Write_Command();
}

