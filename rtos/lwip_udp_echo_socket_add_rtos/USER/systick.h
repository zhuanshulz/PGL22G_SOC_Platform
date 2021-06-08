#ifndef SYSTICK_H
#define SYSTICK_H

#include "PANGO_M1.h"

void SystickInit(void);
void _delay_ms(__IO uint32_t nTime);
void TimingDelay_Decrement(void);
void HAL_IncTick(void);
uint32_t HAL_GetTick(void);

#define systick_base 1000
#define delay_ms(x) _delay_ms((x));

#endif
