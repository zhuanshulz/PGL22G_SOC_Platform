/*
 * *****************************************************************************************		
 * 文件名称：PANGO_M1_udp_speed_up.c
 * 功能描述：UDP硬件加速接口函数
 ******************************************************************************************
 */

#include "PANGO_M1_udp_speed_up.h"
#include <string.h>

/********************************************************************
** 函数名称：SetUdpSpeedUpStatus
** 函数功能：配置UDP加速状态寄存器
** 输入参数：data：写入寄存器值
** 输出参数：无
** 返回参数：无
********************************************************************/
void SetUdpSpeedUpStatus(uint32_t data)
{
	UDP_SPEED_UP_STATUS = data;
}

/********************************************************************
** 函数名称：GetUdpSpeedUpTxBusy
** 函数功能：获取UDP硬件加速TX空闲寄存器状态
** 输入参数：无
** 输出参数：无
** 返回参数：FlagStatus：TX空闲状态检测结果
********************************************************************/
FlagStatus GetUdpSpeedUpTxBusy(void)
{
	return (FlagStatus)((UDP_SPEED_UP_STATUS & UDP_SPEED_UP_TX_BUSY) == UDP_SPEED_UP_TX_BUSY);
}

/********************************************************************
** 函数名称：SetTxStatusON
** 函数功能：打开软核tx发送状态
** 输入参数：info：存储mac、ip以及port的结构体
** 输出参数：无
** 返回参数：无
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
** 函数名称：SetTxStatusOFF
** 函数功能：打开软核tx发送状态
** 输入参数：info：存储mac、ip以及port的结构体
** 输出参数：无
** 返回参数：无
********************************************************************/
void SetTxStatusOFF(SPEED_UP_INFO* info)
{
	while(DMAC_GetTxIdleStatus(DMAC0) == 1);								/* 等待TX空闲 */
	if(1 == info->udp_connect_flag)
	SetUdpSpeedUpStatus(UDP_SOC_CONNECT);
}
/********************************************************************
** 函数名称：GetDestEthInfo
** 函数功能：获取目标设备的MAC地址、IP地址以及端口号
** 输入参数：info：存储mac、ip以及port的结构体
**           data：以太网包数据
** 输出参数：无
** 返回参数：无
********************************************************************/
void GetDestEthInfo(SPEED_UP_INFO* info, uint8_t* data)
{
	if(0 == info->udp_connect_flag)
	{
		memcpy(info->dest_mac, data + 6,  6);									/* 以太网帧MAC偏移量位6 */
		memcpy(info->dest_ip, data  + 26, 4);									/* 以太网帧IP偏移量位26 */
		info->dest_port = data[34] << 8 | data[35];								/* 以太网帧端口偏移量位34 */
	}
}

/********************************************************************
** 函数名称：SetSpeedUpInfo
** 函数功能：设置UDP加速配置信息
** 输入参数：info：存储mac、ip以及port的结构体
**           source_port：本地端口号
** 输出参数：无
** 返回参数：无
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

		DEBUG_P("软核MAC ： %x %x %x %x %x %x\n", info->source_mac[0], info->source_mac[1], info->source_mac[2], info->source_mac[3], info->source_mac[4], info->source_mac[5]);
		DEBUG_P("软核IP  ： %d.%d.%d.%d\n", info->source_ip[0], info->source_ip[1], info->source_ip[2], info->source_ip[3]);
		DEBUG_P("软核PORT： %d\n\n", source_port);
		DEBUG_P("目标MAC ： %x %x %x %x %x %x\n", info->dest_mac[0], info->dest_mac[1], info->dest_mac[2], info->dest_mac[3], info->dest_mac[4], info->dest_mac[5]);
		DEBUG_P("目标IP  ： %d.%d.%d.%d\n", info->dest_ip[0], info->dest_ip[1], info->dest_ip[2], info->dest_ip[3]);
		DEBUG_P("目标PORT： %d\n", info->dest_port);
	}
}


