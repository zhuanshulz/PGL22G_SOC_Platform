#ifndef PANGO_M1_ETH_DMAC_H
#define PANGO_M1_ETH_DMAC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "PANGO_M1.h"

#define DESCRIPTOR_RX_INIT   			((uint32_t)0x00008000)  /* 控制寄存器 : bit[15]         		*/
#define DESCRIPTOR_TX_INIT   			((uint32_t)0x00020000)  /* 控制寄存器 : bit[17]         		*/
#define DMAC0_RX_INIT   				((uint32_t)0x00000001)  /* 控制寄存器 : bit[0]         			*/
#define DMAC0_TX_INIT   				((uint32_t)0x00000002)  /* 控制寄存器 : bit[1]         			*/
#define DMAC0_RX_CTRL   				((uint32_t)0x00000004)  /* 控制寄存器 : bit[2]         			*/
#define DMAC0_TX_CTRL   				((uint32_t)0x00000008)  /* 控制寄存器 : bit[3]         			*/
#define DMAC0_RXIRQ_ENABLE   			((uint32_t)0x00000001)  /* 中断控制寄存器: 使能接收中断 		*/
#define DMAC0_RXIRQ_DISABLE   			((uint32_t)0x00000000)  /* 中断控制寄存器: 失能接收中断 		*/
#define DMAC0_STATUS_RX_IDLE			((uint32_t)0x00000001)  /* 接收空闲状态寄存器: 获取RX IDLE状态寄存器bit[0]  */
#define DMAC0_STATUS_TX_IDLE			((uint32_t)0x00000002)  /* 发送空闲状态寄存器: 获取TX IDLE状态寄存器bit[1]  */
#define DMAC0_STATUS_INIT_DONE			((uint32_t)0x00000004)  /* 初始化完成状态寄存器bit[2]  */
#define DMAC0_INTSTATUS_AXI_IRQ 		((uint32_t)0x00000001)  /* 中断状态寄存器: 获取AXI中断状态寄存器  	*/
#define DMAC0_INTCLEAR_AXI_IRQ  		((uint32_t)0x00000001)  /* 中断状态寄存器: 清除AXI中断状态寄存器   */
#define DMAC0_INTSTATUS_RXIRQ   		((uint32_t)0x00000002)  /* 中断状态寄存器: 获取RX中断状态寄存器  	*/
#define DMAC0_INTCLEAR_RXIRQ    		((uint32_t)0x00000002)  /* 中断状态寄存器: 清除RX中断状态寄存器   */

#define DMAC0_INTSTATUS_AXI_IRQ_Pos    	0  						/* 中断状态寄存器: AXI_IRQ Position  */
#define DMAC0_INTSTATUS_RXIRQ_Pos    	1  						/* 中断状态寄存器: RXIRQ Position  */

#define TS_MAC_TX_RX					(*(__O uint32_t*)(APB1PERIPH_BASE + 0xC000))	/* TS_MAC收发控制寄存器地址   */
#define TS_MAC_CONFIG					(*(__O uint32_t*)(APB1PERIPH_BASE + 0xC010))	/* TS_MAC配置寄存器地址   */
#define TS_MAC_ADD_FILTER				(*(__O uint32_t*)(APB1PERIPH_BASE + 0xC120))	/* TS_MAC地址过滤寄存器地址   */
#define TS_MAC_ADD0						(*(__O uint32_t*)(APB1PERIPH_BASE + 0xC130))	/* TS_MAC MAC地址0寄存器地址   */
#define TS_MAC_ADD1						(*(__O uint32_t*)(APB1PERIPH_BASE + 0xC140))	/* TS_MAC MAC地址1寄存器地址   */

#define TS_MAC_TX_RX_DATA				((uint32_t)0x00000035)	/* TS_MAC收发控制寄存器值   */
#define TS_MAC_CONFIG_DATA				((uint32_t)0x00007217)	/* TS_MAC配置寄存器值   */
#define TS_MAC_ADD_FILTER_DATA			((uint32_t)0x00000480)	/* TS_MAC地址过滤寄存器值   */

typedef struct _ETH_Handle_										/* ETH硬件结构体信息 */
{
	uint32_t dmac_ctrl;											/* dmac控制信号 */
	uint32_t priority;											/* dmac中断优先级 */
	uint32_t AutoNegotiation;           						/* 自协商模式选择 */
	uint32_t Speed;                     						/* 网口速度配置10/100/1000M */
	uint32_t DuplexMode;                						/* 工作模式选择：全双工/半双工 */
	uint16_t PhyAddress;                						/* RHY地址：0-32 */
	uint8_t  MACAddr[6];                   						/* 本机MAC地址（6个字节） */
	uint32_t ChecksumMode;              						/* 校验和选择：是否打开硬件校验和 */
	uint32_t MediaInterface;               						/* 硬件接口选择：MII/GMII 或者RGMII */
}ETH_Handle;


extern ErrorStatus DMAC_Init(DMAC0_TypeDef * DMAC_x, ETH_Handle *heth);
extern void SetTxDescriptor(DMAC0_TypeDef * DMAC_x, int num, int link_num, uint32_t addr, int size);
extern void SetRxDescriptor(DMAC0_TypeDef * DMAC_x, int num, int link_num, uint32_t addr, int size);
extern uint32_t	GetCurrentTxDescriptorNum(DMAC0_TypeDef * DMAC_x);
extern uint32_t	GetCurrentRxDescriptorNum(DMAC0_TypeDef * DMAC_x);
extern void	SetTxDataLen(DMAC0_TypeDef * DMAC_x, int lenght);
extern uint32_t	GetRxDataLen(DMAC0_TypeDef * DMAC_x);
extern void	CleanRxDescriptorNum(DMAC0_TypeDef * DMAC_x, int num);
extern void	SetDmacTxCtrl(DMAC0_TypeDef * DMAC_x);
extern void	SetDmacRxCtrl(DMAC0_TypeDef * DMAC_x);
extern FlagStatus DMAC_GetRxIdleStatus(DMAC0_TypeDef* DMAC_x);
extern FlagStatus DMAC_GetTxIdleStatus(DMAC0_TypeDef* DMAC_x);
extern ITStatus DMAC_GetAxiIRQStatus(DMAC0_TypeDef* DMAC_x);
extern void DMAC_ClearAxiIRQ(DMAC0_TypeDef* DMAC_x);
extern ITStatus DMAC_GetRxIRQStatus(DMAC0_TypeDef* DMAC_x);
extern void DMAC_SetInitStatus(DMAC0_TypeDef* DMAC_x, uint32_t data);
extern void DMAC_ClearRxIRQ(DMAC0_TypeDef* DMAC_x);
extern void TS_MAC_Configure(uint8_t *mac);
#ifdef __cplusplus
}
#endif

#endif  /* PANGO_M1_ETH_DMAC_H */


