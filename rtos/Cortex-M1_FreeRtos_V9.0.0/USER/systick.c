 /*
 * *****************************************************************************************		
 * 文件名称：systick.c
 * 功能描述：系统定时器中断函数 
 ******************************************************************************************
 */
#include "systick.h"

static __IO uint32_t TimingDelay;

/** 
  * @brief  Initialises the systick.
  */
void SystickInit(void)
{
	uint32_t temp = SystemCoreClock / 1000;				//1ms interrupt
	SysTick->LOAD = temp;
	SysTick->VAL = 0;										//Reset current counter's value
	
	//select clock source, enable interrupt, enable counter
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | 
									SysTick_CTRL_TICKINT_Msk | 
									SysTick_CTRL_ENABLE_Msk; 
}

/**
  * @param nTime*ms
  * @return none
  * @brief delay ms
  */
void _delay_ms(__IO uint32_t nTime)
{
	TimingDelay = nTime;
	
	//enable systick
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	
	while(TimingDelay != 0);
}

/**
  * @param none
  * @return none
  * @brief get systick,add into SysTick_Handler
  */
void TimingDelay_Decrement(void)
{
	if(TimingDelay != 0x00)
	{
		TimingDelay--;
	}
}

//SysTick interrupt handler --> PANGO_M1_it.c
