/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "PANGO_sdcard.h"
/* Definitions of physical drive number for each drive */
#define SD_CARD		0	/* Example: Map Ramdisk to physical drive 0 */
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
/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS Stat = STA_NOINIT;
	if (pdrv) Stat =  STA_NOINIT;		/* Supports only drive 0 */
	else Stat = 0;
	return Stat;	/* Return disk status */
}




/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	if (pdrv) return STA_NOINIT;			/* Supports only drive 0 */
	MMC_SD_Init();
	stat = MMC_SD_Reset();
	if(stat!=0)
			stat = RES_ERROR;
	return stat;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;

	if (pdrv) res =  RES_ERROR;			/* Supports only drive 0 */
	else {
		res = MMC_SD_ReadMultiBlock(sector,buff,count);
	}
	return res;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;

	if (pdrv) res =  RES_ERROR;			/* Supports only drive 0 */
	else {
		res = MMC_SD_WriteMultiBlock(sector,buff,count);
	}
	return res;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	if (pdrv) res =  RES_ERROR;			/* Supports only drive 0 */
	else {
			switch(cmd)
			{
				//返回扇区个数
				case GET_SECTOR_COUNT:
						*(DWORD *)buff = 2048; //1GB，即16777216字节
						res = RES_OK;
				break;
				//返回扇区大小
				case GET_SECTOR_SIZE:
						*(WORD *)buff = 512 ;
				res = RES_OK;
				break;
				//返回擦除扇区的最小个数
				case GET_BLOCK_SIZE:
						*(WORD *)buff = 1 ;   //每次擦除一个扇区
					res = RES_OK;
				break;
				default:
					res = RES_OK;
			}
		         //由此看出，此处的数据返回值不是通过return返回的，如之前的讲解是通过指针返回
		return res;
	}
	return RES_PARERR;
}

