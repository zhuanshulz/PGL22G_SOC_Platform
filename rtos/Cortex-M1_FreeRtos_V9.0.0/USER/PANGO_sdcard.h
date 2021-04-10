#include<stdint.h>
#include<integer.h>
#include "PANGO_M1.h"
#include "ff.h"
typedef unsigned int	UINT;	/* int must be 16-bit or 32-bit */
typedef unsigned char	BYTE;	/* char must be 8-bit */
typedef uint16_t		WORD;	/* 16-bit unsigned integer */
//typedef uint32_t		DWORD;	/* 32-bit unsigned integer */
typedef uint64_t		QWORD;	/* 64-bit unsigned integer */
typedef WORD			WCHAR;	/* UTF-16 character type */

		/*
		*************************************************************

				用户API函数:	读, 写, 擦 SD卡  API函数及错误码
 			
		*************************************************************
		*/
		
/* 错误码 error code */
#define   SD_NO_ERR			     	0x00			// 函数执行成功
#define   SD_ERR_NO_CARD		 	0x01			// SD卡没有完全插入到卡座中
#define   SD_ERR_USER_PARAM      	0x02			// 用户使用API函数时，入口参数有错误
#define   SD_ERR_CARD_PARAM		 	0x03			// 卡中参数有错误（与本模块不兼容）
#define	  SD_ERR_VOL_NOTSUSP        0x04			// 卡不支持3.3V供电
#define   SD_ERR_OVER_CARDRANGE		0x05			// 操作超出卡容量范围

/* SD命令可能返回的错误码 */
#define   SD_ERR_CMD_RESPTYPE	 	0x10			// 命令类型错误
#define   SD_ERR_CMD_TIMEOUT     	0x11			// SD命令响应超时
#define   SD_ERR_CMD_RESP		 	0x12			// SD命令响应错误
			
/* 数据流错误码 */
#define   SD_ERR_DATA_CRC16      	0x20			// 数据流CRC16校验不通过
#define   SD_ERR_DATA_START_TOK		0x21			// 读单块或多块时，数据开始令牌不正确
#define	  SD_ERR_DATA_RESP		 	0x22			// 写单块或多块时，SD卡数据响应令牌不正确

/* 等待错误码 */
#define   SD_ERR_TIMEOUT_WAIT    	0x30			// 写或擦操作时，发生超时错误
#define   SD_ERR_TIMEOUT_READ    	0x31			// 读操作超时错误
#define	  SD_ERR_TIMEOUT_WRITE	 	0x32			// 写操作超时错误
#define   SD_ERR_TIMEOUT_ERASE   	0x33			// 擦除操作超时错误
#define	  SD_ERR_TIMEOUT_WAITIDLE 	0x34			// 初始化SD卡时，等待SD卡进入空闲状态超时错误

/* 写操作可能返回的错误码 */
#define	  SD_ERR_WRITE_BLK			0x40			// 写块数据错误
#define	  SD_ERR_WRITE_BLKNUMS      0x41			// 写多块时，想要写入的块与正确写入的块数不一致
#define   SD_ERR_WRITE_PROTECT		0x42			// 卡外壳的写保护开关打在写保护位置

/* Status of Disk Functions */
typedef BYTE	DSTATUS;
/* Results of Disk Functions */
//typedef enum {
//	RES_OK = 0,		/* 0: Successful */
//	RES_ERROR,		/* 1: R/W Error */
//	RES_WRPRT,		/* 2: Write Protected */
//	RES_NOTRDY,		/* 3: Not Ready */
//	RES_PARERR		/* 4: Invalid Parameter */
//} DRESULT;


#define INITOK (uint32_t_t)1
//	STATUS <= STATUS&{18'h3ffff,
//				1'b1,						//write_end
//				1'b1,						//read_end
//				1'b0,						//write_busy
//				1'b0,						//read_busy
//				1'b1,						//write_start
//				1'b1,						//read_start
//				3'd0,						//reserved
//		 		sd_card_state};				// 5 bits
#define NOT_BUSY 3072
#define WRITE_NOT_BUSY 2048
#define READ_NOT_BUSY 1024
#define WRITE_START 512
#define READ_START 256
void SPI_Low(void);
void SPI_High(void);
//写读一个字节			//read and write one byte
 BYTE xchg_spi (BYTE);
void SD_Disable(void);
 void SD_Enable(void);
void Delay_s(__IO uint32_t);
void MMC_SD_Init(void);
uint8_t MMC_SD_Reset(void);

//sd卡写命令
 BYTE MMC_SD_SendCommand(BYTE, DWORD);
uint8_t MMC_SD_ReadSingleBlock(uint32_t , uint8_t* );
uint8_t MMC_SD_WriteSingleBlock(uint32_t , const uint8_t* );
BYTE MMC_SD_WriteMultiBlock(uint32_t ,const BYTE* , uint8_t );
BYTE MMC_SD_ReadMultiBlock(uint32_t , BYTE* , uint8_t );
