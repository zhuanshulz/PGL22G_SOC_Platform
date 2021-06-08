/*
 * ***************************************************************************************** 		
 * �ļ����ƣ�PANGO_ddr3.c
 * ����������DDR3Ӧ�������⺯��
 ******************************************************************************************
 */

#include "PANGO_ddr3.h"

/********************************************************************
 ** �������ƣ�DDR_Read_Data
 ** �������ܣ�DDR������
 ** ���������pBuffer:�����ݻ���
 **           address:��������ʼ��ַ
 **           burst_len:ͻ������
 ** �����������
 ** ���ز�������
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
 ** �������ƣ�DDR_Write_Data
 ** �������ܣ�DDRд����
 ** ���������pBuffer:д���ݻ���
 **           address:д������ʼ��ַ
 **           burst_len:ͻ������
 ** �����������
 ** ���ز�������
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
 ** �������ƣ�DDR_Write_bytes
 ** �������ܣ�DDRд����(4bytes)
 ** ���������data:д������
 **           address:д������ʼ��ַ
 **           burst_len:ͻ������
 ** �����������
 ** ���ز�������
 ********************************************************************/
void DDR_Write_bytes(uint32_t data, uint32_t address, uint8_t burst_len)
{
	uint32_t data_buf[burst_len*4];
	DDR_Set_Read_Addr(DDR_DATA_BASE + address);
	DDR_Read_Command();
	for(int i = 0; i < burst_len; i++)									//����Ҫ����ͻ�����ȵ�����
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

