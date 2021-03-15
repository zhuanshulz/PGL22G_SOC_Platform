#ifndef PANGO_M1_DDR_H
#define PANGO_M1_DDR_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "PANGO_M1.h"

/* ״̬�Ĵ���bit���� */
#define DDR_STATUS_DONE             ((uint32_t) 0x00000001)    	/* ��ʼ�����״̬ */
#define DDR_STATUS_WRITE            ((uint32_t) 0x00000002)    	/* д����״̬ */
#define DDR_STATUS_READ             ((uint32_t) 0x00000004)    	/* ������״̬ */
	 
/* ����״̬��bit���� */	 
#define DDR_WRITE_CMD               ((uint32_t) 0x00000001)    	/* д����  */
#define DDR_READ_CMD                ((uint32_t) 0x00000002)    	/* ������ */

/* ͻ������ */
#define BURST_LEN_1                ((uint32_t) 0x00000001)    	/* ͻ������1  */
#define BURST_LEN_2                ((uint32_t) 0x00000002)    	/* ͻ������2  */
#define BURST_LEN_3                ((uint32_t) 0x00000003)    	/* ͻ������3  */
#define BURST_LEN_4                ((uint32_t) 0x00000004)    	/* ͻ������4  */
#define BURST_LEN_5                ((uint32_t) 0x00000005)    	/* ͻ������5  */
#define BURST_LEN_6                ((uint32_t) 0x00000006)    	/* ͻ������6  */
#define BURST_LEN_7                ((uint32_t) 0x00000007)    	/* ͻ������7  */
#define BURST_LEN_8                ((uint32_t) 0x00000008)   	/* ͻ������8  */

typedef struct
{
  uint32_t Read_Outburst_Len;         							/* ������ͻ������ */
  uint32_t Write_Outburst_Len;         							/* д����ͻ������ */
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

