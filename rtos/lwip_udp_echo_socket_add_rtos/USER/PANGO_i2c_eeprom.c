/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2019 PANGO 
 * 		
 * @file		PANGO_M1_i2c_eeprom.c
 * @author		Embedded Development Team
 * @version		V1.0.0
 * @date		2019-09-09 09:09:09
 * @brief		I2C EEPROM driver
 ******************************************************************************************
 */
#include "PANGO_i2c_eeprom.h"

/********************************************************************
 ** �������ƣ�Delay_ms_eeprom
 ** �������ܣ���ʱ������iic�ȴ���ʱ�������ȴ�iic ready
 ** �����������
 ** �����������
 ** ���ز�������
 ********************************************************************/
static void Delay_ms_eeprom(__IO uint32_t delay_ms)
{
	for(delay_ms=delay_ms*40000; delay_ms != 0; delay_ms--);
}

/********************************************************************
 ** �������ƣ�I2C_EE_BufferWrite
 ** �������ܣ�IIC����λ�ã�ҳд
 ** ���������i2c:�Ĵ����ṹ��
 **   		  pBuffer:д���ݻ���
 **			  WriteAddr:����д��ʼ��ַ
 **           NumByteToWrite:д���ݳ���
 ** �����������
 ** ���ز�������
 ********************************************************************/
void I2C_EE_BufferWrite(I2C_TypeDef *i2c, uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite)
{
	uint8_t NumOfPage = 0,NumOfSingle = 0,Addr = 0,count = 0;
	Addr = WriteAddr % I2C_PageSize;										//���׸��ֽڵ�λ���ҳ���
	count = I2C_PageSize - Addr;											//��д���ҳpage�ĸ����ҳ���
	NumOfPage = NumByteToWrite / I2C_PageSize;								//�ҳ���Ҫд��������ռ��ҳpage
	NumOfSingle = NumByteToWrite % I2C_PageSize;							//�ҳ�д��page�Ժ�ʣ���ٸ��ֽ�
	
	if(Addr == 0)															//�������Ҫд��λ����ĳһ��page �� ��һ��λ��
	{
		if(NumOfPage == 0)													//���Ҫд������С��һҳpage ����Ҫ�Ĵ�С
		{
			I2C_EE_PageWrite(i2c,pBuffer,WriteAddr,NumOfSingle);			//ֱ�ӿ�ʼ��page д
		}
		else
		{
			while(NumOfPage--)												//���page >0 �Ǿ�д��page  
			{
				I2C_EE_PageWrite(i2c,pBuffer,WriteAddr,I2C_PageSize);		//дһҳpage
				WriteAddr += I2C_PageSize;									//�ѵ�ַ�����ۼ�
				pBuffer += I2C_PageSize;									//�ַ������
			}
			if(NumOfSingle!=0)												//д����Ҫд��page �Ժ��������д������
			{
				I2C_EE_PageWrite(i2c,pBuffer,WriteAddr,NumOfSingle);		//��ʣ�µ��ַ�д��ȥ
			}
		}
	}
	else																	//���ǴӸ�ҳ��ҳ�׿�ʼд
	{
		if(NumOfPage == 0)													//Ҫд���ַ���С��һpage
		{
			if(NumOfSingle < count)											//���д����������д��1page�����Ļ�
			{
				I2C_EE_PageWrite(i2c,pBuffer,WriteAddr,NumOfSingle);		//ֱ��д��ȥ
			}
			else															//���Ҫд�����ݴ���д����һҳ������
			{
				I2C_EE_PageWrite(i2c,pBuffer,WriteAddr,count);				//�Ȱ���һҳд��
				WriteAddr += count;											//����ַ�ۼ�
				pBuffer += count;//
				I2C_EE_PageWrite(i2c,pBuffer,WriteAddr,NumOfSingle-count);	//��ȥд��ʣ�µ��ֽ���
		  }
		}
		else																//���Ҫд�����ݴ���һpage
		{
			NumByteToWrite -= count;										//�����д�걾ҳʣ�µ��ֽ���
			NumOfPage = NumByteToWrite / I2C_PageSize;						//����ǻ�ʣ�µ�������ռ�е�ҳ��
			NumOfSingle = NumByteToWrite % I2C_PageSize;					//ʣ�µ�����д��ҳ���Ժ�ʣ�µ��ֽ���
			if(count != 0)													//���Ҫд��һҳ��Ҫ���ֽ�������0��
			{
				I2C_EE_PageWrite(i2c,pBuffer,WriteAddr,count);				//�Ȱ���һҳд��
				WriteAddr += count;
				pBuffer += count;
			}
			while(NumOfPage--)												//д��ʣ�µ�page
			{
				I2C_EE_PageWrite(i2c,pBuffer,WriteAddr,I2C_PageSize);
				WriteAddr += I2C_PageSize;
				pBuffer += I2C_PageSize;
			}
			if(NumOfSingle != 0)											//�������ֽ�д��ȥ
			{
				I2C_EE_PageWrite(i2c,pBuffer,WriteAddr,NumOfSingle);
			}
		}
	}
}

/********************************************************************
 ** �������ƣ�I2C_EE_ByteRead
 ** �������ܣ�IIC���ֽڶ�
 ** ���������i2c:�Ĵ����ṹ��
 **   		  ReadAddr:�����ݵ�ַ
 ** �����������
 ** ���ز�����data:��ȡ������
 ********************************************************************/
uint8_t I2C_EE_ByteRead(I2C_TypeDef *i2c, uint16_t ReadAddr)
{
	uint8_t data=0;
	//while(i2c->SR&I2C_SR_BUSY);
	i2c->TXR = EEPROM_ADDRESS | 0;
	i2c->CR = I2C_CMD_STA|I2C_CMD_WR;	
	while(i2c->SR&I2C_SR_TIP);
	while(i2c->SR&I2C_SR_RXACK);										//wait ack-----Over Here
	
	i2c->TXR = ReadAddr >> 8;
	i2c->CR = I2C_CMD_WR;												//stop
	while(i2c->SR&I2C_SR_TIP);											//wait TIP
	while(i2c->SR&I2C_SR_RXACK);										//wait ack
	
	i2c->TXR = ReadAddr & 0x00ff;
	i2c->CR = I2C_CMD_WR;												//stop
	while(i2c->SR&I2C_SR_TIP);											//wait TIP
	while(i2c->SR&I2C_SR_RXACK);										//wait ack

	i2c->TXR = EEPROM_ADDRESS | 1;	
	i2c->CR = (I2C_CMD_STA|I2C_CMD_WR);
	while(i2c->SR&I2C_SR_TIP);
	while(i2c->SR&I2C_SR_RXACK);										//wait ack	

	i2c->CR = (I2C_CMD_ACK|I2C_CMD_STO|I2C_CMD_RD);						//send nack
	while(i2c->SR&I2C_SR_TIP);
	data = i2c->RXR;
	Delay_ms_eeprom(3);
	return data;
}

/********************************************************************
 ** �������ƣ�I2C_EE_BytesRead
 ** �������ܣ�IIC���ֽڶ�
 ** ���������i2c:�Ĵ����ṹ��
 **   		  pBuffer:�����ݻ���
 **			  ReadAddr:���ݶ���ʼ��ַ
 **           NumByteToRead:�����ݳ���
 ** �����������
 ** ���ز�������
 ********************************************************************/
void I2C_EE_BytesRead(I2C_TypeDef *i2c, uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead)		
{
	int32_t i;
	for(i=0; i<NumByteToRead; i++)
	{
		pBuffer[i] = I2C_EE_ByteRead(i2c, ReadAddr + i);
	}
}

/********************************************************************
 ** �������ƣ�I2C_EE_BytesRead
 ** �������ܣ�IIC�������ֽڶ�
 ** ���������i2c:�Ĵ����ṹ��
 **   		  pBuffer:�����ݻ���
 **			  ReadAddr:���ݶ���ʼ��ַ
 **           NumByteToRead:�����ݳ���
 ** �����������
 ** ���ز�������
 ********************************************************************/
void I2C_EE_BufferRead(I2C_TypeDef *i2c, uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead)
{
	//while(i2c->SR&I2C_SR_BUSY);
	i2c->TXR = EEPROM_ADDRESS | 0;
	i2c->CR = I2C_CMD_STA|I2C_CMD_WR;	
	while(i2c->SR&I2C_SR_TIP);
	while(i2c->SR&I2C_SR_RXACK);									//wait ack-----Over Here
	
	i2c->TXR = ReadAddr >> 8;
	i2c->CR = I2C_CMD_WR;											//stop
	while(i2c->SR&I2C_SR_TIP);										//wait TIP
	while(i2c->SR&I2C_SR_RXACK);									//wait ack
	
	i2c->TXR = ReadAddr & 0x00ff;
	i2c->CR = I2C_CMD_WR;											//stop
	while(i2c->SR&I2C_SR_TIP);										//wait TIP
	while(i2c->SR&I2C_SR_RXACK);									//wait ack

	i2c->TXR = EEPROM_ADDRESS | 1;	
	i2c->CR = (I2C_CMD_STA|I2C_CMD_WR);
	while(i2c->SR&I2C_SR_TIP);
	while(i2c->SR&I2C_SR_RXACK);									//wait ack
	
	while(NumByteToRead--)											//д����
	{
		if(0 == NumByteToRead)
		{
			i2c->CR = I2C_CMD_STO|I2C_CMD_RD;						//send nack
		}
		else
		{
			i2c->CR = I2C_CMD_ACK|I2C_CMD_RD;						
		}
		while(i2c->SR&I2C_SR_TIP);
		*pBuffer = i2c->RXR;
		pBuffer++;
	}
	Delay_ms_eeprom(3);
}

/********************************************************************
 ** �������ƣ�I2C_EE_PageWrite
 ** �������ܣ�IICҳд
 ** ���������i2c:�Ĵ����ṹ��
 **   		  pBuffer:д���ݻ���
 **			  WriteAddr:����д��ʼ��ַ
 **           NumByteToWrite:д���ݳ���
 ** �����������
 ** ���ز�������
 ********************************************************************/
void I2C_EE_PageWrite(I2C_TypeDef *i2c, uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite)
{
	//while(i2c->SR&I2C_SR_BUSY);
	i2c->TXR = EEPROM_ADDRESS | 0;
	i2c->CR = I2C_CMD_STA|I2C_CMD_WR;
	while(i2c->SR&I2C_SR_TIP);										//wait TIP
	while(i2c->SR&I2C_SR_RXACK);									//wait ack-----Over Here

	i2c->TXR = WriteAddr >> 8;	
	i2c->CR = (I2C_CMD_WR);
	while(i2c->SR&I2C_SR_TIP);										//wait TIP
	while(i2c->SR&I2C_SR_RXACK);									//wait ack
	
	i2c->TXR = WriteAddr & 0x00ff;	
	i2c->CR = (I2C_CMD_WR);
	while(i2c->SR&I2C_SR_TIP);										//wait TIP
	while(i2c->SR&I2C_SR_RXACK);									//wait ack
	
	while(NumByteToWrite--)											//д����
	{
		i2c->TXR = *pBuffer;

		pBuffer++;

		i2c->CR |= I2C_CMD_WR;
		while(i2c->SR&I2C_SR_TIP);									//wait TIP
		while(i2c->SR&I2C_SR_RXACK);								//wait ack
	}
	i2c->CR |= I2C_CMD_STO;
	while(i2c->SR&I2C_SR_TIP);										//wait TIP
	while(i2c->SR&I2C_SR_RXACK);									//wait ack
	while(i2c->SR&I2C_SR_BUSY);
	
	Delay_ms_eeprom(3);												//Wait the data to I2C Ready
}

/********************************************************************
 ** �������ƣ�I2C_EE_ByteWrite
 ** �������ܣ�IIC���ֽ�д
 ** ���������i2c:�Ĵ����ṹ��
 **   		  data:д�������
 **			  WriteAddr:����д��ʼ��ַ
 ** �����������
 ** ���ز�������
 ********************************************************************/
void I2C_EE_ByteWrite(I2C_TypeDef *i2c, uint8_t data, uint16_t WriteAddr)
{
	//while(i2c->SR&I2C_SR_BUSY);
	i2c->TXR = EEPROM_ADDRESS | 0;
	i2c->CR = I2C_CMD_STA|I2C_CMD_WR;
	while(i2c->SR&I2C_SR_TIP);										//wait TIP
	while(i2c->SR&I2C_SR_RXACK);									//wait ack-----Over Here

	i2c->TXR = WriteAddr >> 8;	
	i2c->CR = (I2C_CMD_WR);
	while(i2c->SR&I2C_SR_TIP);										//wait TIP
	while(i2c->SR&I2C_SR_RXACK);									//wait ack
	
	i2c->TXR = WriteAddr & 0x00ff;	
	i2c->CR = (I2C_CMD_WR);
	while(i2c->SR&I2C_SR_TIP);										//wait TIP
	while(i2c->SR&I2C_SR_RXACK);									//wait ack
	
	i2c->TXR = data;
	i2c->CR |= (I2C_CMD_STO|I2C_CMD_WR);
	while(i2c->SR&I2C_SR_TIP);										//wait TIP
	while(i2c->SR&I2C_SR_RXACK);									//wait ack
	while(i2c->SR&I2C_SR_BUSY);
	
	Delay_ms_eeprom(3);												//Wait the data to I2C Ready
		
}

/********************************************************************
 ** �������ƣ�I2C_EE_BytesWrite
 ** �������ܣ�IIC���ֽ�д
 ** ���������i2c:�Ĵ����ṹ��
 **   		  pBuffer:д���ݻ���
 **			  WriteAddr:����д��ʼ��ַ
 **           NumByteToRead:д���ݳ���
 ** �����������
 ** ���ز�������
 ********************************************************************/
void I2C_EE_BytesWrite(I2C_TypeDef *i2c, uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite)
{
	int32_t i;
	
	for(i=0; i<NumByteToWrite; i++)
	{
		I2C_EE_ByteWrite(i2c, pBuffer[i], WriteAddr + i);
	}
}



