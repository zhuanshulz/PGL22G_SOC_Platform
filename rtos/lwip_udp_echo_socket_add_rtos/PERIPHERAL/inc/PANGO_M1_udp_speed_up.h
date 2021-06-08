#ifndef PANGO_M1_UDP_SPEED_UP_H
#define PANGO_M1_UDP_SPEED_UP_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "PANGO_M1.h"

#define UDP_SPEED_UP					1						/* UDP硬件加速宏定义，0：表示关闭;1：表示打开 */

#define UDP_PROTOCOL_DEST_MAC_H			(*(__O  uint32_t*)(UDP_SPEED_UP_BASE + 0x00))	/* 目标MAC地址前四个字节[31:00] */
#define UDP_PROTOCOL_DEST_MAC_L			(*(__O  uint32_t*)(UDP_SPEED_UP_BASE + 0x04))	/* 目标MAC地址后两个字节[31:16] */
#define UDP_PROTOCOL_SOURCE_MAC_H		(*(__O  uint32_t*)(UDP_SPEED_UP_BASE + 0x08))	/* 源MAC地址前四个字节[31:00 */
#define UDP_PROTOCOL_SOURCE_MAC_L		(*(__O  uint32_t*)(UDP_SPEED_UP_BASE + 0x0C))	/* 源MAC地址后两个字节[31:16] */
#define UDP_PROTOCOL_DEST_IP			(*(__O  uint32_t*)(UDP_SPEED_UP_BASE + 0x10))	/* 目标IP[31:00] */
#define UDP_PROTOCOL_SOURCE_IP			(*(__O  uint32_t*)(UDP_SPEED_UP_BASE + 0x14))	/* 源IP[31:00] */
#define UDP_PROTOCOL_PORT				(*(__O  uint32_t*)(UDP_SPEED_UP_BASE + 0x18))	/* 目标端口：[31:16];源端口：[15:0] */
#define UDP_PROTOCOL_IP_IDENTICATION	(*(__IO uint32_t*)(UDP_SPEED_UP_BASE + 0x1c))	/* IP标识 */
#define UDP_SPEED_UP_STATUS				(*(__IO uint32_t*)(UDP_SPEED_UP_BASE + 0x20))	/* UDP加速状态寄存器 */

#define UDP_SPEED_UP_TX_BUSY			((uint32_t)0x00000001)							/* UDP硬件加速状态寄存器位bit[0] */
#define UDP_SOC_TX_REQ					((uint32_t)0x00000002)							/* UDP软核发送请求状态寄存器位bit[1] */
#define UDP_SOC_CONNECT					((uint32_t)0x00000004)							/* UDP软核连接状态寄存器位bit[2] */


typedef struct _SPEED_UP_INFO_									/* UDP加速配置结构体信息 */
{
	uint8_t dest_mac[6];										/* 目标mac */
	uint8_t source_mac[6];										/* 源mac */
	uint8_t dest_ip[4];											/* 目标ip */
	uint8_t source_ip[4];										/* 源ip */
	uint32_t dest_port;                     					/* 目标端口 */
	uint32_t source_port;                     					/* 源端口 */
	uint8_t udp_connect_flag;									/* udp连接标志	*/
}SPEED_UP_INFO;

extern SPEED_UP_INFO SpeedUpInfo;

extern void SetUdpSpeedUpStatus(uint32_t data);
extern FlagStatus GetUdpSpeedUpTxBusy(void);
extern void SetTxStatusON(SPEED_UP_INFO* info);
extern void SetTxStatusOFF(SPEED_UP_INFO* info);
extern void GetDestEthInfo(SPEED_UP_INFO* info, uint8_t* data);
extern void SetSpeedUpInfo(SPEED_UP_INFO* info, uint32_t source_port);

#ifdef __cplusplus
}
#endif

#endif  /* PANGO_M1_UDP_SPEED_UP_H */


