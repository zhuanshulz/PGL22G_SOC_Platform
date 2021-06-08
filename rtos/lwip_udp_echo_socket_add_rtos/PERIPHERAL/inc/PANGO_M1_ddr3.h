#ifndef PANGO_M1_DDR_H
#define PANGO_M1_DDR_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "PANGO_M1.h"

/* 状态寄存器bit定义 */
#define DDR_STATUS_DONE             ((uint32_t) 0x00000001)    	/* 初始化完成状态 */
#define DDR_STATUS_WRITE            ((uint32_t) 0x00000002)    	/* 写结束状态 */
#define DDR_STATUS_READ             ((uint32_t) 0x00000004)    	/* 读结束状态 */
	 
/* 命令状态奇bit定义 */	 
#define DDR_WRITE_CMD               ((uint32_t) 0x00000001)    	/* 写命令  */
#define DDR_READ_CMD                ((uint32_t) 0x00000002)    	/* 读命令 */

/* 突发长度 */
#define BURST_LEN_1                ((uint32_t) 0x00000001)    	/* 突发长度1  */
#define BURST_LEN_2                ((uint32_t) 0x00000002)    	/* 突发长度2  */
#define BURST_LEN_3                ((uint32_t) 0x00000003)    	/* 突发长度3  */
#define BURST_LEN_4                ((uint32_t) 0x00000004)    	/* 突发长度4  */
#define BURST_LEN_5                ((uint32_t) 0x00000005)    	/* 突发长度5  */
#define BURST_LEN_6                ((uint32_t) 0x00000006)    	/* 突发长度6  */
#define BURST_LEN_7                ((uint32_t) 0x00000007)    	/* 突发长度7  */
#define BURST_LEN_8                ((uint32_t) 0x00000008)   	/* 突发长度8  */

typedef struct
{
  uint32_t Read_Outburst_Len;         							/* 读数据突发长度 */
  uint32_t Write_Outburst_Len;         							/* 写数据突发长度 */
}DDR_InitTypeDef;

extern void DDR_Init(DDR_InitTypeDef* DDR_InitStruct);
extern void DDR_Set_Read_Addr(uint32_t address);
extern FlagStatus DDR_GetInitDoneStatus(void);
extern FlagStatus DDR_GetWriteStatus(void);
extern FlagStatus DDR_GetReadStatus(void);
extern void DDR_Write_Command(void);
extern void DDR_Read_Command(void);

#ifdef __cplusplus
}
#endif

#endif  /* PANGO_M1_DDR_H */ 

