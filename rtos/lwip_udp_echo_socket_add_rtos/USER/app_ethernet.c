/**
  ******************************************************************************
  * @file    LwIP/LwIP_TCP_Echo_Client/Src/app_ethernet.c 
  * @author  MCD Application Team
  * @brief   Ethernet specefic module
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
#include "lwip/dhcp.h"
#include "app_ethernet.h"
#include "ethernetif.h"
#include "netif/etharp.h"

struct netif gnetif;

/********************************************************************
 ** �������ƣ�Netif_Config
 ** �������ܣ���������ӿ�
 ** �����������
 ** �����������
 ** ���ز�������
 ********************************************************************/
void Netif_Config(void)
{
	ip_addr_t ipaddr;
	ip_addr_t netmask;
	ip_addr_t gw;

	IP_ADDR4(&ipaddr,IP_ADDR0,IP_ADDR1,IP_ADDR2,IP_ADDR3);
	IP_ADDR4(&netmask,NETMASK_ADDR0,NETMASK_ADDR1,NETMASK_ADDR2,NETMASK_ADDR3);
	IP_ADDR4(&gw,GW_ADDR0,GW_ADDR1,GW_ADDR2,GW_ADDR3);

	netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ethernet_input);	/* �������ӿ� */  

	netif_set_default(&gnetif);																/* ע��Ĭ������ӿ� */

	if (netif_is_link_up(&gnetif))
	{
		netif_set_up(&gnetif);																/* ��netif��ȫ����ʱ��������ô˺��� */
	}
	else
	{		
		netif_set_down(&gnetif);															/* ��netif���ӶϿ�ʱ��������ô˺��� */
	}
}

/********************************************************************
 ** �������ƣ�User_notification
 ** �������ܣ�֪ͨ�û��й�����ӿ�����״̬
 ** ���������netif: ����ӿ�
 ** �����������
 ** ���ز�������
 ********************************************************************/
void User_notification(struct netif *netif) 
{
	if (netif_is_up(netif))
	{
		DEBUG_P("Static IP: %d.%d.%d.%d\n",IP_ADDR0,IP_ADDR1,IP_ADDR2,IP_ADDR3);
		DEBUG_P("NETMASK  : %d.%d.%d.%d\n",NETMASK_ADDR0,NETMASK_ADDR1,NETMASK_ADDR2,NETMASK_ADDR3);
		DEBUG_P("Gateway  : %d.%d.%d.%d\n",GW_ADDR0,GW_ADDR1,GW_ADDR2,GW_ADDR3);
	}
	else
	{
		DEBUG_P ("The network cable is not connected \n");
	}
}
