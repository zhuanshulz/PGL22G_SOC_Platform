#ifndef PANGO_M1_TIMER_H
#define PANGO_M1_TIMER_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "PANGO_M1.h"

typedef FunctionalState TIMERInt_TypeDef;  /* ENABLE/DISABLE */

typedef enum
{
  TIMER_DISABLE = 0,  /* External Disable */
  TIMER_EXTI_EN,      /* Select external input as enable */
  TIMER_EXTI_CLK      /* Select external input as clock */
}TIMERExti_TypeDef;

typedef struct
{
  uint32_t Reload;                 /* 重新加载值 */

  TIMERInt_TypeDef TIMER_Int;      /* 定时器中断控制 */

  TIMERExti_TypeDef TIMER_Exti;    /* 选择定时器中断外部触发 */

}TIMER_InitTypeDef;


#define TIMER_CTRL_EN_Pos         0  /* TIMER CTRL: Enable Position */
#define TIMER_CTRL_SELEXTEN_Pos   1  /* TIMER CTRL: External Enable Position */
#define TIMER_CTRL_SELEXTCLK_Pos  2  /* TIMER CTRL: External Clock Position */
#define TIMER_CTRL_IRQEN_Pos      3  /* TIMER CTRL: Interrupt Enable Position */

extern void TIMER_Init(TIMER_TypeDef* TIMERx,TIMER_InitTypeDef* TIMER_InitStruct);
extern void TIMER_StartTimer(TIMER_TypeDef* TIMERx);
extern void TIMER_StopTimer(TIMER_TypeDef* TIMERx);
extern ITStatus TIMER_GetIRQStatus(TIMER_TypeDef* TIMERx);
extern void TIMER_ClearIRQ(TIMER_TypeDef* TIMERx);
extern uint32_t TIMER_GetReload(TIMER_TypeDef* TIMERx);
extern void TIMER_SetReload(TIMER_TypeDef* TIMERx,uint32_t value);
extern uint32_t TIMER_GetValue(TIMER_TypeDef* TIMERx);
extern void TIMER_SetValue(TIMER_TypeDef* TIMERx,uint32_t value);
extern void TIMER_EnableIRQ(TIMER_TypeDef* TIMERx);
extern void TIMER_DisableIRQ(TIMER_TypeDef* TIMERx);
extern void TIMER_SelExtEnable(TIMER_TypeDef *TIMER);
extern void TIMER_SelExtClock(TIMER_TypeDef *TIMER);

#ifdef __cplusplus
}
#endif

#endif  /* PANGO_M1_TIMER_H */


