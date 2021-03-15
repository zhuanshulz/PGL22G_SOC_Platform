/*
 * *****************************************************************************************		
 * 文件名称：PANGO_M1_uart.c
 * 功能描述：UART固件库函数
 ******************************************************************************************
 */

#include "PANGO_M1_uart.h"

/********************************************************************
** 函数名称：UART_Init
** 函数功能：串口寄存器初始化，配置中断使能、波特率等
** 输入参数：UART_TypeDef：UART寄存器结构体指针
**           UART_InitTypeDef：UART初始化端口参数结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
ErrorStatus UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct)
{
	uint32_t new_ctrl = 0;  
	UARTx->DATA = 0;																/* 清零寄存器值 */
	UARTx->STATE = 0;
	UARTx->CTRL = 0;
	UARTx->INTCLEAR = 0;
	UARTx->BAUDDIV = 0;

	if(UART_InitStruct->UART_Mode.UARTMode_Tx == ENABLE)							/* 判断是否使能TX引脚 */
	{
		new_ctrl |= UART_CTRL_TXEN;
	}

	if(UART_InitStruct->UART_Mode.UARTMode_Rx == ENABLE)							/* 判断是否使能RX引脚 */
	{
		new_ctrl |= UART_CTRL_RXEN;
	}

	if(UART_InitStruct->UART_Int.UARTInt_Tx == ENABLE)								/* 判断是否使能TX引脚中断 */
	{
		new_ctrl |= UART_CTRL_TXIRQEN;
	}

	if(UART_InitStruct->UART_Int.UARTInt_Rx == ENABLE)								/* 判断是否使能RX引脚中断 */
	{
		new_ctrl |= UART_CTRL_RXIRQEN;
	}

	if(UART_InitStruct->UART_Ovr.UARTOvr_Tx == ENABLE)								/* 判断是否使能TX溢出 */					
	{
		new_ctrl |= UART_CTRL_TXORIRQEN;
	}

	if(UART_InitStruct->UART_Ovr.UARTOvr_Rx == ENABLE)								/* 判断是否使能RX溢出 */
	{
		new_ctrl |= UART_CTRL_RXORIRQEN;
	}

	if(UART_InitStruct->UART_Hstm == ENABLE)										/* 判断是否使能高速测试模式 */
	{
		new_ctrl |= UART_CTRL_HSTM;
	}

	UARTx->CTRL = 0;         														/* 重新配置控制寄存器时，需要先禁止UART */
	UARTx->CTRL = new_ctrl;  														/* 更新控制寄存器的值 */
	UARTx->BAUDDIV = SystemCoreClock / UART_InitStruct->UART_BaudRate;				/* 配置串口波特率 */	

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
** 函数名称：UART_GetRxBufferFull
** 函数功能：获取串口RX缓存是否满了
** 输入参数：UART_TypeDef：UART寄存器结构体指针
** 输出参数：无
** 返回参数：判断结果
********************************************************************/
FlagStatus UART_GetRxBufferFull(UART_TypeDef* UARTx)
{
	return (FlagStatus)((UARTx->STATE & UART_STATE_RXBF) >> UART_STATE_RXBF_Pos);
}

/********************************************************************
** 函数名称：UART_GetTxBufferFull
** 函数功能：获取串口TX缓存是否满了
** 输入参数：UART_TypeDef：UART寄存器结构体指针
** 输出参数：无
** 返回参数：判断结果
********************************************************************/
FlagStatus UART_GetTxBufferFull(UART_TypeDef* UARTx)
{
	return (FlagStatus)((UARTx->STATE & UART_STATE_TXBF) >> UART_STATE_TXBF_Pos);
}

/********************************************************************
** 函数名称：UART_GetRxBufferOverrunStatus
** 函数功能：获取串口RX缓存是否溢出了
** 输入参数：UART_TypeDef：UART寄存器结构体指针
** 输出参数：无
** 返回参数：判断结果
********************************************************************/
FlagStatus UART_GetRxBufferOverrunStatus(UART_TypeDef* UARTx)
{
	return (FlagStatus)((UARTx->STATE & UART_STATE_RXOR) >> UART_STATE_RXOR_Pos);
}

/********************************************************************
** 函数名称：UART_GetTxBufferOverrunStatus
** 函数功能：获取串口TX缓存是否溢出了
** 输入参数：UART_TypeDef：UART寄存器结构体指针
** 输出参数：无
** 返回参数：判断结果
********************************************************************/
FlagStatus UART_GetTxBufferOverrunStatus(UART_TypeDef* UARTx)
{
	return (FlagStatus)((UARTx->STATE & UART_STATE_TXOR) >> UART_STATE_TXOR_Pos);
}

/********************************************************************
** 函数名称：UART_ClearRxBufferOverrunStatus
** 函数功能：清除串口RX缓存是否溢出状态
** 输入参数：UART_TypeDef：UART寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void UART_ClearRxBufferOverrunStatus(UART_TypeDef* UARTx)
{
	UARTx->STATE = UART_STATE_RXOR;
}

/********************************************************************
** 函数名称：UART_ClearTxBufferOverrunStatus
** 函数功能：清除串口TX缓存是否溢出状态
** 输入参数：UART_TypeDef：UART寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void UART_ClearTxBufferOverrunStatus(UART_TypeDef* UARTx)
{
	UARTx->STATE = UART_STATE_TXOR;
}

/********************************************************************
** 函数名称：UART_SendChar
** 函数功能：发送一个字符
** 输入参数：UART_TypeDef：UART寄存器结构体指针
**           txchar：发送的字符
** 输出参数：无
** 返回参数：无
********************************************************************/
void UART_SendChar(UART_TypeDef* UARTx,char txchar)
{
	while(UARTx->STATE & UART_STATE_TXBF);
	UARTx->DATA = (uint32_t)txchar;
}

/********************************************************************
** 函数名称：UART_SendString
** 函数功能：发送一个字符串
** 输入参数：UART_TypeDef：UART寄存器结构体指针
**           str：发送的字符串
** 输出参数：无
** 返回参数：无
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
** 函数名称：UART_ReceiveChar
** 函数功能：接收一个字符
** 输入参数：UART_TypeDef：UART寄存器结构体指针
** 输出参数：无
** 返回参数：接收的字符
********************************************************************/
char UART_ReceiveChar(UART_TypeDef* UARTx)
{
	while(!(UARTx->STATE & UART_STATE_RXBF));
	return (char)(UARTx->DATA);
}

/********************************************************************
** 函数名称：UART_GetBaudDivider
** 函数功能：获取串口波特率
** 输入参数：UART_TypeDef：UART寄存器结构体指针
** 输出参数：无
** 返回参数：串口波特率
********************************************************************/
uint32_t UART_GetBaudDivider(UART_TypeDef* UARTx)
{
	return UARTx->BAUDDIV;
}

/********************************************************************
** 函数名称：UART_GetTxIRQStatus
** 函数功能：获取TX中断状态
** 输入参数：UART_TypeDef：UART寄存器结构体指针
** 输出参数：无
** 返回参数：TX中断状态寄存器值
********************************************************************/
ITStatus UART_GetTxIRQStatus(UART_TypeDef* UARTx)
{
	return (ITStatus)((UARTx->INTSTATUS & UART_INTSTATUS_TXIRQ) >> UART_INTSTATUS_TXIRQ_Pos);
}

/********************************************************************
** 函数名称：UART_GetRxIRQStatus
** 函数功能：获取RX中断状态
** 输入参数：UART_TypeDef：UART寄存器结构体指针
** 输出参数：无
** 返回参数：RX中断状态寄存器值
********************************************************************/
ITStatus UART_GetRxIRQStatus(UART_TypeDef* UARTx)
{
	return (ITStatus)((UARTx->INTSTATUS & UART_INTSTATUS_RXIRQ) >> UART_INTSTATUS_RXIRQ_Pos);
}

/********************************************************************
** 函数名称：UART_ClearTxIRQ
** 函数功能：清除TX中断状态
** 输入参数：UART_TypeDef：UART寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void UART_ClearTxIRQ(UART_TypeDef* UARTx)
{
	UARTx->INTCLEAR = UART_INTCLEAR_TXIRQ;
}

/********************************************************************
** 函数名称：UART_ClearRxIRQ
** 函数功能：清除RX中断状态
** 输入参数：UART_TypeDef：UART寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void UART_ClearRxIRQ(UART_TypeDef* UARTx)
{
	UARTx->INTCLEAR = UART_INTCLEAR_RXIRQ;
}

/********************************************************************
** 函数名称：UART_GetTxOverrunIRQStatus
** 函数功能：获取TX溢出中断状态
** 输入参数：UART_TypeDef：UART寄存器结构体指针
** 输出参数：无
** 返回参数：TX溢出中断状态寄存器值
********************************************************************/
ITStatus UART_GetTxOverrunIRQStatus(UART_TypeDef* UARTx)
{
	return (ITStatus)((UARTx->INTSTATUS & UART_INTSTATUS_TXORIRQ) >> UART_INTSTATUS_TXORIRQ_Pos);
}

/********************************************************************
** 函数名称：UART_GetRxOverrunIRQStatus
** 函数功能：获取RX溢出中断状态
** 输入参数：UART_TypeDef：UART寄存器结构体指针
** 输出参数：无
** 返回参数：RX溢出中断状态寄存器值
********************************************************************/
ITStatus UART_GetRxOverrunIRQStatus(UART_TypeDef* UARTx)
{
	return (ITStatus)((UARTx->INTSTATUS & UART_INTSTATUS_RXORIRQ) >> UART_INTSTATUS_RXORIRQ_Pos);
}

/********************************************************************
** 函数名称：UART_ClearTxOverrunIRQ
** 函数功能：清除TX溢出中断请求
** 输入参数：UART_TypeDef：UART寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void UART_ClearTxOverrunIRQ(UART_TypeDef* UARTx)
{
	UARTx->INTCLEAR = UART_INTCLEAR_TXORIRQ;
}

/********************************************************************
** 函数名称：UART_ClearRxOverrunIRQ
** 函数功能：清除RX溢出中断请求
** 输入参数：UART_TypeDef：UART寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void UART_ClearRxOverrunIRQ(UART_TypeDef* UARTx)
{
	UARTx->INTCLEAR = UART_INTCLEAR_RXORIRQ;
}

/********************************************************************
** 函数名称：UART_SetHSTM
** 函数功能：设置UART进入高速测试模式
** 输入参数：UART_TypeDef：UART寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void UART_SetHSTM(UART_TypeDef* UARTx)
{
	UARTx->CTRL |= UART_CTRL_HSTM;
}

/********************************************************************
** 函数名称：UART_ClrHSTM
** 函数功能：清除UART高速测试模式
** 输入参数：UART_TypeDef：UART寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void UART_ClrHSTM(UART_TypeDef* UARTx)
{
	UARTx->CTRL &= ~UART_CTRL_HSTM;
}

