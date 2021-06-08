/*
 * *****************************************************************************************		
 * �ļ����ƣ�PANGO_M1_eth_buffer.c
 * ����������ETH BUFFER�̼��⺯��
 ******************************************************************************************
 */
#include <string.h>
#include "PANGO_M1_eth_buffer.h"
#include "ethernetif.h"

DESCRIPTOR_BUF eth_tx_buf[DESCRIPTOR_TX_BUF_CNT];
DESCRIPTOR_BUF eth_rx_buf[DESCRIPTOR_RX_BUF_CNT];
CURRENT_DESCRIPTOR_NUM descriptor_num;

/********************************************************************
** �������ƣ�eth_buf_init
** �������ܣ�ETH��������ʼ��
** �����������
** �����������
** ���ز�������
********************************************************************/
void eth_buf_init(void)
{
	descriptor_num.buf_size = DESCRIPTOR_BUF_SIZE;
	descriptor_num.max_tx_num = DESCRIPTOR_TX_BUF_CNT;
	descriptor_num.max_rx_num = DESCRIPTOR_RX_BUF_CNT;
	descriptor_num.rx_num = 0;
	descriptor_num.tx_num = 0;
	DMAC_SetInitStatus(DMAC0, 0);
	eth_tx_buf_init();
	eth_rx_buf_init();
	DMAC_SetInitStatus(DMAC0, DMAC0_STATUS_INIT_DONE);
}

/********************************************************************
** �������ƣ�eth_tx_buf_init
** �������ܣ�ETH TX��������ʼ��
** �����������
** �����������
** ���ز�������
********************************************************************/
void eth_tx_buf_init(void)
{
	int i = 0;
	int num,link_num;
	uint32_t temp_addr;
	for(i = 0; i < DESCRIPTOR_TX_BUF_CNT; i++)
	{
		num = i;
		if(DESCRIPTOR_TX_BUF_CNT == (i + 1))
		{
			link_num = 0;
		}
		else
		{
			link_num = i + 1;
		}
		temp_addr = DESCRIPTOR_TX_BUF_BASE + i*BUF_BOUNDARY_SIZE;
		eth_tx_buf[i].data_buf = (char *)(temp_addr);
		eth_tx_buf[i].data_len = 0;
		eth_tx_buf[i].data_state = false;
		eth_tx_buf[i].data_error = false;
		SetTxDescriptor(DMAC0, num, link_num, temp_addr, DESCRIPTOR_BUF_SIZE);
	}
}

/********************************************************************
** �������ƣ�eth_rx_buf_init
** �������ܣ�ETH RX��������ʼ��
** �����������
** �����������
** ���ز�������
********************************************************************/
void eth_rx_buf_init(void)
{
	int i = 0;
	int num,link_num;
	uint32_t temp_addr;
	for(i = 0; i < DESCRIPTOR_RX_BUF_CNT; i++)
	{
		num = i;
		if(DESCRIPTOR_RX_BUF_CNT == (i + 1))
		{
			link_num = 0;
		}
		else
		{
			link_num = i + 1;
		}
		temp_addr = DESCRIPTOR_RX_BUF_BASE + i*BUF_BOUNDARY_SIZE;
		eth_rx_buf[i].data_buf = (char *)(temp_addr);
		eth_rx_buf[i].data_len = 0;
		eth_rx_buf[i].data_state = false;
		eth_rx_buf[i].data_error = false;
		SetRxDescriptor(DMAC0, num, link_num, temp_addr, DESCRIPTOR_BUF_SIZE);
	}
}

/********************************************************************
** �������ƣ�eth_rx_buf_init
** �������ܣ�ETH RX��������ʼ��
** �����������
** �����������
** ���ز�����bool�����ͽ��
********************************************************************/
bool eth_tx_data(char * data, int len)
{
	descriptor_num.tx_num = GetCurrentTxDescriptorNum(DMAC0);
	if(DESCRIPTOR_BUF_SIZE >= len)
	{
		memcpy(eth_tx_buf[descriptor_num.tx_num].data_buf, data, len);
		eth_tx_buf[descriptor_num.tx_num].data_len = len;
		SetTxDataLen(DMAC0, len);
		eth_tx_buf_flush(&descriptor_num, len);
		SetDmacTxCtrl(DMAC0);
	}
	else
	{
		return false;
	}
	return true;
}

/********************************************************************
** �������ƣ�eth_clear_buf
** �������ܣ�ETH RX��������ʼ��
** ���������CURRENT_DESCRIPTOR_NUM���������Žṹ��
** ���������RX��������
** ���ز�������
********************************************************************/
void clear_eth_rx_buf(CURRENT_DESCRIPTOR_NUM * num)
{
	int temp_num = 0;
	int temp_len = 0;
	temp_num = num->rx_num;
	temp_len = eth_rx_buf[temp_num].data_len;
	memset(eth_rx_buf[temp_num].data_buf, 0, temp_len);
	eth_rx_buf_flush(num, temp_len);
	eth_rx_buf[temp_num].data_len = 0;
	eth_rx_buf[temp_num].data_state = false;
	eth_rx_buf[temp_num].data_error = false;
	CleanRxDescriptorNum(DMAC0, temp_num);									/* ������������������ */
	temp_num = temp_num + 1;
	if(temp_num < num->max_rx_num)
	{
		num->rx_num++;
	}
	else
	{
		num->rx_num = 0;
	}
}

/********************************************************************
** �������ƣ�eth_tx_buf_flush
** �������ܣ�ETH TX��������д
** ���������CURRENT_DESCRIPTOR_NUM���������Žṹ��
**			 len���������ݳ���
** �����������
** ���ز�������
********************************************************************/
void eth_tx_buf_flush(CURRENT_DESCRIPTOR_NUM * num, int len)
{
	while(DMAC_GetRxIdleStatus(DMAC0) == 1);
	DCACHE_FlushRange((uint32_t)eth_tx_buf[num->tx_num].data_buf, len);
}

/********************************************************************
** �������ƣ�eth_rx_buf_invalidate
** �������ܣ�ETH RX������ˢ��
** ���������CURRENT_DESCRIPTOR_NUM���������Žṹ��
** �����������
** ���ز�������
********************************************************************/
void eth_rx_buf_invalidate(CURRENT_DESCRIPTOR_NUM * num)
{
	while(DMAC_GetRxIdleStatus(DMAC0) == 1);
	DCACHE_InvalidateRange((uint32_t)eth_rx_buf[num->rx_num].data_buf, eth_rx_buf[num->rx_num].data_len);
}

/********************************************************************
** �������ƣ�eth_rx_buf_flush
** �������ܣ�ETH RX��������д
** ���������CURRENT_DESCRIPTOR_NUM���������Žṹ��
**			 len���������ݳ���
** �����������
** ���ز�������
********************************************************************/
void eth_rx_buf_flush(CURRENT_DESCRIPTOR_NUM * num, int len)
{
	while(DMAC_GetRxIdleStatus(DMAC0) == 1);
	DCACHE_FlushRange((uint32_t)eth_rx_buf[num->rx_num].data_buf, len);
}

/********************************************************************
** �������ƣ�ENT_Handler
** �������ܣ�ENT�ж��쳣������(ֱ�ӼĴ���������Ч�ʸ�)
** �����������
** �����������
** ���ز�������
********************************************************************/
void ENT_Handler(void)
{
	int rx_num;
	DMAC0->INTCLEAR = DMAC0_INTCLEAR_AXI_IRQ;							/* ���DMA0 AXI�����ж� */
	if(DMAC_GetRxIRQStatus(DMAC0) != RESET)
	{
		rx_num = (int)DMAC0->DMAC_RX_NUM;
		eth_rx_buf[rx_num].data_state = true;
		eth_rx_buf[rx_num].data_len = (int)DMAC0->DMAC_RX_LEN;
#if !NO_SYS 		
		portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR( s_xSemaphore, &xHigherPriorityTaskWoken );
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
#endif		
		DMAC0->INTCLEAR = DMAC0_INTCLEAR_RXIRQ;							/* ���DMA0 RX�����ж� */
	}
}

