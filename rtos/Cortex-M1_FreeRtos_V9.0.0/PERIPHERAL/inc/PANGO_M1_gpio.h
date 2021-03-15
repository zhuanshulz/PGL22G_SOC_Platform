#ifndef PANGO_M1_GPIO_H
#define PANGO_M1_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "PANGO_M1.h"

typedef enum
{
  GPIO_Mode_IN = 0,  /* GPIO input */
  GPIO_Mode_OUT,     /* GPIO output */
  GPIO_Mode_AF       /* GPIO alternate function */
}GPIOMode_TypeDef;

typedef enum
{
  GPIO_Int_Disable = 0,    /* Disable : Interrupt enable=0 */
  GPIO_Int_Low_Level,      /* Low-level : Interrupt enable=1 */
  GPIO_Int_High_Level,     /* High-level : Interrupt enable=1 & polarity=1 */
  GPIO_Int_Falling_Edge,   /* Fallig edge : Interrupt enable=1 & type=1 */
  GPIO_Int_Rising_Edge     /* Rising edge : Interrupt enable=1 & polarity=1 & type=1 */
}GPIOInt_TypeDef;

typedef struct
{
  uint32_t GPIO_Pin;           /* GPIO pin definition */

  GPIOMode_TypeDef GPIO_Mode;  /* GPIO mode */

  GPIOInt_TypeDef  GPIO_Int;   /* GPIO interrupt */
  
}GPIO_InitTypeDef;

#define GPIO_Pin_0                 ((uint32_t)0x00000001)  /*!< Pin 0 selected */
#define GPIO_Pin_1                 ((uint32_t)0x00000002)  /*!< Pin 1 selected */
#define GPIO_Pin_2                 ((uint32_t)0x00000004)  /*!< Pin 2 selected */
#define GPIO_Pin_3                 ((uint32_t)0x00000008)  /*!< Pin 3 selected */
#define GPIO_Pin_4                 ((uint32_t)0x00000010)  /*!< Pin 4 selected */
#define GPIO_Pin_5                 ((uint32_t)0x00000020)  /*!< Pin 5 selected */
#define GPIO_Pin_6                 ((uint32_t)0x00000040)  /*!< Pin 6 selected */
#define GPIO_Pin_7                 ((uint32_t)0x00000080)  /*!< Pin 7 selected */
#define GPIO_Pin_8                 ((uint32_t)0x00000100)  /*!< Pin 8 selected */
#define GPIO_Pin_9                 ((uint32_t)0x00000200)  /*!< Pin 9 selected */
#define GPIO_Pin_10                ((uint32_t)0x00000400)  /*!< Pin 10 selected */
#define GPIO_Pin_11                ((uint32_t)0x00000800)  /*!< Pin 11 selected */
#define GPIO_Pin_12                ((uint32_t)0x00001000)  /*!< Pin 12 selected */
#define GPIO_Pin_13                ((uint32_t)0x00002000)  /*!< Pin 13 selected */
#define GPIO_Pin_14                ((uint32_t)0x00004000)  /*!< Pin 14 selected */
#define GPIO_Pin_15                ((uint32_t)0x00008000)  /*!< Pin 15 selected */
#define GPIO_Pin_All               ((uint32_t)0x0000FFFF)  /*!< All pins selected */

extern void GPIO_Init(GPIO_TypeDef* GPIOx,GPIO_InitTypeDef* GPIO_InitStruct);
extern void GPIO_SetOutEnable(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin);
extern void GPIO_ClrOutEnable(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin);
extern uint32_t GPIO_GetOutEnable(GPIO_TypeDef* GPIOx);
extern void GPIO_SetBit(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin);
extern void GPIO_ResetBit(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin);
extern void GPIO_WriteBits(GPIO_TypeDef* GPIOx,uint32_t value);
extern uint32_t GPIO_ReadBits(GPIO_TypeDef* GPIOx);
extern void GPIO_SetAltFunc(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin);
extern void GPIO_ClrAltFunc(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin);
extern uint32_t GPIO_GetAltFunc(GPIO_TypeDef* GPIOx);
extern void GPIO_IntClear(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin);
extern uint32_t GPIO_GetIntStatus(GPIO_TypeDef* GPIOx);
extern uint32_t GPIO_SetIntEnable(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin);
extern uint32_t GPIO_ClrIntEnable(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin);
extern void GPIO_SetIntHighLevel(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin);
extern void GPIO_SetIntRisingEdge(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin);
extern void GPIO_SetIntLowLevel(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin);
extern void GPIO_SetIntFallingEdge(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin);
extern void GPIO_MaskedWrite(GPIO_TypeDef* GPIOx,uint32_t value,uint32_t mask);

#ifdef __cplusplus
}
#endif

#endif  /* PANGO_M1_GPIO_H */
