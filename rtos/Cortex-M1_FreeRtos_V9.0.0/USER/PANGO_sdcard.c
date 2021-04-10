#include "PANGO_sdcard.h"
#include "PANGO_M1.h"

//�ȴ�SD������ĳЩ�����ļ��������������������Ϊ�ȴ���ʱ��
//���ٵ�Ƭ������STM32�����Խ������ֵ�ʵ�����
#define WAIT_COUNT 10
/* SD�����ʱʱ��(��λ 8clock)*/
/* timeout of command */
#define SD_CMD_TIMEOUT   	 	100
//��ʼ����ɺ�ɻ��SD�������ͣ�������������ʹ��
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

/*SPI����ģʽ������400KHZ*/
void SPI_Low(void)
{
	SDCARD->clk_div = (uint32_t)498;	//low speed;
}

/*SPI����ģʽ����������25MHZ*/
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

void SD_Disable()//��SD��
{
	SDCARD->cs_control=0x00000000;
}
 void SD_Enable()//��Ƭѡ
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
	while((r1 = xchg_spi(0xff)) == 0xff)//�ȴ���Ӧ��
	{
		Delay_s(10);
		if(retry++ > 20) break;//��ʱ�˳�
	}
	return r1;//����״ֵ̬
}
void MMC_SD_Init(void){
	SD_Enable();
	FCLK_SLOW();
	SD_Disable();
}

//sd����λ
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
		r1 = MMC_SD_SendCommand(0, 0);//��idle����
		retry++;
		if(retry>10) return 1;//��ʱ�˳�
	} while(r1 != 0x01);
	retry = 0;
	do
	{
		r1 = MMC_SD_SendCommand(8, 0x1aa);//��active����
		Delay_s(10);
		retry++;
		//if(retry>100) return 1;//��ʱ�˳�
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
		r1 = MMC_SD_SendCommand(55, 0);//������ʼ��ָ��CMD55+ACMD41
		if(r1!=0x01)return r1;
		Delay_s(10);
		r1 = MMC_SD_SendCommand(41, 0x40000000);//������ʼ��ָ��CMD55+ACMD41
		Delay_s(10);
		if(retry>100) return r1;//��ʱ�˳�
	} while(r1!=0);
	//��ʼ��ָ�����ɣ���������ȡOCR��Ϣ
	//-----------����SD2.0���汾��ʼ-----------
	r1 = MMC_SD_SendCommand(CMD58, 0);
	if(r1!=0x00)return r1; //�������û�з�����ȷӦ��ֱ���˳�������Ӧ��
	//��OCRָ����󣬽�������4�ֽڵ�OCR��Ϣ
	xchg_spi(0xFF);
	xchg_spi(0xFF);
	xchg_spi(0xFF);
	xchg_spi(0xFF);
	//OCR������ɣ�Ƭѡ�ø�
	SD_Disable();
	xchg_spi(0xFF);
//	r1 = MMC_SD_SendCommand(59, 0);//��crc

	r1 = MMC_SD_SendCommand(16, 512);//��������С512
	SPI_High();
	return 0;//��������
}
BYTE MMC_SD_GetCID(BYTE *cid_data)
{
	 uint8_t r1;
	//��CMD10�����ȡCID��Ϣ
	SD_Enable();
   r1 = MMC_SD_SendCommand(10, 0);
   if(r1 != 0x00)	
   return r1;  	//��Ӧ�����˳� 
   //����16���ֽڵ�����
	 uint16_t i;
	 while(xchg_spi(0xff) != 0xfe);//if(retry++ > 50){SD_Disable();return 1;}
    for(i=0;i<16;i++)	 //������д�뵽���ݻ�������
    {
        *(cid_data++)=xchg_spi(0xff);
		}
	 SD_Disable();
	 xchg_spi(0xff);
   return 0;
}
//��һ������
BYTE MMC_SD_ReadSingleBlock(uint32_t sector, BYTE* buffer)
{
	BYTE r1;
	uint16_t i;
	//BYTE retry=0;
	SD_Enable();
	r1 = MMC_SD_SendCommand(17, sector<<9);//������

	if(r1 != 0x00)
		return r1;

	//�����ݵĿ�ʼ
	while(xchg_spi(0xff) != 0xfe);//if(retry++ > 50){SD_Disable();return 1;}

    for(i=0;i<64;i++)	 //������д�뵽���ݻ�������
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
	xchg_spi(0xff);//αcrc
	xchg_spi(0xff);

	SD_Disable();

	return 0;
}
//���������
BYTE MMC_SD_ReadMultiBlock(uint32_t sector, BYTE* buffer, uint8_t count)
{
	BYTE r1;
	uint16_t i;
	//BYTE retry=0;
	SD_Enable();
	r1 = MMC_SD_SendCommand(18, sector<<9);//������
	if(r1 != 0x00)	return r1;	 

  do	//��ʼ�������� 
  {
		//�����ݵĿ�ʼ
		while(xchg_spi(0xff) != 0xfe);//if(retry++ > 50){SD_Disable();return 1;}
		for(i=0;i<512;i++)	 //������д�뵽���ݻ�������
    {
        *(buffer++)=xchg_spi(0xff);
		}
	}while(--count);	
	r1 = MMC_SD_SendCommand(12, 0);//ȫ��������ɣ�����ֹͣ����
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
//д�������
BYTE MMC_SD_WriteMultiBlock(uint32_t sector,const BYTE* buffer, uint8_t count)
{
	BYTE r1;
	uint16_t i;
	SD_Enable();
	//����ACMD23ָ��ʹ��Ԥ����
	r1 = MMC_SD_SendCommand(25, sector<<9);
	
	if(r1 != 0x00)	return r1;	
		
	do
  	{
			//��3����������SD��׼����		
			xchg_spi(0xff);
			xchg_spi(0xff);
			xchg_spi(0xff);
			xchg_spi(0xfc);		//��ʼ����
			//��1��sector������
			for(i=0;i<512;i++)
			{
					xchg_spi(*buffer++);
			}
			     	    //��2��αCRC
			xchg_spi(0xff);
			xchg_spi(0xff);
			do{
			r1 = xchg_spi(0xff);
			}while(r1==0xFF); 
				    //0x05��ʾ����д��ɹ�
			if((r1&0x1F)!=0x05)	
			{
				SD_Disable();
				return r1;
			}
			//���SD��æ�ź�
     	    if(SD_WaitReady()==1)
     	   {
					 SD_Disable();
						return 1;
				 }
		}while(--count);	
	//���ʹ����������0xFD
		 xchg_spi(0xFD);			 //�ȴ�׼����   
		 if(SD_WaitReady()) {
			 SD_Disable();
				xchg_spi(0xff);
			 return 1;
		 }
		 SD_Disable();
		 xchg_spi(0xff);
		 return count;
}
//дһ������
BYTE MMC_SD_WriteSingleBlock(uint32_t sector,const BYTE* buffer)
{
	BYTE r1;
	uint16_t i;
	//BYTE retry=0;

	r1 = MMC_SD_SendCommand(24, sector<<9);//д����
	if(r1 != 0x00)
		return r1;

	xchg_spi(0xff);
	xchg_spi(0xff);
	xchg_spi(0xff);

	xchg_spi(0xfe);//����ʼ��

	for(i=0; i<64; i++)//��512�ֽ�����
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

	if( (r1&0x1f) != 0x05)//�ȴ��Ƿ�ɹ�
	{
		SD_Disable();
		return r1;
	}
	//�ȴ�������
	while(!xchg_spi(0xff));//if(retry++ > 50){SD_Disable();return 1;}

	SD_Disable();

	return 0;
}
