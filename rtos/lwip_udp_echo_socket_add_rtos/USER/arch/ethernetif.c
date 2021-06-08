/**
  ******************************************************************************
  * @file    LwIP/LwIP_TCP_Echo_Client/Src/ethernetif.c
  * @author  MCD Application Team
  * @brief   This file implements Ethernet network interface drivers for lwIP
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "PANGO_M1.h"
#include "lwip/opt.h"
#include "lwip/timeouts.h"
#include "lwip/sys.h"
#include "lwip/etharp.h"
#include "netif/etharp.h"
#include "ethernetif.h"
#include "systick.h"
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Network interface name */
#define IFNAME0 'Z'
#define IFNAME1 'G'

xSemaphoreHandle s_xSemaphore = NULL;		//定义一个信号量，用于任务同步

sys_sem_t tx_sem = NULL;
sys_mbox_t eth_tx_mb = NULL;

ETH_Handle EthHandle;
#if UDP_SPEED_UP
	SPEED_UP_INFO SpeedUpInfo;
#endif

/********************************************************************
 ** 函数名称：low_level_init
 ** 函数功能：在这个函数中初始化硬件，最终被ethernetif_init函数调用
 ** 输入参数：netif：已经初始化了这个以太网的lwip网络接口结构
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
static void low_level_init(struct netif *netif)
{ 
	uint8_t macaddress[6]= {MAC_ADDR0, MAC_ADDR1, MAC_ADDR2, MAC_ADDR3, MAC_ADDR4, MAC_ADDR5};
	
#if UDP_SPEED_UP
	uint8_t ipaddress[4]= {IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3};
	SpeedUpInfo.udp_connect_flag = 0;
	memcpy(SpeedUpInfo.source_mac, macaddress, 6);
	memcpy(SpeedUpInfo.source_ip, ipaddress, 4);
#endif
	
	memcpy(EthHandle.MACAddr, macaddress, 6);
	EthHandle.dmac_ctrl = DMAC0_RXIRQ_ENABLE;
	EthHandle.priority = 0;
	if(DMAC_Init(DMAC0, &EthHandle) == SUCCESS)							/* 配置以太网外设 (DMA) */
	{
		netif->flags |= NETIF_FLAG_LINK_UP;								/* 设置netif链接标志 */
	}
	eth_buf_init();														/* 初始化 Tx/Rx 描述符列表：链接模式 */
	
	netif->hwaddr_len = ETHARP_HWADDR_LEN;								/* 设置netif MAC 硬件地址长度 */

	for(int i = 0; i < ETHARP_HWADDR_LEN; i++)
	{
		netif->hwaddr[i] =  macaddress[i];								/* 设置netif MAC 硬件地址 */
	}

	netif->mtu = 1500;													/* 设置netif最大传输单位 */
	
	netif->flags |= NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;			/* 接收广播地址和ARP流量 */
	  
	s_xSemaphore = xSemaphoreCreateCounting(40,0);

	if(sys_sem_new(&tx_sem , 0) == ERR_OK)
	DEBUG_P("sys_sem_new ok\n");

	if(sys_mbox_new(&eth_tx_mb , 50) == ERR_OK)
	DEBUG_P("sys_mbox_new ok\n");

	/* create the task that handles the ETH_MAC */
	sys_thread_new("ETHIN",
			  ethernetif_input,  										/* 任务入口函数 */
			  netif,        	  										/* 任务入口函数参数 */
			  NETIF_IN_TASK_STACK_SIZE,									/* 任务栈大小 */
			  NETIF_IN_TASK_PRIORITY); 									/* 任务的优先级 */
	
}

/********************************************************************
 ** 函数名称：low_level_output
 ** 函数功能：绑定数据包底层发送函数，数据包包含在pbuf里面
 ** 输入参数：netif：已经初始化了这个以太网的lwip网络接口结构
 **			  p：发送数据包
 ** 输出参数：无
 ** 返回参数：发送结果
 ********************************************************************/
static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
	err_t errval;
	struct pbuf *q;
	uint8_t data_buf[DESCRIPTOR_BUF_SIZE];
	uint8_t *buffer = data_buf;
	uint32_t framelength = 0;
	uint32_t bufferoffset = 0;
	uint32_t byteslefttocopy = 0;
	errval = ERR_OK;
	for(q = p; q != NULL; q = q->next)
	{
		byteslefttocopy = q->len;
		memcpy( (uint8_t*)((uint8_t*)buffer + bufferoffset), (uint8_t*)((uint8_t*)q->payload), byteslefttocopy );
		bufferoffset = bufferoffset + byteslefttocopy;
		framelength = framelength + byteslefttocopy;
	}	
#if UDP_SPEED_UP
	SetTxStatusON(&SpeedUpInfo);
#endif	
	eth_tx_data((char*)buffer ,framelength);								/* 发送数据包 */
#if UDP_SPEED_UP
	SetTxStatusOFF(&SpeedUpInfo);
#endif
//	DEBUG_P("OutPut ethernetif.c %d; tx_data_len = %d;\n", __LINE__, framelength);
//	DEBUG_P("[ ");
//	for(int i = 0; i < framelength; i++)
//	{
//		DEBUG_P("%x ", *buffer++);
//	}
//	DEBUG_P("]\n\n");
	return errval;
}

/********************************************************************
 ** 函数名称：low_level_input
 ** 函数功能：绑定数据包底层接收函数，将数据包缓存在pbuf里面
 ** 输入参数：netif：已经初始化了这个以太网的lwip网络接口结构	  
 ** 输出参数：无
 ** 返回参数：p：接收数据包
 ********************************************************************/
static struct pbuf * low_level_input(struct netif *netif)
{
	struct pbuf *p = NULL;
	struct pbuf *q;
	uint16_t len;
	uint8_t *buffer;
	uint32_t bufferoffset = 0;
	uint32_t byteslefttocopy = 0;

	if(true == eth_rx_buf[descriptor_num.rx_num].data_state)				/* 连接符为环形设计，按顺序缓存 */
	{
		len = eth_rx_buf[descriptor_num.rx_num].data_len - 4;				/* 减去后四位校验位 */
		buffer = (uint8_t*)eth_rx_buf[descriptor_num.rx_num].data_buf;
		if (len > 0)
		{
			p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);						/* 从Lwip buffer pool内存池中申请一个pbuf空间 */
		}
		if (p != NULL)
		{
			bufferoffset = 0;
			eth_rx_buf_invalidate(&descriptor_num);
			#if UDP_SPEED_UP
				GetDestEthInfo(&SpeedUpInfo, buffer);
			#endif
			for(q = p; q != NULL; q = q->next)
			{
				byteslefttocopy = q->len;
				memcpy( (uint8_t*)((uint8_t*)q->payload), (uint8_t*)((uint8_t*)buffer + bufferoffset), byteslefttocopy);
				bufferoffset = bufferoffset + byteslefttocopy;
			}
//			DEBUG_P("InPut ethernetif.c  %d; rx_data_len = %d;\n", __LINE__, len);			
//			DEBUG_P("[ ");
//			for(int i = 0; i < bufferoffset; i++)
//			{
//				DEBUG_P("%02x ", *buffer++);
//			}
//			DEBUG_P("]\n\n");
		}
		clear_eth_rx_buf(&descriptor_num);				
	}
	else
	{
		return NULL;
	}
		
	return p;
}

/********************************************************************
 ** 函数名称：ethernetif_input
 ** 函数功能：当数据包准备好从接口读取时，应该调用此函数。
 **			  它使用应该处理来自网络接口的字节的实际接收的函数low_level_input。
 **			  然后确定接收到的分组的类型，并调用适当的输入功能。
 ** 输入参数：netif：以太网的lwip网络接口结构
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void ethernetif_input(void * argument)
{
	struct pbuf *p;
	struct netif *netif = (struct netif *) argument;
	while(1)
	{
		if(xSemaphoreTake( s_xSemaphore, portMAX_DELAY ) == pdTRUE)
		{
			TRY_GET_NEXT_FRAGMENT:
			p = low_level_input(netif);											/* 将接收到的数据放进pbuf缓存 */
			if(p != NULL)														
			{
				if(netif->input(p, netif) != ERR_OK)							/* 调用接收接口函数 */
				{
					LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
					pbuf_free(p);
					p = NULL;
				}
				else
				{
					xSemaphoreTake( s_xSemaphore, 0);
					goto TRY_GET_NEXT_FRAGMENT;
				}
			}
		}
	}
}

/********************************************************************
 ** 函数名称：ethernetif_init
 ** 函数功能：建立网络接口，调用low_level_init()函数初始化网络硬件接口
 ** 输入参数：netif：以太网的lwip网络接口结构
 ** 输出参数：无
 ** 返回参数：初始化结果
 ********************************************************************/
err_t ethernetif_init(struct netif *netif)
{
	struct ethernetif *ethernetif;

	ethernetif = mem_malloc(sizeof(ethernetif));

	if (ethernetif == NULL) {
		DEBUG_P("ethernetif_init: out of memory\n");
		return ERR_MEM;
	}
	LWIP_ASSERT("netif != NULL", (netif != NULL));

	#if LWIP_NETIF_HOSTNAME
	/* Initialize interface hostname */
	netif->hostname = "lwip";
	#endif /* LWIP_NETIF_HOSTNAME */
	netif->state = ethernetif;
	netif->name[0] = IFNAME0;
	netif->name[1] = IFNAME1;
	/* We directly use etharp_output() here to save a function call.
	* You can instead declare your own function an call etharp_output()
	* from it if you have to do some checks before sending (e.g. if link
	* is available...) */
	netif->output = etharp_output;
	netif->linkoutput = low_level_output;

	/* initialize the hardware */
	low_level_init(netif);

	return ERR_OK;
}

/********************************************************************
 ** 函数名称：sys_now
 ** 函数功能：获取当前的ms计数，当LWIP_TIMERS == 1 和 NO_SYS == 1
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：当前的ms计数
 ********************************************************************/
#if NO_SYS
u32_t sys_now(void)
{
	return HAL_GetTick();
}
#endif 

