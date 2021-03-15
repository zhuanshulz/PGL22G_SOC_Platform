#ifndef PANGO_M1_WDOG_H
#define PANGO_M1_WDOG_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "PANGO_M1.h"

typedef FunctionalState WDOGLock_TypeDef;

typedef FunctionalState WDOGInt_TypeDef;

typedef FunctionalState WDOGRes_TypeDef;

typedef FunctionalState WDOGMode_Typedef;

typedef struct
{
  uint32_t WDOG_Reload;         /* 看门狗重新加载值 */
  
  WDOGLock_TypeDef WDOG_Lock;   /* 看门狗锁寄存器写通道 */
  
  WDOGInt_TypeDef WDOG_Int;     /* 看门狗中断使能标志 */
  
  WDOGRes_TypeDef WDOG_Res;     /* 看门狗复位使能标志 */
  
  WDOGMode_Typedef WDOG_ITMode; /* 看门狗集成测试模式使能标志 */
  
}WDOG_InitTypeDef;

#define WDOG_LOCK_EN_Pos 1           /*[31:1] write register access enable   */
#define WDOG_CTRL_INTEN_Pos 0        /* CTRL register INTEN bit position     */
#define WDOG_CTRL_RESEN_Pos 1        /* CTRL register RESEN bit position     */
#define WDOG_RAWINTSTAT_Pos 0        /* Raw Interrupt Status bit position    */
#define WDOG_MASKINTSTAT_Pos 0       /* Masked Interrupt Status bit position */
#define WDOG_ITCR_INTEGTESTEN_Pos 0  /* Integration Test Mode bit position   */
#define WDOG_ITOP_WDOGRES_Pos 0      /* ITOP WDOGRES bit position            */
#define WDOG_ITOP_WDOGINT_Pos 1      /* ITOP WDOGINT bit position            */

extern ErrorStatus WDOG_Init(WDOG_InitTypeDef* WDOG_InitStruct);
extern void WDOG_RestartCounter(uint32_t reload);
extern uint32_t WDOG_GetCounterValue(void);
extern void WDOG_SetResetEnable(void);
extern FlagStatus WDOG_GetResStatus(void);
extern void WDOG_SetIntEnable(void);
extern FlagStatus WDOG_GetIntStatus(void);
extern void WDOG_ClrIntEnable(void);
extern FlagStatus WDOG_GetRawIntStatus(void);
extern FlagStatus WDOG_GetMaskIntStatus(void);
extern void WDOG_LockWriteAccess(void);
extern void WDOG_UnlockWriteAccess(void);
extern void WDOG_SetITModeEnable(void);
extern void WDOG_ClrITModeEnable(void);
extern FlagStatus WDOG_GetITModeStatus(void);
extern void WDOG_SetITOP(uint32_t itop);
extern FlagStatus WDOG_GetITOPResStatus(void);
extern FlagStatus WDOG_GetITOPIntStatus(void);
extern void WDOG_ClrITOP(uint32_t itop);

#ifdef __cplusplus
}
#endif

#endif  /* PANGO_M1_WDOG_H */


