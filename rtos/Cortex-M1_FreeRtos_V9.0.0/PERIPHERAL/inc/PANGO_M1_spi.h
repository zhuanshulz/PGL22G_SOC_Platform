#ifndef PANGO_M1_SPI_H
#define PANGO_M1_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "PANGO_M1.h"

/* 控制寄存器位定义 */
#define SPI_CR_DIRECTION           ((uint32_t) 0x00000001)    /* 方向（大小端模式）     */
#define SPI_CR_PHASE               ((uint32_t) 0x00000002)    /* 相位                  	*/
#define SPI_CR_POLARITY            ((uint32_t) 0x00000004)    /* 极性               	*/
#define SPI_CR_CLKSEL              ((uint32_t) 0x00000018)    /* 分频时钟               */
#define SPI_CR_CS             	   ((uint32_t) 0x0000ff00)    /* 片选1-8                */

/* 状态寄存器位定义 */
#define SPI_STATUS_ROE             ((uint32_t) 0x00000004)    /* 接收溢出错误  			*/
#define SPI_STATUS_TOE             ((uint32_t) 0x00000008)    /* 传输溢出错误 			*/
#define SPI_STATUS_TMT             ((uint32_t) 0x00000010)    /* 正在传输           	*/
#define SPI_STATUS_TRDY            ((uint32_t) 0x00000020)    /* 准备传输         		*/
#define SPI_STATUS_RRDY            ((uint32_t) 0x00000040)    /* 接收准备          		*/
#define SPI_STATUS_RCV             ((uint32_t) 0x00000080)    /* 正在接收              	*/

typedef struct
{
  FunctionalState DIRECTION;  /* @arg: ENABLE MSB first transmission;
                                 @arg: DISABLE LSB first transmission;
                               */
  FunctionalState PHASE;      /* @arg: ENABLE Posedge transmit data;
                                 @arg: DISABLE Negedge transmit data;
                               */
  FunctionalState POLARITY;   /* @arg: ENABLE Initial polarity to 1
                                 @arg: DISABLE Initial polarity to 0;
                               */
  uint32_t CLKSEL;            /* Clock Selection */
  
}SPI_InitTypeDef;

/* 时钟分频系数 */
#define CLKSEL_CLK_DIV_4   	((uint32_t) 0x00000000)  //CLK/4
#define CLKSEL_CLK_DIV_8   	((uint32_t) 0x00000001)  //CLK/8
#define CLKSEL_CLK_DIV_16  	((uint32_t) 0x00000002)  //CLK/16
#define CLKSEL_CLK_DIV_32  	((uint32_t) 0x00000003)  //CLK/32

/* 片选系数 */
#define SPI_CS_SEL_1   		((uint32_t) 0x00000100)  //CS0
#define SPI_CS_SEL_2   		((uint32_t) 0x00000200)  //CS2
#define SPI_CS_SEL_3   		((uint32_t) 0x00000400)  //CS3
#define SPI_CS_SEL_4   		((uint32_t) 0x00000800)  //CS4
#define SPI_CS_SEL_5   		((uint32_t) 0x00001000)  //CS5
#define SPI_CS_SEL_6   		((uint32_t) 0x00002000)  //CS6
#define SPI_CS_SEL_7   		((uint32_t) 0x00004000)  //CS7
#define SPI_CS_SEL_8   		((uint32_t) 0x00008000)  //CS8

#define SPI_CR_DIRECTION_Pos   0   /* CTRL register DIRECTION bit position */
#define SPI_CR_PHASE_Pos       1   /* CTRL register PHASE bit position     */
#define SPI_CR_POLARITY_Pos    2   /* CTRL register POLARITY bit position  */
#define SPI_CR_CS_Pos    	   8   /* CTRL register CS bit position  */
#define SPI_STATUS_ROE_Pos     2   /* STATUS register ROE bit position     */
#define SPI_STATUS_TOE_Pos     3   /* STATUS register TOE bit position     */
#define SPI_STATUS_TMT_Pos     4   /* STATUS register TMT bit position     */
#define SPI_STATUS_TRDY_Pos    5   /* STATUS register TRDY bit position    */
#define SPI_STATUS_RRDY_Pos    6   /* STATUS register RRDY bit position    */
#define SPI_STATUS_RCV_Pos     7   /* STATUS register RCV bit position     */

#define SPI_CR_CLKSEL_Pos     ((uint32_t) 0x00000003)    /* CTRL register CLKSEL Position */
#define SPI_CR_CLKSEL_Mask    ((uint32_t) 0x00000003)    /* CTRL register CLKSEL mask     */

extern void SPI_Init(SPI_InitTypeDef* SPI_InitStruct);
extern void SPI_SetDirection(void);
extern void SPI_ClrDirection(void);
extern uint32_t SPI_GetDirection(void);
extern void SPI_SetPhase(void);
extern void SPI_ClrPhase(void);
extern uint32_t SPI_GetPhase(void);
extern uint32_t SPI_GetPolarity(void);
extern void SPI_ClrPolarity(void);
extern void SPI_SetPolarity(void);
extern void SPI_SetClkSel(uint32_t clksel);
extern uint32_t SPI_GetClkSel(void);
extern FlagStatus SPI_GetToeStatus(void);
extern FlagStatus SPI_GetRoeStatus(void);
extern FlagStatus SPI_GetTmtStatus(void);
extern FlagStatus SPI_GetTrdyStatus(void);
extern FlagStatus SPI_GetRrdyStatus(void);
extern FlagStatus SPI_GetRcvStatus(void);
extern void SPI_SetRcvStatus(void);
extern void SPI_ClrToeStatus(void);
extern void SPI_ClrRoeStatus(void);
extern void SPI_ClrErrStatus(void);
extern void SPI_WriteData(uint8_t data);
extern uint8_t SPI_ReadData(void);
extern  void SPI_Select_Slave(uint32_t Slave_address);
extern  void SPI_CS_Enable(uint32_t cs);
extern  void SPI_CS_Disable(void);

#ifdef __cplusplus
}
#endif

#endif /* PANGO_M1_SPI_H */ 

