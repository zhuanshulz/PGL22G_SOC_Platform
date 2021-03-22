/*
 * ***************************************************************************************** 		
 * �ļ����ƣ�PANGO_spi_flash.c
 * ����������SPI FlashӦ�������⺯��
 ******************************************************************************************
 */
/******************************** SPI FLASH��Ϣ ********************************
SPI FLASH����ܶ�, ���������������

1��W25X64��Ϣ��
ҳ(Page) ------ 256Byte
����(Sector) -- 4KByte ------ (����16ҳ)
��(Block) ----- 64KByte ----- (����16����)

W25X64оƬ������8MB (64Mbit)
          ҳ����64*16*32 (2M/256)
        ��������64*32
          ������128

2����д������
�� ------------ һ������һҳ(256B)
д ------------ ҳ
���� ---------- �������顢����оƬ

3�����ƺ�״̬�Ĵ�������(Ĭ��:0x00)
BITλ  7   6   5   4   3   2   1   0
      SPR  RV  TB  BP2 BP1 BP0 WEL BUSY
SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
TB,BP2,BP1,BP0:FLASH����д��������
WEL:дʹ������
BUSY:æ���λ(1,æ;0,����)
********************************************************************************/

#include "PANGO_spi_flash.h"

/********************************************************************
 ** �������ƣ�SPI_WriteByte
 ** �������ܣ�SPIдһ���ֽ�
 ** ���������TxData:д�������
 ** �����������
 ** ���ز�������
 ********************************************************************/
static void SPI_WriteByte(uint8_t TxData)
{
	SPI_WriteData(TxData);
	while(SPI_GetTmtStatus() == 1);
}

/********************************************************************
 ** �������ƣ�print_num
 ** �������ܣ���ӡ��ʮ������
 ** �����������
 ** �����������
 ** ���ز�����������SPI����
 ********************************************************************/
static uint8_t SPI_ReadByte(void)
{
	while(SPI_GetTmtStatus() == 1);
	SPI_SetRcvStatus();
	while(SPI_GetRcvStatus() == 1);
	return SPI_ReadData();
}

/********************************************************************
 ** �������ƣ�SFLASH_WriteEnable
 ** �������ܣ�SPI_FLASHдʹ�ܣ���WEL��λ
 ** �����������
 ** �����������
 ** ���ز�������
 ********************************************************************/
static void SFLASH_WriteEnable(void)
{
	SPI0_CS_ENABLE;                                 //ʹ������
	SPI_WriteByte(SFLASH_WRITE_ENABLE);            //��дʹ�ܡ�ָ��
	SPI_CS_DISABLE;                                //ʧ������
}

/********************************************************************
 ** �������ƣ�SFLASH_WriteDisable
 ** �������ܣ�SPI_FLASHд��ֹ,��WEL����
 ** �����������
 ** �����������
 ** ���ز�������
 ********************************************************************/
static void SFLASH_WriteDisable(void)
{
	SPI0_CS_ENABLE;                                 //ʹ������
	SPI_WriteByte(SFLASH_WRITE_DISABLE);           //��дʧ�ܡ�ָ��
	SPI_CS_DISABLE;                                //ʧ������
}

/********************************************************************
 ** �������ƣ�SFLASH_ReadSR
 ** �������ܣ�SPI_FLASHд
 ** �����������
 ** �����������
 ** ���ز�����data_tmp:��ȡ�ֽ�
 ********************************************************************/
uint8_t SFLASH_ReadSR(void)
{
	uint8_t data_tmp;
	SPI0_CS_ENABLE;                                 //ʹ������
	SPI_WriteByte(SFLASH_READ_STATUS_REG);         //����״̬�Ĵ�����ָ��
	data_tmp = SPI_ReadByte();                     //��ȡһ���ֽ�
	SPI_CS_DISABLE;                                //ʧ������
	return data_tmp;
}

/********************************************************************
** �������ƣ�SFLASH_WriteSR
** �������ܣ�дSFLASH״̬�Ĵ���
** ���������SR:д״̬�Ĵ�������
** �����������
** ���ز�������
********************************************************************/
void SFLASH_WriteSR(uint8_t SR)
{
	SFLASH_WriteEnable();                          //дʹ��
	SPI_WriteByte(SFLASH_WRITE_STATUS_REG);        //��д״̬�Ĵ�����ָ��
	SPI_WriteByte(SR);                             //д��һ���ֽ�
	SPI_CS_DISABLE;                                //ʧ������
}

/********************************************************************
** �������ƣ�SFLASH_ReadNByte
** �������ܣ���ReadAddr��ַ��ʼ������ȡSFLASH��nByte
** ���������pBuffer:���ݴ洢���׵�ַ
**           ReadAddr:Ҫ��ȡSFLASH Flash���׵�ַ��ַ
**           nByte:Ҫ��ȡ���ֽ���(���65535B = 64K ��)
** �����������
** ���ز�������
********************************************************************/
void SFLASH_ReadNByte(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t nByte)
{
	SPI0_CS_ENABLE;                                 //ʹ������
	SPI_WriteByte(SFLASH_READ_DATA);               //�������ݡ�ָ��
	SPI_WriteByte((uint8_t)((ReadAddr)>>16));      //����24bit��ַ
	SPI_WriteByte((uint8_t)((ReadAddr)>>8));
	SPI_WriteByte((uint8_t)ReadAddr);

	while(nByte--)                                 //ѭ������
	{
		*pBuffer = SPI_ReadByte();
		pBuffer++;
	}

	SPI_CS_DISABLE;                                //ʧ������
}

/********************************************************************
** �������ƣ�SFLASH_FastReadNByte
** �������ܣ���ReadAddr��ַ��ʼ�������ٶ�ȡSFLASH��nByte
** ���������pBuffer:���ݴ洢���׵�ַ
**           ReadAddr:Ҫ��ȡSFLASH Flash���׵�ַ��ַ
**           nByte:Ҫ��ȡ���ֽ���(���65535B = 64K ��)
** �����������
** ���ز�������
********************************************************************/
void SFLASH_FastReadNByte(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t nByte)
{
	SPI0_CS_ENABLE;                                 //ʹ������
	SPI_WriteByte(SFLASH_FAST_READ);               //��������ݡ�ָ��
	SPI_WriteByte((uint8_t)((ReadAddr)>>16));      //����24bit��ַ
	SPI_WriteByte((uint8_t)((ReadAddr)>>8));
	SPI_WriteByte((uint8_t)ReadAddr);
	SPI_WriteByte(0xFF);                           //�ȴ�8��ʱ��

	while(nByte--)                                 //ѭ������
	{
		*pBuffer = SPI_ReadByte();
		pBuffer++;
	}

	SPI_CS_DISABLE;                                //ʧ������
}

/********************************************************************
** �������ƣ�SFLASH_WritePage
** �������ܣ���SFLASH��д������1ҳ(256���ֽ�)������
** ���������pBuffer:д���������׵�ַ
**           WriteAddr:Ҫд��Flash�ĵ�ַ
**           nByte:Ҫд����ֽ���(���1ҳ)
** �����������
** ���ز�������
********************************************************************/
void SFLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t nByte)
{
	SFLASH_WriteEnable();                          //дʹ��

	SPI0_CS_ENABLE;                                 //ʹ������
	SPI_WriteByte(SFLASH_WRITE_PAGE);              //��ҳ��̡�ָ��
	SPI_WriteByte((uint8_t)((WriteAddr)>>16));     //����24bit��ַ
	SPI_WriteByte((uint8_t)((WriteAddr)>>8));
	SPI_WriteByte((uint8_t)WriteAddr);

	while (nByte--)
	{
		SPI_WriteByte(*pBuffer);
		pBuffer++;
	}

	SPI_CS_DISABLE;
	SFLASH_WaitForNoBusy();                        //�ȴ����У��ȴ�д�������
}

/********************************************************************
** �������ƣ�SFLASH_WriteNoCheck
** �������ܣ��޼���дSFLASH
**           ����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0xFF,�����ڷ�0xFF��д������ݽ�ʧ��!
**           �����Զ���ҳ����
**           ��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
** ���������pBuffer:д���������׵�ַ
**           WriteAddr:Ҫд��Flash�ĵ�ַ
**           nByte:Ҫд����ֽ���
** �����������
** ���ز�������
********************************************************************/
void SFLASH_WriteNoCheck(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t nByte)
{
	uint16_t PageRemain = 256 - WriteAddr%256;     //��ҳʣ���д���ֽ���

	if(nByte <= PageRemain)
	PageRemain = nByte;                          	//������256���ֽ�

	while(1)
	{
		SFLASH_WritePage(pBuffer, WriteAddr, PageRemain);
		if(nByte == PageRemain)                      //д�����
		  break;
		else                                         //д��δ����
		{
			pBuffer += PageRemain;                   //��һҳд������
			WriteAddr += PageRemain;                 //��һҳд�����ݵ�ַ
			nByte -= PageRemain;                     //��д���ֽ����ݼ�

			if(nByte > 256)
				PageRemain = 256;                    //��д��1ҳ(256�ֽ�)������
			else
				PageRemain = nByte;                  //��д������1ҳ(256�ֽ�)������
		}
	}
}

/********************************************************************
** �������ƣ�SFLASH_WriteNByte
** �������ܣ���ReadAddr��ַ��ʼ����д��nByte��SFLASH��
** ���������pBuffer:д���������׵�ַ
**           WriteAddr:Ҫд��Flash�ĵ�ַ
**           nByte:Ҫд����ֽ���(���65535B = 64K ��)
** �����������
** ���ز�������
********************************************************************/
void SFLASH_WriteNByte(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t nByte)
{
	static uint8_t SectorBuf[4096];                //����buf
	uint32_t SecPos;                               //����λ��
	uint16_t SecOff;                               //����ƫ��
	uint16_t SecRemain;                            //ʣ������
	uint16_t i;

	SecPos = WriteAddr/4096;                       //��ַ��������(0~511)
	SecOff = WriteAddr%4096;                       //��ַ����������ƫ��
	SecRemain = 4096-SecOff;                       //��ַ��������ʣ���ֽ���(������С4096B=4KB)

	if(nByte <= SecRemain)
	SecRemain = nByte;                           	//д�����ݴ�С < ʣ��ռ��С (��ʣ��ռ乻������Щ����)

	while(1)
	{
		SFLASH_ReadNByte(SectorBuf, SecPos*4096, 4096);        	//������������������
		for(i=0; i<SecRemain; i++)                             	//У������,�Ƿ���Ҫ����
		{
			if(SectorBuf[SecOff + i] != 0xFF)                   //�洢���ݲ�Ϊ0xFF ����Ҫ����
			break;
		}
		if(i < SecRemain)                                      	//��Ҫ����
		{
			SFLASH_EraseSector(SecPos);                         //����������
			for(i=0; i<SecRemain; i++)                          //����д�������(��1��ʱ����д������������ʣ��Ŀռ�)
			{
				SectorBuf[SecOff + i] = pBuffer[i];
			}
			SFLASH_WriteNoCheck(SectorBuf, SecPos*4096, 4096);   //д���������������� = ������ + ��д�����ݣ�
		}
		else
			SFLASH_WriteNoCheck(pBuffer, WriteAddr, SecRemain);  //����Ҫ����,ֱ��д������ʣ��ռ�

		if(nByte == SecRemain)                       			//д�����
		{
			SFLASH_WriteDisable();                     			//дʧ��, �˳�д
			break;
		}
		else                                         			//д��δ����
		{
			SecPos++;                                  			//������ַ��1
			SecOff = 0;                                			//ƫ��λ�ù���
			pBuffer += SecRemain;                      			//ָ��ƫ��
			WriteAddr += SecRemain;                    			//д��ַƫ��
			nByte -= SecRemain;                        			//��д���ֽ����ݼ�
		if(nByte > 4096)
			SecRemain = 4096;                        			//��д��1����(4096�ֽ�)������
		else
			SecRemain = nByte;                       			//��д������1����(4096�ֽ�)������
		}
	}
}

/********************************************************************
** �������ƣ�SFLASH_WaitForNoBusy
** �������ܣ��ȴ���æ
** ��������w��
** �����������
** ���ز�������
********************************************************************/
void SFLASH_WaitForNoBusy(void)
{
	while((SFLASH_ReadSR()&0x01)==0x01);           				//�ȴ�BUSYλ���
}

/********************************************************************
** �������ƣ�SFLASH_EraseBlock
** �������ܣ������飬��������Ҫһ��ʱ��
** ��������wBlockAddr:���ַ 0~31
** �����������
** ���ز�������
********************************************************************/
void SFLASH_EraseBlock(uint32_t BlockAddr)
{
	BlockAddr *= 65536;                            //���׵�ַ
	SFLASH_WriteEnable();                          //дʹ��
	SFLASH_WaitForNoBusy();
	SPI0_CS_ENABLE;                                 //ʹ������
	SPI_WriteByte(SFLASH_ERASE_BLOCK);             //�������顷ָ��
	SPI_WriteByte((uint8_t)((BlockAddr)>>16));     //������ַ
	SPI_WriteByte((uint8_t)((BlockAddr)>>8));
	SPI_WriteByte((uint8_t)BlockAddr);
	SPI_CS_DISABLE;

	SFLASH_WaitForNoBusy();                        //�ȴ��������
}

/********************************************************************
** �������ƣ�SFLASH_EraseSector
** �������ܣ���������
** ��������wSectorAddr:������ַ 0~511
** �����������
** ���ز�������
********************************************************************/
void SFLASH_EraseSector(uint32_t SectorAddr)
{
	SectorAddr *= 4096;                            //�����׵�ַ
	SFLASH_WriteEnable();                          //дʹ��
	SFLASH_WaitForNoBusy();
	SPI0_CS_ENABLE;                                 //ʹ������
	SPI_WriteByte(SFLASH_ERASE_SECTOR);            //������������ָ��
	SPI_WriteByte((uint8_t)((SectorAddr)>>16));    //������ַ
	SPI_WriteByte((uint8_t)((SectorAddr)>>8));
	SPI_WriteByte((uint8_t)SectorAddr);
	SPI_CS_DISABLE;

	SFLASH_WaitForNoBusy();                        //�ȴ��������
}

/********************************************************************
** �������ƣ�SFLASH_EraseChip
** �������ܣ���������оƬ(��Ƭ����ʱ��ϳ�)
** ��������w��
** �����������
** ���ز�������
********************************************************************/
void SFLASH_EraseChip(void)
{
	SFLASH_WriteEnable();                          //дʹ��
	SFLASH_WaitForNoBusy();
	SPI0_CS_ENABLE;                                 //ʹ������
	SPI_WriteByte(SFLASH_ERASE_CHIP);              //������оƬ��ָ��
	SPI_CS_DISABLE;

	SFLASH_WaitForNoBusy();                        //�ȴ�оƬ��������
}

/********************************************************************
** �������ƣ�SFLASH_PowerDown
** �������ܣ��������ģʽ
** ��������w��
** �����������
** ���ز�������
********************************************************************/
void SFLASH_PowerDown(void)
{
	SPI0_CS_ENABLE;                                 //ʹ������
	SPI_WriteByte(SFLASH_POWER_DOWN);              //�����硷ָ��
	SPI_CS_DISABLE;                                //ʧ������
}

/********************************************************************
** �������ƣ�SFLASH_WAKEUP
** �������ܣ����绽��
** ��������w��
** �����������
** ���ز�������
********************************************************************/
void SFLASH_WAKEUP(void)
{
	SPI0_CS_ENABLE;                                 //ʹ������
	SPI_WriteByte(SFLASH_RELEASE_POWER_DOWN);      //�����绽�ѡ�ָ��
	SPI_CS_DISABLE;                                //ʧ������
}

/********************************************************************
** �������ƣ�SFLASH_ReadID
** �������ܣ���ȡоƬID SFLASH��ID(W25X64: EF16��
** ��������w��
** �����������
** ���ز�����ID:16λID��
********************************************************************/
uint16_t SFLASH_ReadID(void)
{
	uint16_t ID = 0;
	SPI0_CS_ENABLE;                                 //ʹ������

	SPI_WriteByte(SFLASH_DEVICE_ID);               //���豸ID��ָ��
	SPI_WriteByte(0x00);
	SPI_WriteByte(0x00);
	SPI_WriteByte(0x00);

	ID |= SPI_ReadByte()<<8;                       //��ȡID
	ID |= SPI_ReadByte();
	SPI_CS_DISABLE;                                //ʧ������
	return ID;
}

/********************************************************************
** �������ƣ�SFLASH_ReadJEDEC_ID
** �������ܣ���ȡоƬJEDEC_ID(W25X64: EF4017��
** ��������w��
** �����������
** ���ز�����ID:24λID��
********************************************************************/
uint32_t SFLASH_ReadJEDEC_ID(void)
{
	uint32_t ID = 0;
	SPI0_CS_ENABLE;                                 //ʹ������

	SPI_WriteByte(SFLASH_JEDEC_ID);                //��JEDEC_ID��ָ��

	ID |= SPI_ReadByte()<<16;                      //��ȡID
	ID |= SPI_ReadByte()<<8;
	ID |= SPI_ReadByte();
	SPI_CS_DISABLE;                                //ʧ������
	return ID;
}


