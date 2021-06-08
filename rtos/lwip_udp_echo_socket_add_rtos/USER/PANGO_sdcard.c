#include "PANGO_sdcard.h"
#include "PANGO_M1.h"

//等待SD卡进行某些操作的计数器，超过这个次数认为等待超时，
//高速单片机（如STM32）可以将这个数值适当扩大
#define WAIT_COUNT 10
/* SD卡命令超时时间(单位 8clock)*/
/* timeout of command */
#define SD_CMD_TIMEOUT   	 	100
//初始化完成后可获得SD卡的类型，方便其他程序使用
unsigned char SD_TYPE = 0;

/* Definitions of physical drive number for each drive */
#define SD_CARD		0	/* Example: Map Ramdisk to physical drive 0 */
//#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
//#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */
/* MMC/SD command */
#define CMD0	(0)			/* GO_IDLE_STATE */
#define CMD1	(1)			/* SEND_OP_COND (MMC) */
#define	ACMD41	(0x80+41)	/* SEND_OP_COND (SDC) */
#define CMD8	(8)			/* SEND_IF_COND */
#define CMD9	(9)			/* SEND_CSD */
#define CMD10	(10)		/* SEND_CID */
#define CMD12	(12)		/* STOP_TRANSMISSION */
#define ACMD13	(0x80+13)	/* SD_STATUS (SDC) */
#define CMD16	(16)		/* SET_BLOCKLEN */
#define CMD17	(17)		/* READ_SINGLE_BLOCK */
#define CMD18	(18)		/* READ_MULTIPLE_BLOCK */
#define CMD23	(23)		/* SET_BLOCK_COUNT (MMC) */
#define	ACMD23	(0x80+23)	/* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24	(24)		/* WRITE_BLOCK */
#define CMD25	(25)		/* WRITE_MULTIPLE_BLOCK */
#define CMD32	(32)		/* ERASE_ER_BLK_START */
#define CMD33	(33)		/* ERASE_ER_BLK_END */
#define CMD38	(38)		/* ERASE */
#define CMD55	(55)		/* APP_CMD */
#define CMD58	(58)		/* READ_OCR */
#define	MMC_WP		0 /* Write protected (yes:true, no:false, default:false) */
#define	MMC_CD		1 
void Delay_s(__IO uint32_t nCount)
{
	for(; nCount != 0; nCount--);
}

/*SPI低速模式，低于400KHZ*/
void SPI_Low(void)
{
	SDCARD->clk_div = (uint32_t)498;	//low speed;
}

/*SPI高速模式，但不超过25MHZ*/
void SPI_High(void)
{
	SDCARD->clk_div = (uint32_t)2;	//fast speed;
}

/* Exchange a byte */
BYTE xchg_spi (
	BYTE dat	/* Data to send */
)
{
#if 0
	SPIx_DR = dat;
	while (SPIx_SR & _BV(7)) ;
	return (BYTE)SPIx_DR;
#else
		while (SDCARD->start_stop != (uint32_t)0) Delay_s(20);
    SDCARD->spi_write_data = dat;
		SDCARD->start_stop = (uint32_t)14114;
    while (SDCARD->start_stop == 14115) Delay_s(20);
		if(SDCARD->start_stop == (uint32_t)0)
			return SDCARD->spi_read_data;
		return 0;
#endif
}
#define CS_HIGH() SDCARD->cs_control=0x00000000;
#define CS_LOW() SDCARD->cs_control=0xffffffff;
#define FCLK_SLOW() SDCARD->clk_div = (uint32_t)498;	//low speed;
#define FCLK_FAST() SDCARD->clk_div = (uint32_t)2;	//fast speed;

void SD_Disable()//关SD卡
{
	SDCARD->cs_control=0x00000000;
}
 void SD_Enable()//开片选
{
	SDCARD->cs_control=0xffffffff;
}
UINT Timer1, Timer2;	/* 1kHz decrement timer stopped at zero (disk_timerproc()) */

BYTE MMC_SD_SendCommand(		/* Return value: R1 resp (bit7==1:Failed to send) */
	BYTE cmd,		/* Command index */
	DWORD arg		/* Argument */
)
{
	BYTE r1;
	BYTE retry=0;
	SD_Enable();
	Delay_s(10);
	/* Send command packet */
	xchg_spi(0x40 | cmd);				/* Start + command index */
	xchg_spi((BYTE)(arg >> 24));		/* Argument[31..24] */
	xchg_spi((BYTE)(arg >> 16));		/* Argument[23..16] */
	xchg_spi((BYTE)(arg >> 8));			/* Argument[15..8] */
	xchg_spi((BYTE)arg);				/* Argument[7..0] */
	if(cmd == 0x0)
		xchg_spi(0x95);
		else if (cmd == 0x8)
			xchg_spi(0x87);
		else
			xchg_spi(0xff);
	while((r1 = xchg_spi(0xff)) == 0xff)//等待响应，
	{
		Delay_s(10);
		if(retry++ > 20) break;//超时退出
	}
	return r1;//返回状态值
}
void MMC_SD_Init(void){
	SD_Enable();
	FCLK_SLOW();
	SD_Disable();
}

//sd卡复位
BYTE MMC_SD_Reset(void)
{
	BYTE i;
	BYTE retry;
	BYTE r1=0;
	retry = 0;
	SPI_Low();
	SD_Disable();
	do
	{
		for(i=0;i<10;i++) {
			xchg_spi(0xff);
			Delay_s(10);
		}
		r1 = MMC_SD_SendCommand(0, 0);//发idle命令
		retry++;
		if(retry>10) return 1;//超时退出
	} while(r1 != 0x01);
	retry = 0;
	do
	{
		r1 = MMC_SD_SendCommand(8, 0x1aa);//发active命令
		Delay_s(10);
		retry++;
		//if(retry>100) return 1;//超时退出
	} while(r1 != 0x01);
	if(r1 == 0x01)
	{
		xchg_spi(0xff);
		xchg_spi(0xff);
		xchg_spi(0xff);
		xchg_spi(0xff);
	}
	SD_Disable();
	xchg_spi(0xff);
	do
	{
		r1 = MMC_SD_SendCommand(55, 0);//发卡初始化指令CMD55+ACMD41
		if(r1!=0x01)return r1;
		Delay_s(10);
		r1 = MMC_SD_SendCommand(41, 0x40000000);//发卡初始化指令CMD55+ACMD41
		Delay_s(10);
		if(retry>100) return r1;//超时退出
	} while(r1!=0);
	//初始化指令发送完成，接下来获取OCR信息
	//-----------鉴别SD2.0卡版本开始-----------
	r1 = MMC_SD_SendCommand(CMD58, 0);
	if(r1!=0x00)return r1; //如果命令没有返回正确应答，直接退出，返回应答
	//读OCR指令发出后，紧接着是4字节的OCR信息
	xchg_spi(0xFF);
	xchg_spi(0xFF);
	xchg_spi(0xFF);
	xchg_spi(0xFF);
	//OCR接收完成，片选置高
	SD_Disable();
	xchg_spi(0xFF);
//	r1 = MMC_SD_SendCommand(59, 0);//关crc

	r1 = MMC_SD_SendCommand(16, 512);//设扇区大小512
	SPI_High();
	return 0;//正常返回
}
BYTE MMC_SD_GetCID(BYTE *cid_data)
{
	 uint8_t r1;
	//发CMD10命令，读取CID信息
	SD_Enable();
   r1 = MMC_SD_SendCommand(10, 0);
   if(r1 != 0x00)	
   return r1;  	//响应错误，退出 
   //接收16个字节的数据
	 uint16_t i;
	 while(xchg_spi(0xff) != 0xfe);//if(retry++ > 50){SD_Disable();return 1;}
    for(i=0;i<16;i++)	 //将数据写入到数据缓冲区中
    {
        *(cid_data++)=xchg_spi(0xff);
		}
	 SD_Disable();
	 xchg_spi(0xff);
   return 0;
}
//读一个扇区
BYTE MMC_SD_ReadSingleBlock(uint32_t sector, BYTE* buffer)
{
	BYTE r1;
	uint16_t i;
	//BYTE retry=0;
	SD_Enable();
	//r1 = MMC_SD_SendCommand(17, sector<<9);//读命令
	r1 = MMC_SD_SendCommand(17, sector);//读命令
	if(r1 != 0x00)
		return r1;

	//等数据的开始
	while(xchg_spi(0xff) != 0xfe);//if(retry++ > 50){SD_Disable();return 1;}

    for(i=0;i<64;i++)	 //将数据写入到数据缓冲区中
    {
        *(buffer++)=xchg_spi(0xff);
        *(buffer++)=xchg_spi(0xff);
        *(buffer++)=xchg_spi(0xff);
        *(buffer++)=xchg_spi(0xff);
        *(buffer++)=xchg_spi(0xff);
        *(buffer++)=xchg_spi(0xff);
        *(buffer++)=xchg_spi(0xff);
        *(buffer++)=xchg_spi(0xff);
    }
	xchg_spi(0xff);//伪crc
	xchg_spi(0xff);

	SD_Disable();

	return 0;
}
//读多个扇区
BYTE MMC_SD_ReadMultiBlock(uint32_t sector, BYTE* buffer, uint8_t count)
{
	BYTE r1;
	uint16_t i;
	//BYTE retry=0;
	SD_Enable();
	r1 = MMC_SD_SendCommand(18, sector);//读命令
		//r1 = MMC_SD_SendCommand(18, sector<<9);//读命令
	if(r1 != 0x00)	return r1;	 

  do	//开始接收数据 
  {
		//等数据的开始
		while(xchg_spi(0xff) != 0xfe);//if(retry++ > 50){SD_Disable();return 1;}
		for(i=0;i<512;i++)	 //将数据写入到数据缓冲区中
    {
        *(buffer++)=xchg_spi(0xff);
		}
	}while(--count);	
	r1 = MMC_SD_SendCommand(12, 0);//全部传输完成，发送停止命令
	SD_Disable();
	xchg_spi(0xff);
	return 0;	
}
BYTE SD_WaitReady(void)
{
  BYTE r1;
  uint16_t retry=0;
  do
  {
    r1 = xchg_spi(0xFF);
    retry++;
    if(retry==0xfffe)
    	return 1; 
  }while(r1!=0xFF); 

	xchg_spi(0xff);
		return 0;
}
//写多个扇区
BYTE MMC_SD_WriteMultiBlock(uint32_t sector,const BYTE* buffer, uint8_t count)
{
	BYTE r1;
	uint16_t i;
	SD_Enable();
	//启用ACMD23指令使能预擦除
	//r1 = MMC_SD_SendCommand(25, sector<<9);
	r1 = MMC_SD_SendCommand(25, sector);
	if(r1 != 0x00)	return r1;	
		
	do
  	{
			//放3个空数据让SD卡准备好		
			xchg_spi(0xff);
			xchg_spi(0xff);
			xchg_spi(0xff);
			xchg_spi(0xfc);		//开始令牌
			//发1个sector的数据
			for(i=0;i<512;i++)
			{
					xchg_spi(*buffer++);
			}
			     	    //发2个伪CRC
			xchg_spi(0xff);
			xchg_spi(0xff);
			do{
			r1 = xchg_spi(0xff);
			}while(r1==0xFF); 
				    //0x05表示数据写入成功
			if((r1&0x1F)!=0x05)	
			{
				SD_Disable();
				return r1;
			}
			//检测SD卡忙信号
     	    if(SD_WaitReady()==1)
     	   {
					 SD_Disable();
						return 1;
				 }
		}while(--count);	
	//发送传输结束令牌0xFD
		 xchg_spi(0xFD);			 //等待准备好   
		 if(SD_WaitReady()) {
			 SD_Disable();
				xchg_spi(0xff);
			 return 1;
		 }
		 SD_Disable();
		 xchg_spi(0xff);
		 return count;
}
//写一个扇区
BYTE MMC_SD_WriteSingleBlock(uint32_t sector,const BYTE* buffer)
{
	BYTE r1;
	uint16_t i;
	//BYTE retry=0;

	//r1 = MMC_SD_SendCommand(24, sector<<9);//写命令
	r1 = MMC_SD_SendCommand(24, sector);//写命令
	if(r1 != 0x00)
		return r1;

	xchg_spi(0xff);
	xchg_spi(0xff);
	xchg_spi(0xff);

	xchg_spi(0xfe);//发开始符

	for(i=0; i<64; i++)//送512字节数据
	{
		xchg_spi(*buffer++);
		xchg_spi(*buffer++);
		xchg_spi(*buffer++);
		xchg_spi(*buffer++);
		xchg_spi(*buffer++);
		xchg_spi(*buffer++);
		xchg_spi(*buffer++);
		xchg_spi(*buffer++);
	}

	xchg_spi(0xff);
	xchg_spi(0xff);

	r1 = xchg_spi(0xff);

	if( (r1&0x1f) != 0x05)//等待是否成功
	{
		SD_Disable();
		return r1;
	}
	//等待操作完
	while(!xchg_spi(0xff));//if(retry++ > 50){SD_Disable();return 1;}

	SD_Disable();

	return 0;
}
