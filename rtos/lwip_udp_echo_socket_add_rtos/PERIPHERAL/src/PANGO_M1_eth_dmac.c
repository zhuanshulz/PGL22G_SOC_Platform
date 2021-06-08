/*
 * *****************************************************************************************		
 * �ļ����ƣ�PANGO_M1_eth_dmac.c
 * ����������DMAC�̼��⺯��
 ******************************************************************************************
 */

#include "PANGO_M1_eth_dmac.h"
#include <string.h>

/********************************************************************
** �������ƣ�DMAC_Init
** �������ܣ�DMAC��ʼ��
** ���������DMAC0_TypeDef���Ĵ����ṹ��ָ��
** 			 ETH_Handle:ETHӲ���ṹ����Ϣ 
** �����������
** ���ز�����ErrorStatus������״̬��Ϣ
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
** �������ƣ�SetTxDescriptor
** �������ܣ�����TX����������Ϣ
** ���������DMAC0_TypeDef���Ĵ����ṹ��ָ��
**			 num����������
**			 link_num�����ӷ���
**			 addr��tx buffer��ַ
**			 size��tx buffer��С
** �����������
** ���ز�������
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
** �������ƣ�SetRxDescriptor
** �������ܣ�����RX����������Ϣ
** ���������DMAC0_TypeDef���Ĵ����ṹ��ָ��
**			 num����������
**			 link_num�����ӷ���
**			 addr��rx buffer��ַ
**			 size��rx buffer��С
** �����������
** ���ز�������
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
** �������ƣ�GetCurrentTxDescriptorNum
** �������ܣ���ȡ��ǰ�ɲ�����TX��������
** ���������DMAC0_TypeDef���Ĵ����ṹ��ָ��
** �����������
** ���ز�����uint32_t����������
********************************************************************/
uint32_t GetCurrentTxDescriptorNum(DMAC0_TypeDef * DMAC_x)
{
	return DMAC_x->DMAC_TX_NUM;
}

/********************************************************************
** �������ƣ�GetCurrentRxDescriptorNum
** �������ܣ���ȡ��ǰ�ɲ�����RX��������
** ���������DMAC0_TypeDef���Ĵ����ṹ��ָ��
** �����������
** ���ز�����uint32_t����������
********************************************************************/
uint32_t GetCurrentRxDescriptorNum(DMAC0_TypeDef * DMAC_x)
{
	return DMAC_x->DMAC_RX_NUM;
}

/********************************************************************
** �������ƣ�SetTxDataLen
** �������ܣ�����TX���������͵�ʵ�����ݳ���
** ���������DMAC0_TypeDef���Ĵ����ṹ��ָ��
**			 lenght��ʵ�����ݳ���
** �����������
** ���ز�������
********************************************************************/
void SetTxDataLen(DMAC0_TypeDef * DMAC_x, int lenght)
{
	DMAC_x->DMAC_TX_LEN = lenght;
}

/********************************************************************
** �������ƣ�GetRxDataLen
** �������ܣ���ȡRX���������յ�ʵ�����ݳ���
** ���������DMAC0_TypeDef���Ĵ����ṹ��ָ��
** �����������
** ���ز�����uint32_t��ʵ�����ݳ���
********************************************************************/
uint32_t GetRxDataLen(DMAC0_TypeDef * DMAC_x)
{
	return DMAC_x->DMAC_RX_LEN;
}

/********************************************************************
** �������ƣ�CleanRxDescriptorNum
** �������ܣ������ȡ��ɵ�RX������״̬
** ���������DMAC0_TypeDef���Ĵ����ṹ��ָ��
**			 num�����������
** �����������
** ���ز�������
********************************************************************/
void CleanRxDescriptorNum(DMAC0_TypeDef * DMAC_x, int num)
{
	DMAC_x->DMAC_CTRL = ((num << 16) & 0xffff0000) | DMAC0_RX_CTRL;
}

/********************************************************************
** �������ƣ�SetDmacTxCtrl
** �������ܣ�����DMAC TX������λ
** ���������DMAC0_TypeDef���Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void SetDmacTxCtrl(DMAC0_TypeDef * DMAC_x)
{
	while(DMAC_GetRxIdleStatus(DMAC0) == 1);
	DMAC_x->DMAC_CTRL = DMAC0_TX_CTRL;
}

/********************************************************************
** �������ƣ�SetDmacRxCtrl
** �������ܣ�����DMAC RX������λ
** ���������DMAC0_TypeDef���Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void SetDmacRxCtrl(DMAC0_TypeDef * DMAC_x)
{
	DMAC_x->DMAC_CTRL = DMAC0_RX_CTRL;
}

/********************************************************************
** �������ƣ�DMAC_GetRxIdleStatus
** �������ܣ���ȡRX���мĴ���״̬
** ���������DMAC0_TypeDef���Ĵ����ṹ��ָ��
** �����������
** ���ز�����FlagStatus��RX����״̬�����
********************************************************************/
FlagStatus DMAC_GetRxIdleStatus(DMAC0_TypeDef* DMAC_x)
{
	return (FlagStatus)((DMAC_x->STATUS & DMAC0_STATUS_RX_IDLE) == DMAC0_STATUS_RX_IDLE);
}

/********************************************************************
** �������ƣ�DMAC_GetTxIdleStatus
** �������ܣ���ȡTX���мĴ���״̬
** ���������DMAC0_TypeDef���Ĵ����ṹ��ָ��
** �����������
** ���ز�����FlagStatus��TX����״̬�����
********************************************************************/
FlagStatus DMAC_GetTxIdleStatus(DMAC0_TypeDef* DMAC_x)
{
	return (FlagStatus)((DMAC_x->STATUS & DMAC0_STATUS_TX_IDLE) == DMAC0_STATUS_TX_IDLE);
}

/********************************************************************
** �������ƣ�DMAC_GetAxiIRQStatus
** �������ܣ���ȡAXI�жϼĴ���״̬
** ���������DMAC0_TypeDef���Ĵ����ṹ��ָ��
** �����������
** ���ز�����ITStatus��RX�ж�״̬
********************************************************************/
ITStatus DMAC_GetAxiIRQStatus(DMAC0_TypeDef* DMAC_x)
{
	return (ITStatus)((DMAC_x->INTSTATUS & DMAC0_INTSTATUS_AXI_IRQ) >> DMAC0_INTSTATUS_AXI_IRQ_Pos);
}

/********************************************************************
** �������ƣ�DMAC_ClearAxiIRQ
** �������ܣ����AXI�жϼĴ���״̬
** ���������DMAC0_TypeDef���Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void DMAC_ClearAxiIRQ(DMAC0_TypeDef* DMAC_x)
{
	DMAC_x->INTCLEAR = DMAC0_INTCLEAR_AXI_IRQ;
}

/********************************************************************
** �������ƣ�DMAC_GetRxIRQStatus
** �������ܣ���ȡRX�жϼĴ���״̬
** ���������DMAC0_TypeDef���Ĵ����ṹ��ָ��
** �����������
** ���ز�����ITStatus��RX�ж�״̬
********************************************************************/
ITStatus DMAC_GetRxIRQStatus(DMAC0_TypeDef* DMAC_x)
{
	return (ITStatus)((DMAC_x->INTSTATUS & DMAC0_INTSTATUS_RXIRQ) >> DMAC0_INTSTATUS_RXIRQ_Pos);
}

/********************************************************************
** �������ƣ�DMAC_SetInitStatus
** �������ܣ�������������ʼ��״ֵ̬
** ���������DMAC0_TypeDef���Ĵ����ṹ��ָ��
**           data�����õļĴ���ֵ
** �����������
** ���ز�������
********************************************************************/
void DMAC_SetInitStatus(DMAC0_TypeDef* DMAC_x, uint32_t data)
{
	DMAC_x->STATUS = data;
}

/********************************************************************
** �������ƣ�DMAC_ClearRxIRQ
** �������ܣ����RX�жϼĴ���״̬
** ���������DMAC0_TypeDef���Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void DMAC_ClearRxIRQ(DMAC0_TypeDef* DMAC_x)
{
	DMAC_x->INTCLEAR = DMAC0_INTCLEAR_RXIRQ;
}

/********************************************************************
** �������ƣ�TS_MAC_Configure
** �������ܣ�TS_MAC���ýӿں���
** ���������mac���������mac��ַ
** �����������
** ���ز�������
********************************************************************/
void TS_MAC_Configure(uint8_t *mac)
{
	TS_MAC_TX_RX = TS_MAC_TX_RX_DATA;
	TS_MAC_CONFIG = TS_MAC_CONFIG_DATA;
	TS_MAC_ADD_FILTER = TS_MAC_ADD_FILTER_DATA;
	TS_MAC_ADD0 = mac[5] << 24 | mac[4] << 16 | mac[3] << 8 | mac[2];
	TS_MAC_ADD1 = mac[1] << 24 | mac[0] <<16;
}
