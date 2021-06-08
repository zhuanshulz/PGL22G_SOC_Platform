/*
 * Copyright (c) 2017 Simon Goldschmidt
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Simon Goldschmidt
 *
 */
 
#include <lwip/opt.h>
#include <lwip/arch.h>
#include "lwip/tcpip.h"

 /* FreeRTOSÍ·ÎÄ¼þ */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define MAC_ADDR0   			0x60U
#define MAC_ADDR1   			0x50U
#define MAC_ADDR2   			0x40U
#define MAC_ADDR3   			0x30U
#define MAC_ADDR4   			0x20U
#define MAC_ADDR5   			0x10U


#define DEST_IP_ADDR0   		192U
#define DEST_IP_ADDR1   		168U
#define DEST_IP_ADDR2   		0U
#define DEST_IP_ADDR3   		3U

#define DEST_PORT       		5001U
 
/*Static IP ADDRESS: IP_ADDR0.IP_ADDR1.IP_ADDR2.IP_ADDR3 */
#define IP_ADDR0   				192U
#define IP_ADDR1    			168U
#define IP_ADDR2    			0U
#define IP_ADDR3    			2U
   
/*NETMASK*/
#define NETMASK_ADDR0   		255U
#define NETMASK_ADDR1    		255U
#define NETMASK_ADDR2    		255U
#define NETMASK_ADDR3    		0U

/*Gateway Address*/
#define GW_ADDR0    			192U
#define GW_ADDR1    			168U
#define GW_ADDR2    			0U
#define GW_ADDR3    			1U

#define SYS_MBOX_NULL  (QueueHandle_t)0
#define SYS_SEM_NULL   (SemaphoreHandle_t)0
#define SYS_MRTEX_NULL SYS_SEM_NULL
#define SYS_DEFAULT_THREAD_STACK_DEPTH	configMINIMAL_STACK_SIZE

typedef SemaphoreHandle_t sys_sem_t;
typedef SemaphoreHandle_t sys_mutex_t;
typedef QueueHandle_t sys_mbox_t;
typedef TaskHandle_t sys_thread_t;

typedef int sys_prot_t;



void TCPIP_Init(void);

