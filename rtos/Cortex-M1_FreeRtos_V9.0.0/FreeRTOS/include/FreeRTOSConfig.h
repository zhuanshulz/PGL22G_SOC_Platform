/*
 * FreeRTOS Kernel V10.1.0
 * Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

/* Prevent C code being included by the IAR assembler. */
#ifndef __IASMARM__
	#include <stdint.h>
	extern uint32_t SystemCoreClock;
#endif

#define configUSE_PREEMPTION			1 //使用剥脱型内核
#define configUSE_IDLE_HOOK				0 //使用空闲任务钩子函数
#define configUSE_TICK_HOOK				1 //使用滴答任务钩子函数
#define configCPU_CLOCK_HZ				( SystemCoreClock )//获取CPU频率
#define configTICK_RATE_HZ				( ( TickType_t ) 500 )//节拍频率
#define configMAX_PRIORITIES			( 5 ) //最大任务优先级的数目
#define configMINIMAL_STACK_SIZE		( ( unsigned short ) 60 )//最小任务堆栈分配
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 11000 ) ) //堆大小
#define configMAX_TASK_NAME_LEN			( 5 )//任务名称最大长度
#define configUSE_TRACE_FACILITY		0 //Trace 功能 1-》0
#define configUSE_16_BIT_TICKS			0 //32 bit width
#define configIDLE_SHOULD_YIELD			1 //抢占式下时间片的配置
#define configUSE_MUTEXES				1 //recursive mutex代码使用
#define configQUEUE_REGISTRY_SIZE		8 //依赖调试器识别
#define configCHECK_FOR_STACK_OVERFLOW	2 //是否检测堆栈溢出
#define configUSE_RECURSIVE_MUTEXES		1 //recursive mutex代码使用
#define configUSE_MALLOC_FAILED_HOOK	1 //分配内存失败回调函数
#define configUSE_APPLICATION_TASK_TAG	0 //
#define configUSE_COUNTING_SEMAPHORES	1 //设为 1 则程序中会包含semaphore 相关的代码，设为 0 则忽略相关的代码。
#define configGENERATE_RUN_TIME_STATS	0 //是否产生运行的统计信息 用于调试
#define configUSE_QUEUE_SETS			1 

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 			0    //包含co-routile
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 ) //co-routile优先级数量

/* Software timer definitions. */
#define configUSE_TIMERS				1  //启用软件定时器
#define configTIMER_TASK_PRIORITY		( 2 ) //软件定时器任务的优先级
#define configTIMER_QUEUE_LENGTH		5   //软件定时器用到的命令队列的长度
#define configTIMER_TASK_STACK_DEPTH	( 80 ) //软件定时器需要的堆栈大小

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	1
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1
#define INCLUDE_eTaskGetState			1

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names - or at least those used in the unmodified vector table. */
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler
#define vPortSVCHandler   SVC_Handler

/* Bump up the priority of recmuCONTROLLING_TASK_PRIORITY to prevent false
positive errors being reported considering the priority of other tasks in the
system. */
#define recmuCONTROLLING_TASK_PRIORITY ( configMAX_PRIORITIES - 1 )

#endif /* FREERTOS_CONFIG_H */

