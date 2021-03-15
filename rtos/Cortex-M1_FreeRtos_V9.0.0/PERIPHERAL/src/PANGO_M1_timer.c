/*
 * *****************************************************************************************		
 * 文件名称：PANGO_M1_timer.c
 * 功能描述：TIMER固件库函数
 ******************************************************************************************
 */

#include "PANGO_M1_timer.h"

/********************************************************************
** 函数名称：TIMER_Init
** 函数功能：定时器中断寄存器初始化，配置中断使能、中断触发方式、计数器大小等
** 输入参数：TIMER_TypeDef：TIMER寄存器结构体指针
**           TIMER_InitTypeDef：TIMER初始化端口参数结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void TIMER_Init(TIMER_TypeDef* TIMERx,TIMER_InitTypeDef* TIMER_InitStruct)
{
	TIMERx->CTRL = 0;														  	/* 清零所有寄存器 */
	TIMERx->VALUE = 0;
	TIMERx->RELOAD = 0;
	TIMERx->INTCLEAR = 0;

	TIMERx->VALUE = TIMER_InitStruct->Reload;									/* 配置VALUE寄存器 */  
	TIMERx->RELOAD = TIMER_InitStruct->Reload;									/* 配置RELOAD寄存器 */  
	TIMERx->CTRL |= TIMER_CTRL_EN;												/* 使能定时器 */

	if(TIMER_InitStruct->TIMER_Int == ENABLE)									/* 判断是否需要使能定时器中断 */
	{
		TIMERx->CTRL |= TIMER_CTRL_IRQEN;
	}

	if(TIMER_InitStruct->TIMER_Exti == TIMER_DISABLE)							/* 判断是否需要禁止外部触发定时器中断 */
	{
		TIMERx->CTRL &= ~(TIMER_CTRL_SELEXTEN |TIMER_CTRL_SELEXTEN );			
	}

	if(TIMER_InitStruct->TIMER_Exti == TIMER_EXTI_EN)							/* 判断是否需要使能外部触发中断 */
	{
		TIMERx->CTRL |= TIMER_CTRL_SELEXTEN;									
	}
	else if(TIMER_InitStruct->TIMER_Exti == TIMER_EXTI_CLK)						/* 判断是否需要内部时钟输入 */
	{
		TIMERx->CTRL |= TIMER_CTRL_SELEXTCLK;
	}
}

/********************************************************************
** 函数名称：TIMER_StartTimer
** 函数功能：开启定时器中断
** 输入参数：TIMER_TypeDef：TIMER寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void TIMER_StartTimer(TIMER_TypeDef* TIMERx)
{
	TIMERx->CTRL |= TIMER_CTRL_EN;
}

/********************************************************************
** 函数名称：TIMER_StopTimer
** 函数功能：停止定时器中断
** 输入参数：TIMER_TypeDef：TIMER寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void TIMER_StopTimer(TIMER_TypeDef* TIMERx)
{
	TIMERx->CTRL &= ~TIMER_CTRL_EN;
}

/********************************************************************
** 函数名称：TIMER_GetIRQStatus
** 函数功能：读取定时器中断状态寄存器值
** 输入参数：TIMER_TypeDef：TIMER寄存器结构体指针
** 输出参数：无
** 返回参数：中断状态寄存器值
********************************************************************/
ITStatus TIMER_GetIRQStatus(TIMER_TypeDef* TIMERx)
{
	return (ITStatus)(TIMERx->INTSTATUS);
}

/********************************************************************
** 函数名称：TIMER_ClearIRQ
** 函数功能：清除定时器中断
** 输入参数：TIMER_TypeDef：TIMER寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void TIMER_ClearIRQ(TIMER_TypeDef* TIMERx)
{
	TIMERx->INTCLEAR = TIMER_INTCLEAR;
}

/********************************************************************
** 函数名称：TIMER_GetReload
** 函数功能：读取定时器重新加载值，重新加载值是定时器在发生溢出后设置的值
** 输入参数：TIMER_TypeDef：TIMER寄存器结构体指针
** 输出参数：无
** 返回参数：定时器重新加载值
********************************************************************/
uint32_t TIMER_GetReload(TIMER_TypeDef* TIMERx)
{
	return TIMERx->RELOAD;
}

/********************************************************************
** 函数名称：TIMER_SetReload
** 函数功能：设置定时器重新加载值，重新加载值是定时器在发生溢出后设置的值
** 输入参数：TIMER_TypeDef：TIMER寄存器结构体指针
**			  value：重新加载值
** 输出参数：无
** 返回参数：无
********************************************************************/
void TIMER_SetReload(TIMER_TypeDef* TIMERx,uint32_t value)
{
	TIMERx->RELOAD = value;
}

/********************************************************************
** 函数名称：TIMER_GetValue
** 函数功能：读取定时器当前计数值
** 输入参数：TIMER_TypeDef：TIMER寄存器结构体指针
** 输出参数：无
** 返回参数：定时器当前计数值
********************************************************************/
uint32_t TIMER_GetValue(TIMER_TypeDef* TIMERx)
{
	return TIMERx->VALUE;
}

/********************************************************************
** 函数名称：TIMER_SetValue
** 函数功能：设置定时器当前计数值
** 输入参数：TIMER_TypeDef：TIMER寄存器结构体指针
**			  value：新计数值
** 输出参数：无
** 返回参数：无
********************************************************************/
void TIMER_SetValue(TIMER_TypeDef* TIMERx,uint32_t value)
{
	TIMERx->VALUE = value;
}

/********************************************************************
** 函数名称：TIMER_EnableIRQ
** 函数功能：使能定时器中断请求
** 输入参数：TIMER_TypeDef：TIMER寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void TIMER_EnableIRQ(TIMER_TypeDef* TIMERx)
{
	TIMERx->CTRL |= TIMER_CTRL_IRQEN;
}

/********************************************************************
** 函数名称：TIMER_DisableIRQ
** 函数功能：禁止定时器中断请求
** 输入参数：TIMER_TypeDef：TIMER寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void TIMER_DisableIRQ(TIMER_TypeDef* TIMERx)
{
	TIMERx->CTRL &= ~TIMER_CTRL_IRQEN;
}

/********************************************************************
** 函数名称：TIMER_SelExtEnable
** 函数功能：使能外部触发定时器中断
** 输入参数：TIMER_TypeDef：TIMER寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void TIMER_SelExtEnable(TIMER_TypeDef *TIMER)
{
	TIMER->CTRL = ~(TIMER_CTRL_SELEXTEN |TIMER_CTRL_SELEXTCLK );
	TIMER->CTRL |= TIMER_CTRL_SELEXTEN;    
}

/********************************************************************
** 函数名称：TIMER_SelExtClock
** 函数功能：选择外部输入定时器中断时钟
** 输入参数：TIMER_TypeDef：TIMER寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void TIMER_SelExtClock(TIMER_TypeDef *TIMER)
{
	TIMER->CTRL = ~(TIMER_CTRL_SELEXTEN |TIMER_CTRL_SELEXTCLK );
	TIMER->CTRL |= TIMER_CTRL_SELEXTCLK;    
}

