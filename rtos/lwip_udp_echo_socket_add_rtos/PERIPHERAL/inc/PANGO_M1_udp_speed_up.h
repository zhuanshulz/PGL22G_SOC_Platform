#ifndef PANGO_M1_UDP_SPEED_UP_H
#define PANGO_M1_UDP_SPEED_UP_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "PANGO_M1.h"

#define UDP_SPEED_UP					1						/* UDPӲ�����ٺ궨�壬0����ʾ�ر�;1����ʾ�� */

#define UDP_PROTOCOL_DEST_MAC_H			(*(__O  uint32_t*)(UDP_SPEED_UP_BASE + 0x00))	/* Ŀ��MAC��ַǰ�ĸ��ֽ�[31:00] */
#define UDP_PROTOCOL_DEST_MAC_L			(*(__O  uint32_t*)(UDP_SPEED_UP_BASE + 0x04))	/* Ŀ��MAC��ַ�������ֽ�[31:16] */
#define UDP_PROTOCOL_SOURCE_MAC_H		(*(__O  uint32_t*)(UDP_SPEED_UP_BASE + 0x08))	/* ԴMAC��ַǰ�ĸ��ֽ�[31:00 */
#define UDP_PROTOCOL_SOURCE_MAC_L		(*(__O  uint32_t*)(UDP_SPEED_UP_BASE + 0x0C))	/* ԴMAC��ַ�������ֽ�[31:16] */
#define UDP_PROTOCOL_DEST_IP			(*(__O  uint32_t*)(UDP_SPEED_UP_BASE + 0x10))	/* Ŀ��IP[31:00] */
#define UDP_PROTOCOL_SOURCE_IP			(*(__O  uint32_t*)(UDP_SPEED_UP_BASE + 0x14))	/* ԴIP[31:00] */
#define UDP_PROTOCOL_PORT				(*(__O  uint32_t*)(UDP_SPEED_UP_BASE + 0x18))	/* Ŀ��˿ڣ�[31:16];Դ�˿ڣ�[15:0] */
#define UDP_PROTOCOL_IP_IDENTICATION	(*(__IO uint32_t*)(UDP_SPEED_UP_BASE + 0x1c))	/* IP��ʶ */
#define UDP_SPEED_UP_STATUS				(*(__IO uint32_t*)(UDP_SPEED_UP_BASE + 0x20))	/* UDP����״̬�Ĵ��� */

#define UDP_SPEED_UP_TX_BUSY			((uint32_t)0x00000001)							/* UDPӲ������״̬�Ĵ���λbit[0] */
#define UDP_SOC_TX_REQ					((uint32_t)0x00000002)							/* UDP��˷�������״̬�Ĵ���λbit[1] */
#define UDP_SOC_CONNECT					((uint32_t)0x00000004)							/* UDP�������״̬�Ĵ���λbit[2] */


typedef struct _SPEED_UP_INFO_									/* UDP�������ýṹ����Ϣ */
{
	uint8_t dest_mac[6];										/* Ŀ��mac */
	uint8_t source_mac[6];										/* Դmac */
	uint8_t dest_ip[4];											/* Ŀ��ip */
	uint8_t source_ip[4];										/* Դip */
	uint32_t dest_port;                     					/* Ŀ��˿� */
	uint32_t source_port;                     					/* Դ�˿� */
	uint8_t udp_connect_flag;									/* udp���ӱ�־	*/
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


