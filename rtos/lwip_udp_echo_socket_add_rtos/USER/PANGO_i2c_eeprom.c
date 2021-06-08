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
 ** 函数名称：Delay_ms_eeprom
 ** 函数功能：延时函数，iic等待延时函数，等待iic ready
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
static void Delay_ms_eeprom(__IO uint32_t delay_ms)
{
	for(delay_ms=delay_ms*40000; delay_ms != 0; delay_ms--);
}

/********************************************************************
 ** 函数名称：I2C_EE_BufferWrite
 ** 函数功能：IIC任意位置，页写
 ** 输入参数：i2c:寄存器结构体
 **   		  pBuffer:写数据缓存
 **			  WriteAddr:数据写起始地址
 **           NumByteToWrite:写数据长度
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void I2C_EE_BufferWrite(I2C_TypeDef *i2c, uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite)
{
	uint8_t NumOfPage = 0,NumOfSingle = 0,Addr = 0,count = 0;
	Addr = WriteAddr % I2C_PageSize;										//把首个字节的位置找出来
	count = I2C_PageSize - Addr;											//把写完该页page的个数找出来
	NumOfPage = NumByteToWrite / I2C_PageSize;								//找出你要写的数据能占几页page
	NumOfSingle = NumByteToWrite % I2C_PageSize;							//找出写完page以后还剩多少个字节
	
	if(Addr == 0)															//如果上来要写的位置是某一个page 的 第一个位置
	{
		if(NumOfPage == 0)													//如果要写的字数小于一页page 所需要的大小
		{
			I2C_EE_PageWrite(i2c,pBuffer,WriteAddr,NumOfSingle);			//直接开始从page 写
		}
		else
		{
			while(NumOfPage--)												//如果page >0 那就写完page  
			{
				I2C_EE_PageWrite(i2c,pBuffer,WriteAddr,I2C_PageSize);		//写一页page
				WriteAddr += I2C_PageSize;									//把地址进行累加
				pBuffer += I2C_PageSize;									//字符往后加
			}
			if(NumOfSingle!=0)												//写完你要写的page 以后如果还有写的数据
			{
				I2C_EE_PageWrite(i2c,pBuffer,WriteAddr,NumOfSingle);		//将剩下的字符写进去
			}
		}
	}
	else																	//不是从该页的页首开始写
	{
		if(NumOfPage == 0)													//要写的字符数小于一page
		{
			if(NumOfSingle < count)											//如果写的数还不够写完1page的数的话
			{
				I2C_EE_PageWrite(i2c,pBuffer,WriteAddr,NumOfSingle);		//直接写进去
			}
			else															//如果要写的数据大于写完这一页的字数
			{
				I2C_EE_PageWrite(i2c,pBuffer,WriteAddr,count);				//先把这一页写完
				WriteAddr += count;											//将地址累加
				pBuffer += count;//
				I2C_EE_PageWrite(i2c,pBuffer,WriteAddr,NumOfSingle-count);	//再去写完剩下的字节数
		  }
		}
		else																//如果要写的数据大于一page
		{
			NumByteToWrite -= count;										//这个是写完本页剩下的字节数
			NumOfPage = NumByteToWrite / I2C_PageSize;						//这个是还剩下的数据所占有的页数
			NumOfSingle = NumByteToWrite % I2C_PageSize;					//剩下的数据写完页数以后还剩下的字节数
			if(count != 0)													//如果要写完一页需要的字节数不是0；
			{
				I2C_EE_PageWrite(i2c,pBuffer,WriteAddr,count);				//先把这一页写完
				WriteAddr += count;
				pBuffer += count;
			}
			while(NumOfPage--)												//写完剩下的page
			{
				I2C_EE_PageWrite(i2c,pBuffer,WriteAddr,I2C_PageSize);
				WriteAddr += I2C_PageSize;
				pBuffer += I2C_PageSize;
			}
			if(NumOfSingle != 0)											//将最后的字节写进去
			{
				I2C_EE_PageWrite(i2c,pBuffer,WriteAddr,NumOfSingle);
			}
		}
	}
}

/********************************************************************
 ** 函数名称：I2C_EE_ByteRead
 ** 函数功能：IIC单字节读
 ** 输入参数：i2c:寄存器结构体
 **   		  ReadAddr:读数据地址
 ** 输出参数：无
 ** 返回参数：data:读取的数据
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
 ** 函数名称：I2C_EE_BytesRead
 ** 函数功能：IIC多字节读
 ** 输入参数：i2c:寄存器结构体
 **   		  pBuffer:读数据缓存
 **			  ReadAddr:数据读起始地址
 **           NumByteToRead:读数据长度
 ** 输出参数：无
 ** 返回参数：无
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
 ** 函数名称：I2C_EE_BytesRead
 ** 函数功能：IIC连续多字节读
 ** 输入参数：i2c:寄存器结构体
 **   		  pBuffer:读数据缓存
 **			  ReadAddr:数据读起始地址
 **           NumByteToRead:读数据长度
 ** 输出参数：无
 ** 返回参数：无
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
	
	while(NumByteToRead--)											//写数据
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
 ** 函数名称：I2C_EE_PageWrite
 ** 函数功能：IIC页写
 ** 输入参数：i2c:寄存器结构体
 **   		  pBuffer:写数据缓存
 **			  WriteAddr:数据写起始地址
 **           NumByteToWrite:写数据长度
 ** 输出参数：无
 ** 返回参数：无
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
	
	while(NumByteToWrite--)											//写数据
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
 ** 函数名称：I2C_EE_ByteWrite
 ** 函数功能：IIC单字节写
 ** 输入参数：i2c:寄存器结构体
 **   		  data:写入的数据
 **			  WriteAddr:数据写起始地址
 ** 输出参数：无
 ** 返回参数：无
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
 ** 函数名称：I2C_EE_BytesWrite
 ** 函数功能：IIC多字节写
 ** 输入参数：i2c:寄存器结构体
 **   		  pBuffer:写数据缓存
 **			  WriteAddr:数据写起始地址
 **           NumByteToRead:写数据长度
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void I2C_EE_BytesWrite(I2C_TypeDef *i2c, uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite)
{
	int32_t i;
	
	for(i=0; i<NumByteToWrite; i++)
	{
		I2C_EE_ByteWrite(i2c, pBuffer[i], WriteAddr + i);
	}
}



