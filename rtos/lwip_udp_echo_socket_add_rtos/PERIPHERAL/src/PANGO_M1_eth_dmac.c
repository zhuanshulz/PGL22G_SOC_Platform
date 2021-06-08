/*
 * *****************************************************************************************		
 * 文件名称：PANGO_M1_eth_dmac.c
 * 功能描述：DMAC固件库函数
 ******************************************************************************************
 */

#include "PANGO_M1_eth_dmac.h"
#include <string.h>

/********************************************************************
** 函数名称：DMAC_Init
** 函数功能：DMAC初始化
** 输入参数：DMAC0_TypeDef：寄存器结构体指针
** 			 ETH_Handle:ETH硬件结构体信息 
** 输出参数：无
** 返回参数：ErrorStatus：错误状态信息
********************************************************************/
ErrorStatus DMAC_Init(DMAC0_TypeDef * DMAC_x, ETH_Handle *heth)
{
	DMAC_x->CTRL = heth->dmac_ctrl;
	TS_MAC_Configure(heth->MACAddr);
	NVIC_EnableIRQ(ENT_IRQn);
	NVIC_SetPriority(ENT_IRQn, heth->priority);										
	return SUCCESS;
}

/********************************************************************
** 函数名称：SetTxDescriptor
** 函数功能：设置TX环描述符信息
** 输入参数：DMAC0_TypeDef：寄存器结构体指针
**			 num：描述符号
**			 link_num：链接符号
**			 addr：tx buffer地址
**			 size：tx buffer大小
** 输出参数：无
** 返回参数：无
********************************************************************/
void SetTxDescriptor(DMAC0_TypeDef * DMAC_x, int num, int link_num, uint32_t addr, int size)
{
	int temp_num = 0;
	int temp_link_num = 0;
	int temp_lenght = 0;
	temp_num = num << 16;
	temp_link_num = link_num << 16;
	temp_lenght = size << 16;
	
	DMAC_x->DESCRIPTOR_NUM = temp_num & 0xffff0000;
	DMAC_x->DESCRIPTOR_CTRL = DESCRIPTOR_TX_INIT | (temp_link_num & 0xffff0000);
	DMAC_x->DESCRIPTOR_TX_ADDR = addr;
	DMAC_x->DESCRIPTOR_LEN = temp_lenght & 0xffff0000;
	DMAC_x->DMAC_CTRL = DMAC0_TX_INIT;	
}

/********************************************************************
** 函数名称：SetRxDescriptor
** 函数功能：设置RX环描述符信息
** 输入参数：DMAC0_TypeDef：寄存器结构体指针
**			 num：描述符号
**			 link_num：链接符号
**			 addr：rx buffer地址
**			 size：rx buffer大小
** 输出参数：无
** 返回参数：无
********************************************************************/
void SetRxDescriptor(DMAC0_TypeDef * DMAC_x, int num, int link_num, uint32_t addr, int size)
{
	int temp_num = 0;
	int temp_link_num = 0;
	int temp_lenght = 0;
	temp_num = num;
	temp_link_num = link_num;
	temp_lenght = size;
	
	DMAC_x->DESCRIPTOR_NUM = temp_num & 0x0000ffff;
	DMAC_x->DESCRIPTOR_CTRL = DESCRIPTOR_RX_INIT | (temp_link_num & 0x0000ffff);
	DMAC_x->DESCRIPTOR_RX_ADDR = addr;
	DMAC_x->DESCRIPTOR_LEN = temp_lenght & 0x0000ffff;
	DMAC_x->DMAC_CTRL = DMAC0_RX_INIT;
}

/********************************************************************
** 函数名称：GetCurrentTxDescriptorNum
** 函数功能：获取当前可操作的TX描述符号
** 输入参数：DMAC0_TypeDef：寄存器结构体指针
** 输出参数：无
** 返回参数：uint32_t：描述符号
********************************************************************/
uint32_t GetCurrentTxDescriptorNum(DMAC0_TypeDef * DMAC_x)
{
	return DMAC_x->DMAC_TX_NUM;
}

/********************************************************************
** 函数名称：GetCurrentRxDescriptorNum
** 函数功能：获取当前可操作的RX描述符号
** 输入参数：DMAC0_TypeDef：寄存器结构体指针
** 输出参数：无
** 返回参数：uint32_t：描述符号
********************************************************************/
uint32_t GetCurrentRxDescriptorNum(DMAC0_TypeDef * DMAC_x)
{
	return DMAC_x->DMAC_RX_NUM;
}

/********************************************************************
** 函数名称：SetTxDataLen
** 函数功能：设置TX缓存区发送的实际数据长度
** 输入参数：DMAC0_TypeDef：寄存器结构体指针
**			 lenght：实际数据长度
** 输出参数：无
** 返回参数：无
********************************************************************/
void SetTxDataLen(DMAC0_TypeDef * DMAC_x, int lenght)
{
	DMAC_x->DMAC_TX_LEN = lenght;
}

/********************************************************************
** 函数名称：GetRxDataLen
** 函数功能：获取RX缓存区接收的实际数据长度
** 输入参数：DMAC0_TypeDef：寄存器结构体指针
** 输出参数：无
** 返回参数：uint32_t：实际数据长度
********************************************************************/
uint32_t GetRxDataLen(DMAC0_TypeDef * DMAC_x)
{
	return DMAC_x->DMAC_RX_LEN;
}

/********************************************************************
** 函数名称：CleanRxDescriptorNum
** 函数功能：清除提取完成的RX缓存区状态
** 输入参数：DMAC0_TypeDef：寄存器结构体指针
**			 num：描述符编号
** 输出参数：无
** 返回参数：无
********************************************************************/
void CleanRxDescriptorNum(DMAC0_TypeDef * DMAC_x, int num)
{
	DMAC_x->DMAC_CTRL = ((num << 16) & 0xffff0000) | DMAC0_RX_CTRL;
}

/********************************************************************
** 函数名称：SetDmacTxCtrl
** 函数功能：设置DMAC TX环控制位
** 输入参数：DMAC0_TypeDef：寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void SetDmacTxCtrl(DMAC0_TypeDef * DMAC_x)
{
	while(DMAC_GetRxIdleStatus(DMAC0) == 1);
	DMAC_x->DMAC_CTRL = DMAC0_TX_CTRL;
}

/********************************************************************
** 函数名称：SetDmacRxCtrl
** 函数功能：设置DMAC RX环控制位
** 输入参数：DMAC0_TypeDef：寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void SetDmacRxCtrl(DMAC0_TypeDef * DMAC_x)
{
	DMAC_x->DMAC_CTRL = DMAC0_RX_CTRL;
}

/********************************************************************
** 函数名称：DMAC_GetRxIdleStatus
** 函数功能：获取RX空闲寄存器状态
** 输入参数：DMAC0_TypeDef：寄存器结构体指针
** 输出参数：无
** 返回参数：FlagStatus：RX空闲状态检测结果
********************************************************************/
FlagStatus DMAC_GetRxIdleStatus(DMAC0_TypeDef* DMAC_x)
{
	return (FlagStatus)((DMAC_x->STATUS & DMAC0_STATUS_RX_IDLE) == DMAC0_STATUS_RX_IDLE);
}

/********************************************************************
** 函数名称：DMAC_GetTxIdleStatus
** 函数功能：获取TX空闲寄存器状态
** 输入参数：DMAC0_TypeDef：寄存器结构体指针
** 输出参数：无
** 返回参数：FlagStatus：TX空闲状态检测结果
********************************************************************/
FlagStatus DMAC_GetTxIdleStatus(DMAC0_TypeDef* DMAC_x)
{
	return (FlagStatus)((DMAC_x->STATUS & DMAC0_STATUS_TX_IDLE) == DMAC0_STATUS_TX_IDLE);
}

/********************************************************************
** 函数名称：DMAC_GetAxiIRQStatus
** 函数功能：获取AXI中断寄存器状态
** 输入参数：DMAC0_TypeDef：寄存器结构体指针
** 输出参数：无
** 返回参数：ITStatus：RX中断状态
********************************************************************/
ITStatus DMAC_GetAxiIRQStatus(DMAC0_TypeDef* DMAC_x)
{
	return (ITStatus)((DMAC_x->INTSTATUS & DMAC0_INTSTATUS_AXI_IRQ) >> DMAC0_INTSTATUS_AXI_IRQ_Pos);
}

/********************************************************************
** 函数名称：DMAC_ClearAxiIRQ
** 函数功能：清除AXI中断寄存器状态
** 输入参数：DMAC0_TypeDef：寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void DMAC_ClearAxiIRQ(DMAC0_TypeDef* DMAC_x)
{
	DMAC_x->INTCLEAR = DMAC0_INTCLEAR_AXI_IRQ;
}

/********************************************************************
** 函数名称：DMAC_GetRxIRQStatus
** 函数功能：获取RX中断寄存器状态
** 输入参数：DMAC0_TypeDef：寄存器结构体指针
** 输出参数：无
** 返回参数：ITStatus：RX中断状态
********************************************************************/
ITStatus DMAC_GetRxIRQStatus(DMAC0_TypeDef* DMAC_x)
{
	return (ITStatus)((DMAC_x->INTSTATUS & DMAC0_INTSTATUS_RXIRQ) >> DMAC0_INTSTATUS_RXIRQ_Pos);
}

/********************************************************************
** 函数名称：DMAC_SetInitStatus
** 函数功能：设置描述符初始化状态值
** 输入参数：DMAC0_TypeDef：寄存器结构体指针
**           data：配置的寄存器值
** 输出参数：无
** 返回参数：无
********************************************************************/
void DMAC_SetInitStatus(DMAC0_TypeDef* DMAC_x, uint32_t data)
{
	DMAC_x->STATUS = data;
}

/********************************************************************
** 函数名称：DMAC_ClearRxIRQ
** 函数功能：清除RX中断寄存器状态
** 输入参数：DMAC0_TypeDef：寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void DMAC_ClearRxIRQ(DMAC0_TypeDef* DMAC_x)
{
	DMAC_x->INTCLEAR = DMAC0_INTCLEAR_RXIRQ;
}

/********************************************************************
** 函数名称：TS_MAC_Configure
** 函数功能：TS_MAC配置接口函数
** 输入参数：mac：软核网卡mac地址
** 输出参数：无
** 返回参数：无
********************************************************************/
void TS_MAC_Configure(uint8_t *mac)
{
	TS_MAC_TX_RX = TS_MAC_TX_RX_DATA;
	TS_MAC_CONFIG = TS_MAC_CONFIG_DATA;
	TS_MAC_ADD_FILTER = TS_MAC_ADD_FILTER_DATA;
	TS_MAC_ADD0 = mac[5] << 24 | mac[4] << 16 | mac[3] << 8 | mac[2];
	TS_MAC_ADD1 = mac[1] << 24 | mac[0] <<16;
}
