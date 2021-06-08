/*
 * *****************************************************************************************		
 * 文件名称：PANGO_M1_gpio.c
 * 功能描述：GPIO固件库函数
 ******************************************************************************************
 */

#include "PANGO_M1_gpio.h"

/********************************************************************
** 函数名称：GPIO_Init
** 函数功能：GPIO端口初始化，包括端口输入输出类型以及中断
** 输入参数：GPIO_TypeDef：GPIO寄存器结构体指针
**           GPIO_InitTypeDef：GPIO初始化端口参数结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void GPIO_Init(GPIO_TypeDef* GPIOx,GPIO_InitTypeDef* GPIO_InitStruct)
{
	uint32_t GPIO_Pin = GPIO_InitStruct->GPIO_Pin;
	GPIOMode_TypeDef GPIO_Mode = GPIO_InitStruct->GPIO_Mode;
	GPIOInt_TypeDef GPIO_Int = GPIO_InitStruct->GPIO_Int;

	/* 设置GPIO模式寄存器 */
	if(GPIO_Mode == GPIO_Mode_IN)
	{
		GPIOx->OUTENCLR = GPIO_Pin;
	}
	else if(GPIO_Mode == GPIO_Mode_OUT)
	{
		GPIOx->OUTENSET = GPIO_Pin;
	}
	else if(GPIO_Mode == GPIO_Mode_AF)
	{
		GPIOx->ALTFUNCSET = GPIO_Pin;
	}

	/* 设置GPIO中断寄存器 */
	if(GPIO_Int == GPIO_Int_Low_Level)
	{
		GPIOx->INTENSET |= GPIO_Pin;
		GPIOx->INTTYPECLR |= GPIO_Pin;
		GPIOx->INTPOLCLR |= GPIO_Pin;
	}
	else if(GPIO_Int == GPIO_Int_High_Level)
	{
		GPIOx->INTENSET |= GPIO_Pin;
		GPIOx->INTTYPECLR |= GPIO_Pin;
		GPIOx->INTPOLSET |= GPIO_Pin;
	}
	else if(GPIO_Int == GPIO_Int_Falling_Edge)
	{
		GPIOx->INTENSET |= GPIO_Pin;
		GPIOx->INTTYPESET |= GPIO_Pin;
		GPIOx->INTPOLCLR |= GPIO_Pin;
	}
	else if(GPIO_Int == GPIO_Int_Rising_Edge)
	{
		GPIOx->INTENSET |= GPIO_Pin;
		GPIOx->INTPOLSET |= GPIO_Pin;
		GPIOx->INTTYPESET |= GPIO_Pin;
	}
}

/********************************************************************
** 函数名称：GPIO_SetOutEnable
** 函数功能：设置GPIO端口为输出模式，设置相应的GPIO引脚为1，即可设置为输出模式
** 输入参数：GPIO_TypeDef：GPIO寄存器结构体指针
**           GPIO_Pin：GPIO引脚编号
** 输出参数：无
** 返回参数：无
********************************************************************/
void GPIO_SetOutEnable(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->OUTENSET = GPIO_Pin;
}

/********************************************************************
** 函数名称：GPIO_ClrOutEnable
** 函数功能：设置GPIO端口为输入模式，设置相应的GPIO引脚为1，即可设置为输入模式
** 输入参数：GPIO_TypeDef：GPIO寄存器结构体指针
**           GPIO_Pin：GPIO引脚编号GPIO_Pin_0-GPIO_Pin_15
** 输出参数：无
** 返回参数：无
********************************************************************/
void GPIO_ClrOutEnable(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->OUTENCLR = GPIO_Pin;
}

/********************************************************************
** 函数名称：GPIO_SetBit
** 函数功能：设置GPIO端口输出为“1”，高电平
** 输入参数：GPIO_TypeDef：GPIO寄存器结构体指针
**           GPIO_Pin：GPIO引脚编号GPIO_Pin_0-GPIO_Pin_15
** 输出参数：无
** 返回参数：无
********************************************************************/
void GPIO_SetBit(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->DATAOUT |= GPIO_Pin;
}

/********************************************************************
** 函数名称：GPIO_ResetBit
** 函数功能：设置GPIO端口输出为“0”，低电平
** 输入参数：GPIO_TypeDef：GPIO寄存器结构体指针
**           GPIO_Pin：GPIO引脚编号GPIO_Pin_0-GPIO_Pin_15
** 输出参数：无
** 返回参数：无
********************************************************************/
void GPIO_ResetBit(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->DATAOUT &= ~GPIO_Pin;
}

/********************************************************************
** 函数名称：GPIO_WriteBits
** 函数功能：设置GPIO的端口值，批量设置
** 输入参数：GPIO_TypeDef：GPIO寄存器结构体指针
**           value：需要设置GPIO的引脚值
** 输出参数：无
** 返回参数：无
********************************************************************/
void GPIO_WriteBits(GPIO_TypeDef* GPIOx,uint32_t value)
{
	GPIOx->DATAOUT = value;
}

/********************************************************************
** 函数名称：GPIO_ReadBits
** 函数功能：读取GPIO的端口值，批量读取
** 输入参数：GPIO_TypeDef：GPIO寄存器结构体指针
** 输出参数：无
** 返回参数：GPIO端口值
********************************************************************/
uint32_t GPIO_ReadBits(GPIO_TypeDef* GPIOx)
{
	return GPIOx->DATA; 
}

/********************************************************************
** 函数名称：GPIO_GetOutEnable
** 函数功能：读取GPIO的端口类型，是输入或输出
** 输入参数：GPIO_TypeDef：GPIO寄存器结构体指针
** 输出参数：无
** 返回参数：GPIO端口类型，“1”表示输出；“0”表示输入
********************************************************************/
uint32_t GPIO_GetOutEnable(GPIO_TypeDef* GPIOx)
{
	return GPIOx->OUTENSET;
}

/********************************************************************
** 函数名称：GPIO_SetAltFunc
** 函数功能：使能引脚替换功能，将对应引脚编号位设置为1，用于替换功能，
		  即：将函数的第1位设置为1，将引脚1设置为它的替换功能
** 输入参数：GPIO_TypeDef：GPIO寄存器结构体指针
**           GPIO_Pin：GPIO引脚编号GPIO_Pin_0-GPIO_Pin_15
** 输出参数：无
** 返回参数：无
********************************************************************/
void GPIO_SetAltFunc(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->ALTFUNCSET = GPIO_Pin;
}

/********************************************************************
** 函数名称：GPIO_ClrAltFunc
** 函数功能：禁止引脚替换功能，将对应引脚编号位设置为1，禁用替换功能，
		  即：将函数的第1位设置为1，将引脚1设置为原始输出模式
** 输入参数：GPIO_TypeDef：GPIO寄存器结构体指针
**           GPIO_Pin：GPIO引脚编号GPIO_Pin_0-GPIO_Pin_15
** 输出参数：无
** 返回参数：无
********************************************************************/
void GPIO_ClrAltFunc(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->ALTFUNCCLR = GPIO_Pin;
}

/********************************************************************
** 函数名称：GPIO_GetAltFunc
** 函数功能：读取GPIO的端口引脚是否设置为它的替代功能或原始输出功能
** 输入参数：GPIO_TypeDef：GPIO寄存器结构体指针
** 输出参数：无
** 返回参数：GPIO端口类型，“1”表示替换功能
********************************************************************/
uint32_t GPIO_GetAltFunc(GPIO_TypeDef* GPIOx)
{
	return GPIOx->ALTFUNCSET;
}

/********************************************************************
** 函数名称：GPIO_IntClear
** 函数功能：清除指定引脚的中断标志
** 输入参数：GPIO_TypeDef：GPIO寄存器结构体指针
**           GPIO_Pin：GPIO引脚编号GPIO_Pin_0-GPIO_Pin_15
** 输出参数：无
** 返回参数：无
********************************************************************/
void GPIO_IntClear(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->INTCLEAR |= GPIO_Pin;
}

/********************************************************************
** 函数名称：GPIO_GetIntStatus
** 函数功能：读取GPIO的中断请求状态
** 输入参数：GPIO_TypeDef：GPIO寄存器结构体指针
** 输出参数：无
** 返回参数：GPIO端口中断状态
********************************************************************/
uint32_t GPIO_GetIntStatus(GPIO_TypeDef* GPIOx)
{
	return GPIOx->INTSTATUS;
}

/********************************************************************
** 函数名称：GPIO_SetIntEnable
** 函数功能：使能指定GPIO的中断
** 输入参数：GPIO_TypeDef：GPIO寄存器结构体指针
**           GPIO_Pin：GPIO引脚编号GPIO_Pin_0-GPIO_Pin_15
** 输出参数：无
** 返回参数：GPIO端口新中断状态
********************************************************************/
uint32_t GPIO_SetIntEnable(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->INTENSET |= GPIO_Pin;
	return GPIOx->INTENSET;
}

/********************************************************************
** 函数名称：GPIO_ClrIntEnable
** 函数功能：禁用指定GPIO的中断
** 输入参数：GPIO_TypeDef：GPIO寄存器结构体指针
**           GPIO_Pin：GPIO引脚编号GPIO_Pin_0-GPIO_Pin_15
** 输出参数：无
** 返回参数：GPIO端口新中断状态
********************************************************************/
uint32_t GPIO_ClrIntEnable(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->INTENCLR |= GPIO_Pin;
	return GPIOx->INTENCLR;
}

/********************************************************************
** 函数名称：GPIO_SetIntHighLevel
** 函数功能：设置GPIO的中断为高电平触发
** 输入参数：GPIO_TypeDef：GPIO寄存器结构体指针
**           GPIO_Pin：GPIO引脚编号GPIO_Pin_0-GPIO_Pin_15
** 输出参数：无
** 返回参数：无
********************************************************************/
void GPIO_SetIntHighLevel(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->INTENSET |= GPIO_Pin;    /* Set INT Enable bit */
	GPIOx->INTTYPECLR |= GPIO_Pin; /* Clear INT TYPE bit */
	GPIOx->INTPOLSET |= GPIO_Pin;  /* Set INT POLarity bit */
}

/********************************************************************
** 函数名称：GPIO_SetIntRisingEdge
** 函数功能：设置GPIO的中断为上升沿触发
** 输入参数：GPIO_TypeDef：GPIO寄存器结构体指针
**           GPIO_Pin：GPIO引脚编号GPIO_Pin_0-GPIO_Pin_15
** 输出参数：无
** 返回参数：无
********************************************************************/
void GPIO_SetIntRisingEdge(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->INTENSET |= GPIO_Pin;   /* Set INT Enable bit */
	GPIOx->INTTYPESET |= GPIO_Pin; /* Set INT TYPE bit */
	GPIOx->INTPOLSET |= GPIO_Pin;  /* Set INT POLarity bit */
}

/********************************************************************
** 函数名称：GPIO_SetIntLowLevel
** 函数功能：设置GPIO的中断为低电平触发
** 输入参数：GPIO_TypeDef：GPIO寄存器结构体指针
**           GPIO_Pin：GPIO引脚编号GPIO_Pin_0-GPIO_Pin_15
** 输出参数：无
** 返回参数：无
********************************************************************/
void GPIO_SetIntLowLevel(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->INTENSET |= GPIO_Pin;    /* Set INT Enable bit */
	GPIOx->INTTYPECLR |= GPIO_Pin;  /* Clear INT TYPE bit */
	GPIOx->INTPOLCLR |= GPIO_Pin;   /* Clear INT POLarity bit */
}

/********************************************************************
** 函数名称：GPIO_SetIntFallingEdge
** 函数功能：设置GPIO的中断为下降沿触发
** 输入参数：GPIO_TypeDef：GPIO寄存器结构体指针
**           GPIO_Pin：GPIO引脚编号GPIO_Pin_0-GPIO_Pin_15
** 输出参数：无
** 返回参数：无
********************************************************************/
void GPIO_SetIntFallingEdge(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->INTENSET |= GPIO_Pin;    /* Set INT Enable bit */
	GPIOx->INTTYPESET |= GPIO_Pin;  /* Set INT TYPE bit */
	GPIOx->INTPOLCLR |= GPIO_Pin;   /* Clear INT POLarity bit */
}

/********************************************************************
** 函数名称：GPIO_MaskedWrite
** 函数功能：使用用户定义的掩码在所需端口上输出指定的值以执行掩码访问
** 输入参数：GPIO_TypeDef：GPIO寄存器结构体指针
**           value：GPIO引脚输出指定端口的值
**           mask：GPIO引脚输出端口掩码
** 输出参数：无
** 返回参数：无
********************************************************************/
void GPIO_MaskedWrite(GPIO_TypeDef* GPIOx,uint32_t value,uint32_t mask)
{
	GPIOx->MASKLOWBYTE[0x00FF & mask] = value;
	GPIOx->MASKHIGHBYTE[((0xFF00 & mask) >> 8)] = value;
}

