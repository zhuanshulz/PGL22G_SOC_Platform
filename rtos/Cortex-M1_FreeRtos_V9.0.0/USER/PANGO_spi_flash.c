/*
 * ***************************************************************************************** 		
 * 文件名称：PANGO_spi_flash.c
 * 功能描述：SPI Flash应用驱动库函数
 ******************************************************************************************
 */
/******************************** SPI FLASH信息 ********************************
SPI FLASH种类很多, 但软件基本都兼容

1、W25X64信息：
页(Page) ------ 256Byte
扇区(Sector) -- 4KByte ------ (等于16页)
块(Block) ----- 64KByte ----- (等于16扇区)

W25X64芯片容量：8MB (64Mbit)
          页数：64*16*32 (2M/256)
        扇区数：64*32
          块数：128

2、读写操作：
读 ------------ 一次最大读一页(256B)
写 ------------ 页
擦出 ---------- 扇区、块、整个芯片

3、控制和状态寄存器命令(默认:0x00)
BIT位  7   6   5   4   3   2   1   0
      SPR  RV  TB  BP2 BP1 BP0 WEL BUSY
SPR:默认0,状态寄存器保护位,配合WP使用
TB,BP2,BP1,BP0:FLASH区域写保护设置
WEL:写使能锁定
BUSY:忙标记位(1,忙;0,空闲)
********************************************************************************/

#include "PANGO_spi_flash.h"

/********************************************************************
 ** 函数名称：SPI_WriteByte
 ** 函数功能：SPI写一个字节
 ** 输入参数：TxData:写入的数据
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void SPI_WriteByte(uint8_t TxData)
{
	SPI_WriteData(TxData);
	while(SPI_GetTmtStatus() == 1);
}

/********************************************************************
 ** 函数名称：print_num
 ** 函数功能：打印成十进制数
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：读出的SPI数据
 ********************************************************************/
uint8_t SPI_ReadByte(void)
{
	while(SPI_GetTmtStatus() == 1);
	SPI_SetRcvStatus();
	while(SPI_GetRcvStatus() == 1);
	return SPI_ReadData();
}

/********************************************************************
 ** 函数名称：SFLASH_WriteEnable
 ** 函数功能：SPI_FLASH写使能，将WEL置位
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void SFLASH_WriteEnable(void)
{
	SPI0_CS_ENABLE;                                 //使能器件
	SPI_WriteByte(SFLASH_WRITE_ENABLE);            //《写使能》指令
	SPI_CS_DISABLE;                                //失能器件
}

/********************************************************************
 ** 函数名称：SFLASH_WriteDisable
 ** 函数功能：SPI_FLASH写禁止,将WEL清零
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
static void SFLASH_WriteDisable(void)
{
	SPI0_CS_ENABLE;                                 //使能器件
	SPI_WriteByte(SFLASH_WRITE_DISABLE);           //《写失能》指令
	SPI_CS_DISABLE;                                //失能器件
}

/********************************************************************
 ** 函数名称：SFLASH_ReadSR
 ** 函数功能：SPI_FLASH写
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：data_tmp:读取字节
 ********************************************************************/
uint8_t SFLASH_ReadSR(void)
{
	uint8_t data_tmp;
	SPI0_CS_ENABLE;                                 //使能器件
	SPI_WriteByte(SFLASH_READ_STATUS_REG);         //《读状态寄存器》指令
	data_tmp = SPI_ReadByte();                     //读取一个字节
	SPI_CS_DISABLE;                                //失能器件
	return data_tmp;
}

/********************************************************************
** 函数名称：SFLASH_WriteSR
** 函数功能：写SFLASH状态寄存器
** 输入参数：SR:写状态寄存器命令
** 输出参数：无
** 返回参数：无
********************************************************************/
void SFLASH_WriteSR(uint8_t SR)
{
	SFLASH_WriteEnable();                          //写使能
	SPI_WriteByte(SFLASH_WRITE_STATUS_REG);        //《写状态寄存器》指令
	SPI_WriteByte(SR);                             //写入一个字节
	SPI_CS_DISABLE;                                //失能器件
}

/********************************************************************
** 函数名称：SFLASH_ReadNByte
** 函数功能：从ReadAddr地址开始连续读取SFLASH的nByte
** 输入参数：pBuffer:数据存储区首地址
**           ReadAddr:要读取SFLASH Flash的首地址地址
**           nByte:要读取的字节数(最大65535B = 64K 块)
** 输出参数：无
** 返回参数：无
********************************************************************/
void SFLASH_ReadNByte(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t nByte)
{
	SPI0_CS_ENABLE;                                 //使能器件
	SPI_WriteByte(SFLASH_READ_DATA);               //《读数据》指令
	SPI_WriteByte((uint8_t)((ReadAddr)>>16));      //发送24bit地址
	SPI_WriteByte((uint8_t)((ReadAddr)>>8));
	SPI_WriteByte((uint8_t)ReadAddr);

	while(nByte--)                                 //循环读数
	{
		*pBuffer = SPI_ReadByte();
		pBuffer++;
	}

	SPI_CS_DISABLE;                                //失能器件
}

/********************************************************************
** 函数名称：SFLASH_FastReadNByte
** 函数功能：从ReadAddr地址开始连续快速读取SFLASH的nByte
** 输入参数：pBuffer:数据存储区首地址
**           ReadAddr:要读取SFLASH Flash的首地址地址
**           nByte:要读取的字节数(最大65535B = 64K 块)
** 输出参数：无
** 返回参数：无
********************************************************************/
void SFLASH_FastReadNByte(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t nByte)
{
	SPI0_CS_ENABLE;                                 //使能器件
	SPI_WriteByte(SFLASH_FAST_READ);               //《快读数据》指令
	SPI_WriteByte((uint8_t)((ReadAddr)>>16));      //发送24bit地址
	SPI_WriteByte((uint8_t)((ReadAddr)>>8));
	SPI_WriteByte((uint8_t)ReadAddr);
	SPI_WriteByte(0xFF);                           //等待8个时钟

	while(nByte--)                                 //循环读数
	{
		*pBuffer = SPI_ReadByte();
		pBuffer++;
	}

	SPI_CS_DISABLE;                                //失能器件
}

/********************************************************************
** 函数名称：SFLASH_WritePage
** 函数功能：在SFLASH内写入少于1页(256个字节)的数据
** 输入参数：pBuffer:写入数据区首地址
**           WriteAddr:要写入Flash的地址
**           nByte:要写入的字节数(最大1页)
** 输出参数：无
** 返回参数：无
********************************************************************/
void SFLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t nByte)
{
	SFLASH_WriteEnable();                          //写使能

	SPI0_CS_ENABLE;                                 //使能器件
	SPI_WriteByte(SFLASH_WRITE_PAGE);              //《页编程》指令
	SPI_WriteByte((uint8_t)((WriteAddr)>>16));     //发送24bit地址
	SPI_WriteByte((uint8_t)((WriteAddr)>>8));
	SPI_WriteByte((uint8_t)WriteAddr);

	while (nByte--)
	{
		SPI_WriteByte(*pBuffer);
		pBuffer++;
	}

	SPI_CS_DISABLE;
	SFLASH_WaitForNoBusy();                        //等待空闲（等待写入结束）
}

/********************************************************************
** 函数名称：SFLASH_WriteNoCheck
** 函数功能：无检验写SFLASH
**           必须确保所写的地址范围内的数据全部为0xFF,否则在非0xFF处写入的数据将失败!
**           具有自动换页功能
**           在指定地址开始写入指定长度的数据,但是要确保地址不越界!
** 输入参数：pBuffer:写入数据区首地址
**           WriteAddr:要写入Flash的地址
**           nByte:要写入的字节数
** 输出参数：无
** 返回参数：无
********************************************************************/
void SFLASH_WriteNoCheck(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t nByte)
{
	uint16_t PageRemain = 256 - WriteAddr%256;     //单页剩余可写的字节数

	if(nByte <= PageRemain)
	PageRemain = nByte;                          	//不大于256个字节

	while(1)
	{
		SFLASH_WritePage(pBuffer, WriteAddr, PageRemain);
		if(nByte == PageRemain)                      //写入结束
		  break;
		else                                         //写入未结束
		{
			pBuffer += PageRemain;                   //下一页写入数据
			WriteAddr += PageRemain;                 //下一页写入数据地址
			nByte -= PageRemain;                     //待写入字节数递减

			if(nByte > 256)
				PageRemain = 256;                    //待写入1页(256字节)的数据
			else
				PageRemain = nByte;                  //待写入少于1页(256字节)的数据
		}
	}
}

/********************************************************************
** 函数名称：SFLASH_WriteNByte
** 函数功能：从ReadAddr地址开始连续写入nByte到SFLASH中
** 输入参数：pBuffer:写入数据区首地址
**           WriteAddr:要写入Flash的地址
**           nByte:要写入的字节数(最大65535B = 64K 块)
** 输出参数：无
** 返回参数：无
** N25Q128 = 128-Mbit, 4-Kbyte subsector
** sectors = 128Mbit / 4KB = (128*1024/8)/4 = 4,096
********************************************************************/
void SFLASH_WriteNByte(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t nByte)
{
	static uint8_t SectorBuf[4096];                //扇区buf
	uint32_t SecPos;                               //扇区位置
	uint16_t SecOff;                               //扇区偏移
	uint16_t SecRemain;                            //剩余扇区
	uint16_t i;

	SecPos = WriteAddr/4096;                       //地址所在扇区(0~511)
	SecOff = WriteAddr%4096;                       //地址所在扇区的偏移
	SecRemain = 4096-SecOff;                       //地址所在扇区剩余字节数(扇区大小4096B=4KB)

	if(nByte <= SecRemain)
	SecRemain = nByte;                           	//写入数据大小 < 剩余空间大小 (即剩余空间够保存这些数据)

	while(1)
	{
		SFLASH_ReadNByte(SectorBuf, SecPos*4096, 4096);        	//读出整个扇区的内容
		for(i=0; i<SecRemain; i++)                             	//校验数据,是否需要擦除
		{
			if(SectorBuf[SecOff + i] != 0xFF)                   //存储数据不为0xFF 则需要擦除
			break;
		}
		if(i < SecRemain)                                      	//需要擦除
		{
			SFLASH_EraseSector(SecPos);                         //擦除该扇区
			for(i=0; i<SecRemain; i++)                          //保存写入的数据(第1次时，是写入那扇区后面剩余的空间)
			{
				SectorBuf[SecOff + i] = pBuffer[i];
			}
			SFLASH_WriteNoCheck(SectorBuf, SecPos*4096, 4096);   //写入整个扇区（扇区 = 老数据 + 新写入数据）
		}
		else
			SFLASH_WriteNoCheck(pBuffer, WriteAddr, SecRemain);  //不需要擦除,直接写入扇区剩余空间

		if(nByte == SecRemain)                       			//写入结束
		{
			SFLASH_WriteDisable();                     			//写失能, 退出写
			break;
		}
		else                                         			//写入未结束
		{
			SecPos++;                                  			//扇区地址增1
			SecOff = 0;                                			//偏移位置归零
			pBuffer += SecRemain;                      			//指针偏移
			WriteAddr += SecRemain;                    			//写地址偏移
			nByte -= SecRemain;                        			//待写入字节数递减
		if(nByte > 4096)
			SecRemain = 4096;                        			//待写入1扇区(4096字节)的数据
		else
			SecRemain = nByte;                       			//待写入少于1扇区(4096字节)的数据
		}
	}
}

/********************************************************************
** 函数名称：SFLASH_WaitForNoBusy
** 函数功能：等待不忙
** 输入参数无
** 输出参数：无
** 返回参数：无
********************************************************************/
void SFLASH_WaitForNoBusy(void)
{
	while((SFLASH_ReadSR()&0x01)==0x01);           				//等待BUSY位清空
}

/********************************************************************
** 函数名称：SFLASH_EraseBlock
** 函数功能：擦除块，擦除块需要一定时间
** 输入参数BlockAddr:块地址 0~31
** 输出参数：无
** 返回参数：无
********************************************************************/
void SFLASH_EraseBlock(uint32_t BlockAddr)
{
	BlockAddr *= 65536;                            //块首地址
	SFLASH_WriteEnable();                          //写使能
	SFLASH_WaitForNoBusy();
	SPI0_CS_ENABLE;                                 //使能器件
	SPI_WriteByte(SFLASH_ERASE_BLOCK);             //《擦除块》指令
	SPI_WriteByte((uint8_t)((BlockAddr)>>16));     //擦除地址
	SPI_WriteByte((uint8_t)((BlockAddr)>>8));
	SPI_WriteByte((uint8_t)BlockAddr);
	SPI_CS_DISABLE;

	SFLASH_WaitForNoBusy();                        //等待擦除完成
}

/********************************************************************
** 函数名称：SFLASH_EraseSector
** 函数功能：擦除扇区
** 输入参数SectorAddr:扇区地址 0~511
** 输出参数：无
** 返回参数：无
********************************************************************/
void SFLASH_EraseSector(uint32_t SectorAddr)
{
	SectorAddr *= 4096;                            //扇区首地址
	SFLASH_WriteEnable();                          //写使能
	SFLASH_WaitForNoBusy();
	SPI0_CS_ENABLE;                                 //使能器件
	SPI_WriteByte(SFLASH_ERASE_SECTOR);            //《擦除扇区》指令
	SPI_WriteByte((uint8_t)((SectorAddr)>>16));    //擦除地址
	SPI_WriteByte((uint8_t)((SectorAddr)>>8));
	SPI_WriteByte((uint8_t)SectorAddr);
	SPI_CS_DISABLE;

	SFLASH_WaitForNoBusy();                        //等待擦除完成
}

/********************************************************************
** 函数名称：SFLASH_EraseChip
** 函数功能：擦除整个芯片(整片擦除时间较长)
** 输入参数无
** 输出参数：无
** 返回参数：无
********************************************************************/
void SFLASH_EraseChip(void)
{
	SFLASH_WriteEnable();                          //写使能
	SFLASH_WaitForNoBusy();
	SPI0_CS_ENABLE;                                 //使能器件
	SPI_WriteByte(SFLASH_ERASE_CHIP);              //《擦除芯片》指令
	SPI_CS_DISABLE;

	SFLASH_WaitForNoBusy();                        //等待芯片擦除结束
}

/********************************************************************
** 函数名称：SFLASH_PowerDown
** 函数功能：进入掉电模式
** 输入参数无
** 输出参数：无
** 返回参数：无
********************************************************************/
void SFLASH_PowerDown(void)
{
	SPI0_CS_ENABLE;                                 //使能器件
	SPI_WriteByte(SFLASH_POWER_DOWN);              //《掉电》指令
	SPI_CS_DISABLE;                                //失能器件
}

/********************************************************************
** 函数名称：SFLASH_WAKEUP
** 函数功能：掉电唤醒
** 输入参数无
** 输出参数：无
** 返回参数：无
********************************************************************/
void SFLASH_WAKEUP(void)
{
	SPI0_CS_ENABLE;                                 //使能器件
	SPI_WriteByte(SFLASH_RELEASE_POWER_DOWN);      //《掉电唤醒》指令
	SPI_CS_DISABLE;                                //失能器件
}

/********************************************************************
** 函数名称：SFLASH_ReadID
** 函数功能：读取芯片ID SFLASH的ID(W25X64: EF16）
** 输入参数无
** 输出参数：无
** 返回参数：ID:16位ID号
********************************************************************/
uint16_t SFLASH_ReadID(void)
{
	uint16_t ID = 0;
	SPI0_CS_ENABLE;                                 //使能器件

	SPI_WriteByte(SFLASH_DEVICE_ID);               //《设备ID》指令
	SPI_WriteByte(0x00);
	SPI_WriteByte(0x00);
	SPI_WriteByte(0x00);

	ID |= SPI_ReadByte()<<8;                       //读取ID
	ID |= SPI_ReadByte();
	SPI_CS_DISABLE;                                //失能器件
	return ID;
}

/********************************************************************
** 函数名称：SFLASH_ReadJEDEC_ID
** 函数功能：读取芯片JEDEC_ID(W25X64: EF4017）
** 输入参数无
** 输出参数：无
** 返回参数：ID:24位ID号
********************************************************************/
uint32_t SFLASH_ReadJEDEC_ID(void)
{
	uint32_t ID = 0;
	SPI0_CS_ENABLE;                                 //使能器件

	SPI_WriteByte(SFLASH_JEDEC_ID);                //《JEDEC_ID》指令

	ID |= SPI_ReadByte()<<16;                      //读取ID
	ID |= SPI_ReadByte()<<8;
	ID |= SPI_ReadByte();
	SPI_CS_DISABLE;                                //失能器件
	return ID;
}


