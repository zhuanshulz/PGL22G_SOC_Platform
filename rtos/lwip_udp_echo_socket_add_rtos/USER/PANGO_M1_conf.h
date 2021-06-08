/*
 * ***************************************************************************************** 		
 * 文件名称：PANGO_M1_conf.h
 * 功能描述：库函数配置文件
 ******************************************************************************************
 */

#ifndef PANGO_M1_CONF_H
#define PANGO_M1_CONF_H

#include "PANGO_M1_uart.h"			//UART
#include "PANGO_M1_wdog.h"			//WatchDog
#include "PANGO_M1_timer.h"			//Timer
#include "PANGO_M1_spi.h"			//SPI
#include "PANGO_M1_i2c.h"			//I2C
#include "PANGO_M1_gpio.h"			//GPIO
#include "PANGO_M1_printk.h"		//printk
#include "PANGO_spi_flash.h"		//spi flash
#include "PANGO_i2c_eeprom.h"		//iic eeprom
#include "PANGO_M1_memory.h"		//sMemory
#include "PANGO_M1_ddr3.h"			//ddr3
#include "PANGO_ddr3.h"				//ddr3
#include "PANGO_M1_icache.h"		//icache
#include "PANGO_M1_dcache.h"		//dcache
#include "PANGO_M1_eth_dmac.h"		//eth dmac	
#include "PANGO_M1_eth_buffer.h"	//eth buffer
#include "PANGO_M1_udp_speed_up.h"	//udp_speed_up
//#define USE_FULL_ASSERT
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __PANGO_M1_CONF_H */


