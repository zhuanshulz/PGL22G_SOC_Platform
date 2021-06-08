/*
 * *****************************************************************************************
 * 文件名称：system_PANGO_M1.c
 * 功能描述：系统初始化固件库函数
 ******************************************************************************************
 */

#include "PANGO_M1.h"

/*----------------------------------------------------------------------------
  定义系统时钟
 *----------------------------------------------------------------------------*/
#define  XTAL            (125000000UL)     	/* 晶振频率 */

#define  SYSTEM_CLOCK    (XTAL)       		/* 100MHz  */

uint32_t SystemCoreClock = SYSTEM_CLOCK;  	/* 系统内核时钟 */

/********************************************************************
** 函数名称：SystemCoreClockUpdate
** 函数功能：更新系统内核时钟
** 输入参数：无
** 输出参数：无
** 返回参数：无
********************************************************************/
void SystemCoreClockUpdate (void)
{
  SystemCoreClock = SYSTEM_CLOCK;
}

/********************************************************************
** 函数名称：SystemInit
** 函数功能：系统初始化函数
** 输入参数：无
** 输出参数：无
** 返回参数：无
********************************************************************/
void SystemInit (void)
{
	SystemCoreClock = SYSTEM_CLOCK;
		GPIO0->DATA = 0;
	GPIO0->DATAOUT = 0;
	GPIO0->OUTENSET = 0;
	GPIO0->OUTENCLR = 0;
	GPIO0->ALTFUNCSET = 0;
	GPIO0->ALTFUNCCLR = 0;
	GPIO0->INTENSET = 0;
	GPIO0->INTENCLR = 0;
	GPIO0->INTTYPESET = 0;
	GPIO0->INTTYPECLR = 0;
	GPIO0->INTPOLSET = 0;
	GPIO0->INTPOLCLR = 0;
	GPIO0->INTCLEAR = 0;
	for(int pos = 0;pos < 256;pos++)
	{
		GPIO0->MASKLOWBYTE[pos] = 0;
		GPIO0->MASKHIGHBYTE[pos] = 0;
	}
}
