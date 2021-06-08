/*
 * *****************************************************************************************		
 * �ļ����ƣ�PANGO_M1_uart.c
 * ����������UART�̼��⺯��
 ******************************************************************************************
 */

#include "PANGO_M1_uart.h"

/********************************************************************
** �������ƣ�UART_Init
** �������ܣ����ڼĴ�����ʼ���������ж�ʹ�ܡ������ʵ�
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
**           UART_InitTypeDef��UART��ʼ���˿ڲ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
ErrorStatus UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct)
{
	uint32_t new_ctrl = 0;  
	UARTx->DATA = 0;																/* ����Ĵ���ֵ */
	UARTx->STATE = 0;
	UARTx->CTRL = 0;
	UARTx->INTCLEAR = 0;
	UARTx->BAUDDIV = 0;

	if(UART_InitStruct->UART_Mode.UARTMode_Tx == ENABLE)							/* �ж��Ƿ�ʹ��TX���� */
	{
		new_ctrl |= UART_CTRL_TXEN;
	}

	if(UART_InitStruct->UART_Mode.UARTMode_Rx == ENABLE)							/* �ж��Ƿ�ʹ��RX���� */
	{
		new_ctrl |= UART_CTRL_RXEN;
	}

	if(UART_InitStruct->UART_Int.UARTInt_Tx == ENABLE)								/* �ж��Ƿ�ʹ��TX�����ж� */
	{
		new_ctrl |= UART_CTRL_TXIRQEN;
	}

	if(UART_InitStruct->UART_Int.UARTInt_Rx == ENABLE)								/* �ж��Ƿ�ʹ��RX�����ж� */
	{
		new_ctrl |= UART_CTRL_RXIRQEN;
	}

	if(UART_InitStruct->UART_Ovr.UARTOvr_Tx == ENABLE)								/* �ж��Ƿ�ʹ��TX��� */					
	{
		new_ctrl |= UART_CTRL_TXORIRQEN;
	}

	if(UART_InitStruct->UART_Ovr.UARTOvr_Rx == ENABLE)								/* �ж��Ƿ�ʹ��RX��� */
	{
		new_ctrl |= UART_CTRL_RXORIRQEN;
	}

	if(UART_InitStruct->UART_Hstm == ENABLE)										/* �ж��Ƿ�ʹ�ܸ��ٲ���ģʽ */
	{
		new_ctrl |= UART_CTRL_HSTM;
	}

	UARTx->CTRL = 0;         														/* �������ÿ��ƼĴ���ʱ����Ҫ�Ƚ�ֹUART */
	UARTx->CTRL = new_ctrl;  														/* ���¿��ƼĴ�����ֵ */
	UARTx->BAUDDIV = SystemCoreClock / UART_InitStruct->UART_BaudRate;				/* ���ô��ڲ����� */	

	if((UARTx->STATE & (UART_STATE_RXOR | UART_STATE_TXOR)))
	{
		return ERROR;
	}
	else
	{ 
		return SUCCESS;
	}
}

/********************************************************************
** �������ƣ�UART_GetRxBufferFull
** �������ܣ���ȡ����RX�����Ƿ�����
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
** �����������
** ���ز������жϽ��
********************************************************************/
FlagStatus UART_GetRxBufferFull(UART_TypeDef* UARTx)
{
	return (FlagStatus)((UARTx->STATE & UART_STATE_RXBF) >> UART_STATE_RXBF_Pos);
}

/********************************************************************
** �������ƣ�UART_GetTxBufferFull
** �������ܣ���ȡ����TX�����Ƿ�����
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
** �����������
** ���ز������жϽ��
********************************************************************/
FlagStatus UART_GetTxBufferFull(UART_TypeDef* UARTx)
{
	return (FlagStatus)((UARTx->STATE & UART_STATE_TXBF) >> UART_STATE_TXBF_Pos);
}

/********************************************************************
** �������ƣ�UART_GetRxBufferOverrunStatus
** �������ܣ���ȡ����RX�����Ƿ������
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
** �����������
** ���ز������жϽ��
********************************************************************/
FlagStatus UART_GetRxBufferOverrunStatus(UART_TypeDef* UARTx)
{
	return (FlagStatus)((UARTx->STATE & UART_STATE_RXOR) >> UART_STATE_RXOR_Pos);
}

/********************************************************************
** �������ƣ�UART_GetTxBufferOverrunStatus
** �������ܣ���ȡ����TX�����Ƿ������
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
** �����������
** ���ز������жϽ��
********************************************************************/
FlagStatus UART_GetTxBufferOverrunStatus(UART_TypeDef* UARTx)
{
	return (FlagStatus)((UARTx->STATE & UART_STATE_TXOR) >> UART_STATE_TXOR_Pos);
}

/********************************************************************
** �������ƣ�UART_ClearRxBufferOverrunStatus
** �������ܣ��������RX�����Ƿ����״̬
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void UART_ClearRxBufferOverrunStatus(UART_TypeDef* UARTx)
{
	UARTx->STATE = UART_STATE_RXOR;
}

/********************************************************************
** �������ƣ�UART_ClearTxBufferOverrunStatus
** �������ܣ��������TX�����Ƿ����״̬
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void UART_ClearTxBufferOverrunStatus(UART_TypeDef* UARTx)
{
	UARTx->STATE = UART_STATE_TXOR;
}

/********************************************************************
** �������ƣ�UART_SendChar
** �������ܣ�����һ���ַ�
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
**           txchar�����͵��ַ�
** �����������
** ���ز�������
********************************************************************/
void UART_SendChar(UART_TypeDef* UARTx,char txchar)
{
	while(UARTx->STATE & UART_STATE_TXBF);
	UARTx->DATA = (uint32_t)txchar;
}

/********************************************************************
** �������ƣ�UART_SendString
** �������ܣ�����һ���ַ���
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
**           str�����͵��ַ���
** �����������
** ���ز�������
********************************************************************/
void UART_SendString(UART_TypeDef* pUARTx, char *str)
{
	unsigned int k = 0;
	do 
	{
		UART_SendChar( pUARTx, *(str + k) );
		k++;
	} while(*(str + k)!='\0');
}

/********************************************************************
** �������ƣ�UART_ReceiveChar
** �������ܣ�����һ���ַ�
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
** �����������
** ���ز��������յ��ַ�
********************************************************************/
char UART_ReceiveChar(UART_TypeDef* UARTx)
{
	while(!(UARTx->STATE & UART_STATE_RXBF));
	return (char)(UARTx->DATA);
}

/********************************************************************
** �������ƣ�UART_GetBaudDivider
** �������ܣ���ȡ���ڲ�����
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
** �����������
** ���ز��������ڲ�����
********************************************************************/
uint32_t UART_GetBaudDivider(UART_TypeDef* UARTx)
{
	return UARTx->BAUDDIV;
}

/********************************************************************
** �������ƣ�UART_GetTxIRQStatus
** �������ܣ���ȡTX�ж�״̬
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
** �����������
** ���ز�����TX�ж�״̬�Ĵ���ֵ
********************************************************************/
ITStatus UART_GetTxIRQStatus(UART_TypeDef* UARTx)
{
	return (ITStatus)((UARTx->INTSTATUS & UART_INTSTATUS_TXIRQ) >> UART_INTSTATUS_TXIRQ_Pos);
}

/********************************************************************
** �������ƣ�UART_GetRxIRQStatus
** �������ܣ���ȡRX�ж�״̬
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
** �����������
** ���ز�����RX�ж�״̬�Ĵ���ֵ
********************************************************************/
ITStatus UART_GetRxIRQStatus(UART_TypeDef* UARTx)
{
	return (ITStatus)((UARTx->INTSTATUS & UART_INTSTATUS_RXIRQ) >> UART_INTSTATUS_RXIRQ_Pos);
}

/********************************************************************
** �������ƣ�UART_ClearTxIRQ
** �������ܣ����TX�ж�״̬
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void UART_ClearTxIRQ(UART_TypeDef* UARTx)
{
	UARTx->INTCLEAR = UART_INTCLEAR_TXIRQ;
}

/********************************************************************
** �������ƣ�UART_ClearRxIRQ
** �������ܣ����RX�ж�״̬
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void UART_ClearRxIRQ(UART_TypeDef* UARTx)
{
	UARTx->INTCLEAR = UART_INTCLEAR_RXIRQ;
}

/********************************************************************
** �������ƣ�UART_GetTxOverrunIRQStatus
** �������ܣ���ȡTX����ж�״̬
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
** �����������
** ���ز�����TX����ж�״̬�Ĵ���ֵ
********************************************************************/
ITStatus UART_GetTxOverrunIRQStatus(UART_TypeDef* UARTx)
{
	return (ITStatus)((UARTx->INTSTATUS & UART_INTSTATUS_TXORIRQ) >> UART_INTSTATUS_TXORIRQ_Pos);
}

/********************************************************************
** �������ƣ�UART_GetRxOverrunIRQStatus
** �������ܣ���ȡRX����ж�״̬
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
** �����������
** ���ز�����RX����ж�״̬�Ĵ���ֵ
********************************************************************/
ITStatus UART_GetRxOverrunIRQStatus(UART_TypeDef* UARTx)
{
	return (ITStatus)((UARTx->INTSTATUS & UART_INTSTATUS_RXORIRQ) >> UART_INTSTATUS_RXORIRQ_Pos);
}

/********************************************************************
** �������ƣ�UART_ClearTxOverrunIRQ
** �������ܣ����TX����ж�����
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void UART_ClearTxOverrunIRQ(UART_TypeDef* UARTx)
{
	UARTx->INTCLEAR = UART_INTCLEAR_TXORIRQ;
}

/********************************************************************
** �������ƣ�UART_ClearRxOverrunIRQ
** �������ܣ����RX����ж�����
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void UART_ClearRxOverrunIRQ(UART_TypeDef* UARTx)
{
	UARTx->INTCLEAR = UART_INTCLEAR_RXORIRQ;
}

/********************************************************************
** �������ƣ�UART_SetHSTM
** �������ܣ�����UART������ٲ���ģʽ
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void UART_SetHSTM(UART_TypeDef* UARTx)
{
	UARTx->CTRL |= UART_CTRL_HSTM;
}

/********************************************************************
** �������ƣ�UART_ClrHSTM
** �������ܣ����UART���ٲ���ģʽ
** ���������UART_TypeDef��UART�Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void UART_ClrHSTM(UART_TypeDef* UARTx)
{
	UARTx->CTRL &= ~UART_CTRL_HSTM;
}

