/*
 * *****************************************************************************************		
 * �ļ����ƣ�PANGO_M1_udp_speed_up.c
 * ����������UDPӲ�����ٽӿں���
 ******************************************************************************************
 */

#include "PANGO_M1_udp_speed_up.h"
#include <string.h>

/********************************************************************
** �������ƣ�SetUdpSpeedUpStatus
** �������ܣ�����UDP����״̬�Ĵ���
** ���������data��д��Ĵ���ֵ
** �����������
** ���ز�������
********************************************************************/
void SetUdpSpeedUpStatus(uint32_t data)
{
	UDP_SPEED_UP_STATUS = data;
}

/********************************************************************
** �������ƣ�GetUdpSpeedUpTxBusy
** �������ܣ���ȡUDPӲ������TX���мĴ���״̬
** �����������
** �����������
** ���ز�����FlagStatus��TX����״̬�����
********************************************************************/
FlagStatus GetUdpSpeedUpTxBusy(void)
{
	return (FlagStatus)((UDP_SPEED_UP_STATUS & UDP_SPEED_UP_TX_BUSY) == UDP_SPEED_UP_TX_BUSY);
}

/********************************************************************
** �������ƣ�SetTxStatusON
** �������ܣ������tx����״̬
** ���������info���洢mac��ip�Լ�port�Ľṹ��
** �����������
** ���ز�������
********************************************************************/
void SetTxStatusON(SPEED_UP_INFO* info)
{
	if(1 == info->udp_connect_flag)
	{
		SetUdpSpeedUpStatus(UDP_SOC_CONNECT | UDP_SOC_TX_REQ);
		while(GetUdpSpeedUpTxBusy() == 1);
	}
}

/********************************************************************
** �������ƣ�SetTxStatusOFF
** �������ܣ������tx����״̬
** ���������info���洢mac��ip�Լ�port�Ľṹ��
** �����������
** ���ز�������
********************************************************************/
void SetTxStatusOFF(SPEED_UP_INFO* info)
{
	while(DMAC_GetTxIdleStatus(DMAC0) == 1);								/* �ȴ�TX���� */
	if(1 == info->udp_connect_flag)
	SetUdpSpeedUpStatus(UDP_SOC_CONNECT);
}
/********************************************************************
** �������ƣ�GetDestEthInfo
** �������ܣ���ȡĿ���豸��MAC��ַ��IP��ַ�Լ��˿ں�
** ���������info���洢mac��ip�Լ�port�Ľṹ��
**           data����̫��������
** �����������
** ���ز�������
********************************************************************/
void GetDestEthInfo(SPEED_UP_INFO* info, uint8_t* data)
{
	if(0 == info->udp_connect_flag)
	{
		memcpy(info->dest_mac, data + 6,  6);									/* ��̫��֡MACƫ����λ6 */
		memcpy(info->dest_ip, data  + 26, 4);									/* ��̫��֡IPƫ����λ26 */
		info->dest_port = data[34] << 8 | data[35];								/* ��̫��֡�˿�ƫ����λ34 */
	}
}

/********************************************************************
** �������ƣ�SetSpeedUpInfo
** �������ܣ�����UDP����������Ϣ
** ���������info���洢mac��ip�Լ�port�Ľṹ��
**           source_port�����ض˿ں�
** �����������
** ���ز�������
********************************************************************/
void SetSpeedUpInfo(SPEED_UP_INFO* info, uint32_t source_port)
{
	if(0 == info->udp_connect_flag)
	{
		uint32_t temp_dest_mac_h = 0;
		uint32_t temp_dest_mac_l = 0;
		uint32_t temp_source_mac_h = 0;
		uint32_t temp_source_mac_l = 0;
		uint32_t temp_dest_ip = 0;
		uint32_t temp_source_ip = 0;
		uint32_t temp_port = 0;
		
		temp_dest_mac_h 	= info->dest_mac[0]   << 24 | info->dest_mac[1]   << 16 | info->dest_mac[2]   << 8 | info->dest_mac[3];
		temp_dest_mac_l 	= info->dest_mac[4]   << 24 | info->dest_mac[5]   << 16;
		temp_source_mac_h 	= info->source_mac[0] << 24 | info->source_mac[1] << 16 | info->source_mac[2] << 8 | info->source_mac[3];
		temp_source_mac_l	= info->source_mac[4] << 24 | info->source_mac[5] << 16;
		temp_dest_ip 		= info->dest_ip[0]   << 24 | info->dest_ip[1]   << 16 | info->dest_ip[2]   << 8 | info->dest_ip[3];
		temp_source_ip 		= info->source_ip[0] << 24 | info->source_ip[1] << 16 | info->source_ip[2] << 8 | info->source_ip[3];
		temp_port 			= source_port  << 16 | info->dest_port;

		UDP_PROTOCOL_DEST_MAC_H 	= temp_dest_mac_h;
		UDP_PROTOCOL_DEST_MAC_L 	= temp_dest_mac_l;
		UDP_PROTOCOL_SOURCE_MAC_H 	= temp_source_mac_h;
		UDP_PROTOCOL_SOURCE_MAC_L 	= temp_source_mac_l;
		UDP_PROTOCOL_SOURCE_IP 		= temp_source_ip;
		UDP_PROTOCOL_DEST_IP 		= temp_dest_ip;
		UDP_PROTOCOL_PORT 			= temp_port;
		
		info->udp_connect_flag = 1;
		SetUdpSpeedUpStatus(UDP_SOC_CONNECT);

		DEBUG_P("���MAC �� %x %x %x %x %x %x\n", info->source_mac[0], info->source_mac[1], info->source_mac[2], info->source_mac[3], info->source_mac[4], info->source_mac[5]);
		DEBUG_P("���IP  �� %d.%d.%d.%d\n", info->source_ip[0], info->source_ip[1], info->source_ip[2], info->source_ip[3]);
		DEBUG_P("���PORT�� %d\n\n", source_port);
		DEBUG_P("Ŀ��MAC �� %x %x %x %x %x %x\n", info->dest_mac[0], info->dest_mac[1], info->dest_mac[2], info->dest_mac[3], info->dest_mac[4], info->dest_mac[5]);
		DEBUG_P("Ŀ��IP  �� %d.%d.%d.%d\n", info->dest_ip[0], info->dest_ip[1], info->dest_ip[2], info->dest_ip[3]);
		DEBUG_P("Ŀ��PORT�� %d\n", info->dest_port);
	}
}


