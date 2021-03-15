#ifndef PANGO_M1_I2C_H
#define PANGO_M1_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "PANGO_M1.h"

#define I2C_CTR_EN     ((uint32_t)0x00000080)  /* ���ƼĴ��� : ʹ��IIC Core bit[7]    	*/
#define I2C_CTR_IEN    ((uint32_t)0x00000040)
#define I2C_CTR_PERE   ((uint32_t)0x0000FFFF)  /* ��Ƶ�Ĵ��� : ��Ƶֵbit[15:0]        	*/
#define I2C_CMD_IACK   ((uint32_t)0x00000001)  /* ����Ĵ��� : �ж�Ӧ��bit[0]         	*/
#define I2C_CMD_ACK    ((uint32_t)0x00000008)  /* ����Ĵ��� : Ӧ��bit[3]             	*/
#define I2C_CMD_WR     ((uint32_t)0x00000010)  /* ����Ĵ��� : д���ݵ����豸bit[4]   	*/
#define I2C_CMD_RD     ((uint32_t)0x00000020)  /* ����Ĵ��� : �����豸����bit[5]     	*/
#define I2C_CMD_STO    ((uint32_t)0x00000040)  /* ����Ĵ��� : �������bit[6]         	*/
#define I2C_CMD_STA    ((uint32_t)0x00000080)  /* ����Ĵ��� : ��ʼ����bit[7]         	*/
#define I2C_SR_TIP     ((uint32_t)0x00000002)  /* ״̬�Ĵ��� : ���ݴ���״̬��־bit[1] 	*/
#define I2C_SR_AL      ((uint32_t)0x00000020)  /* ״̬�Ĵ��� : �ٲö�ʧbit[5]         	*/
#define I2C_SR_BUSY    ((uint32_t)0x00000040)  /* ״̬�Ĵ��� : I2Cæ״̬bit[6]        	*/
#define I2C_SR_RXACK   ((uint32_t)0x00000080)  /* ״̬�Ĵ��� : ���մ��豸��Ӧ�ź�bit[7] */

extern ErrorStatus I2C_Init(I2C_TypeDef * I2Cx, uint16_t speed, uint8_t irq_en);
extern void I2C_SendByte(I2C_TypeDef *i2c ,uint8_t slv_data,uint8_t data_address,uint8_t data);
extern void I2C_SendBytes(I2C_TypeDef *i2c ,uint8_t slv_address,uint8_t data_start_address,uint8_t *data,int32_t data_num);
extern void I2C_ReadBytes(I2C_TypeDef *i2c ,uint8_t slv_address,uint8_t data_start_address,uint8_t *data,int32_t data_num);
extern uint8_t I2C_ReceiveByte(I2C_TypeDef *i2c ,uint8_t slv_address,uint8_t mem_addr);
extern void Delay_ms_i2c(__IO uint32_t delay_ms);
extern uint16_t I2C_Rate_Set(I2C_TypeDef * I2Cx,uint16_t Rate);
extern void I2C_Enable(I2C_TypeDef * I2Cx);
extern void I2C_UnEnable(I2C_TypeDef * I2Cx);
extern void I2C_InterruptOpen(I2C_TypeDef * I2Cx);
extern void I2C_InterruptClose(I2C_TypeDef * I2Cx);

#ifdef __cplusplus
}
#endif

#endif /* PANGO_M1_I2C_H */
