/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
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
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
#include "PANGO_M1.h"
#include "tcp_client.h"
#include "lwip/netif.h"
#include "lwip/ip.h"
#include "lwip/tcp.h"
#include "lwip/init.h"
#include "netif/etharp.h"
#include "lwip/udp.h"
#include "lwip/pbuf.h"
#include "lwip/api.h"
#include <lwip/sockets.h>
#include "sys_arch.h"
#include <stdio.h>	
#include <string.h>

/********************************************************************
 ** �������ƣ�client
 ** �������ܣ��ͻ��˽��̴�����
 ** ���������thread_param���¼�����
 ** �����������
 ** ���ز�������
 ********************************************************************/
static void client(void *thread_param)
{
	int sock = -1;
	struct sockaddr_in client_addr;

	ip4_addr_t ipaddr;

	uint8_t send_buf[]= "This is a TCP Client test...\n";

	DEBUG_P("Ŀ��IP��ַ:%d.%d.%d.%d \t �˿ں�:%d\n\n",      \
	DEST_IP_ADDR0,DEST_IP_ADDR1,DEST_IP_ADDR2,DEST_IP_ADDR3,DEST_PORT);

	DEBUG_P("�뽫������λ������ΪTCP Server.��User/arch/sys_arch.h�ļ��н�Ŀ��IP��ַ�޸�Ϊ�������ϵ�IP��ַ\n\n");

	DEBUG_P("�޸Ķ�Ӧ�ĺ궨��:DEST_IP_ADDR0,DEST_IP_ADDR1,DEST_IP_ADDR2,DEST_IP_ADDR3,DEST_PORT\n\n");

	IP4_ADDR(&ipaddr,DEST_IP_ADDR0,DEST_IP_ADDR1,DEST_IP_ADDR2,DEST_IP_ADDR3);
	while(1)
	{
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock < 0)
		{
			DEBUG_P("Socket error\n");
			vTaskDelay(10);
			continue;
		} 

		client_addr.sin_family = AF_INET;      
		client_addr.sin_port = htons(DEST_PORT);   
		client_addr.sin_addr.s_addr = ipaddr.addr;
		memset(&(client_addr.sin_zero), 0, sizeof(client_addr.sin_zero));    

		if (connect(sock, (struct sockaddr *)&client_addr, sizeof(struct sockaddr)) == -1) 
		{
			DEBUG_P("Connect failed!\n");
			closesocket(sock);
			vTaskDelay(10);
			continue;
		}                                           

		DEBUG_P("Connect to server successful!\n");

		while (1)
		{
			if(write(sock,send_buf,sizeof(send_buf)) < 0)
			break;

			vTaskDelay(1000);
		}

		closesocket(sock);
	}
}

/********************************************************************
 ** �������ƣ�client_init
 ** �������ܣ��ͻ��˽��̴�������
 ** �����������
 ** �����������
 ** ���ز�������
 ********************************************************************/
void client_init(void)
{
	sys_thread_new("client", client, NULL, 512, 4);
}
