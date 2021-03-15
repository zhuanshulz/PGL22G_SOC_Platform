/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2019 PANGO 
 * 		
 * @file		PANGO_M1_it.h
 * @author		Embedded Development Team
 * @version		V1.0.0
 * @date		2019-09-09 09:09:09
 * @brief		This file contains the headers of the interrupt handlers.
 ******************************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PANGO_M1_IT_H
#define PANGO_M1_IT_H

#ifdef __cplusplus
	extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "PANGO_M1.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

/* Core Exceptions Handler */
void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

/* StdPeriph Interrupts Handler */
void UART0_Handler(void);
void UART1_Handler(void);
void TIMER0_Handler(void);
void TIMER1_Handler(void);
void GPIO0_Handler(void);
void RTC_Handler(void);
void I2C_Handler(void);
void CAN_Handler(void);
void ENT_Handler(void);
void DTimer_Handler(void);
void TRNG_Handler(void);
#ifdef __cplusplus
}
#endif

#endif /* PANGO_M1_IT_H */

