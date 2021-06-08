#ifndef PANGO_M1_ETH_DMAC_H
#define PANGO_M1_ETH_DMAC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "PANGO_M1.h"

#define DESCRIPTOR_RX_INIT   			((uint32_t)0x00008000)  /* ���ƼĴ��� : bit[15]         		*/
#define DESCRIPTOR_TX_INIT   			((uint32_t)0x00020000)  /* ���ƼĴ��� : bit[17]         		*/
#define DMAC0_RX_INIT   				((uint32_t)0x00000001)  /* ���ƼĴ��� : bit[0]         			*/
#define DMAC0_TX_INIT   				((uint32_t)0x00000002)  /* ���ƼĴ��� : bit[1]         			*/
#define DMAC0_RX_CTRL   				((uint32_t)0x00000004)  /* ���ƼĴ��� : bit[2]         			*/
#define DMAC0_TX_CTRL   				((uint32_t)0x00000008)  /* ���ƼĴ��� : bit[3]         			*/
#define DMAC0_RXIRQ_ENABLE   			((uint32_t)0x00000001)  /* �жϿ��ƼĴ���: ʹ�ܽ����ж� 		*/
#define DMAC0_RXIRQ_DISABLE   			((uint32_t)0x00000000)  /* �жϿ��ƼĴ���: ʧ�ܽ����ж� 		*/
#define DMAC0_STATUS_RX_IDLE			((uint32_t)0x00000001)  /* ���տ���״̬�Ĵ���: ��ȡRX IDLE״̬�Ĵ���bit[0]  */
#define DMAC0_STATUS_TX_IDLE			((uint32_t)0x00000002)  /* ���Ϳ���״̬�Ĵ���: ��ȡTX IDLE״̬�Ĵ���bit[1]  */
#define DMAC0_STATUS_INIT_DONE			((uint32_t)0x00000004)  /* ��ʼ�����״̬�Ĵ���bit[2]  */
#define DMAC0_INTSTATUS_AXI_IRQ 		((uint32_t)0x00000001)  /* �ж�״̬�Ĵ���: ��ȡAXI�ж�״̬�Ĵ���  	*/
#define DMAC0_INTCLEAR_AXI_IRQ  		((uint32_t)0x00000001)  /* �ж�״̬�Ĵ���: ���AXI�ж�״̬�Ĵ���   */
#define DMAC0_INTSTATUS_RXIRQ   		((uint32_t)0x00000002)  /* �ж�״̬�Ĵ���: ��ȡRX�ж�״̬�Ĵ���  	*/
#define DMAC0_INTCLEAR_RXIRQ    		((uint32_t)0x00000002)  /* �ж�״̬�Ĵ���: ���RX�ж�״̬�Ĵ���   */

#define DMAC0_INTSTATUS_AXI_IRQ_Pos    	0  						/* �ж�״̬�Ĵ���: AXI_IRQ Position  */
#define DMAC0_INTSTATUS_RXIRQ_Pos    	1  						/* �ж�״̬�Ĵ���: RXIRQ Position  */

#define TS_MAC_TX_RX					(*(__O uint32_t*)(APB1PERIPH_BASE + 0xC000))	/* TS_MAC�շ����ƼĴ�����ַ   */
#define TS_MAC_CONFIG					(*(__O uint32_t*)(APB1PERIPH_BASE + 0xC010))	/* TS_MAC���üĴ�����ַ   */
#define TS_MAC_ADD_FILTER				(*(__O uint32_t*)(APB1PERIPH_BASE + 0xC120))	/* TS_MAC��ַ���˼Ĵ�����ַ   */
#define TS_MAC_ADD0						(*(__O uint32_t*)(APB1PERIPH_BASE + 0xC130))	/* TS_MAC MAC��ַ0�Ĵ�����ַ   */
#define TS_MAC_ADD1						(*(__O uint32_t*)(APB1PERIPH_BASE + 0xC140))	/* TS_MAC MAC��ַ1�Ĵ�����ַ   */

#define TS_MAC_TX_RX_DATA				((uint32_t)0x00000035)	/* TS_MAC�շ����ƼĴ���ֵ   */
#define TS_MAC_CONFIG_DATA				((uint32_t)0x00007217)	/* TS_MAC���üĴ���ֵ   */
#define TS_MAC_ADD_FILTER_DATA			((uint32_t)0x00000480)	/* TS_MAC��ַ���˼Ĵ���ֵ   */

typedef struct _ETH_Handle_										/* ETHӲ���ṹ����Ϣ */
{
	uint32_t dmac_ctrl;											/* dmac�����ź� */
	uint32_t priority;											/* dmac�ж����ȼ� */
	uint32_t AutoNegotiation;           						/* ��Э��ģʽѡ�� */
	uint32_t Speed;                     						/* �����ٶ�����10/100/1000M */
	uint32_t DuplexMode;                						/* ����ģʽѡ��ȫ˫��/��˫�� */
	uint16_t PhyAddress;                						/* RHY��ַ��0-32 */
	uint8_t  MACAddr[6];                   						/* ����MAC��ַ��6���ֽڣ� */
	uint32_t ChecksumMode;              						/* У���ѡ���Ƿ��Ӳ��У��� */
	uint32_t MediaInterface;               						/* Ӳ���ӿ�ѡ��MII/GMII ����RGMII */
}ETH_Handle;


extern ErrorStatus DMAC_Init(DMAC0_TypeDef * DMAC_x, ETH_Handle *heth);
extern void SetTxDescriptor(DMAC0_TypeDef * DMAC_x, int num, int link_num, uint32_t addr, int size);
extern void SetRxDescriptor(DMAC0_TypeDef * DMAC_x, int num, int link_num, uint32_t addr, int size);
extern uint32_t	GetCurrentTxDescriptorNum(DMAC0_TypeDef * DMAC_x);
extern uint32_t	GetCurrentRxDescriptorNum(DMAC0_TypeDef * DMAC_x);
extern void	SetTxDataLen(DMAC0_TypeDef * DMAC_x, int lenght);
extern uint32_t	GetRxDataLen(DMAC0_TypeDef * DMAC_x);
extern void	CleanRxDescriptorNum(DMAC0_TypeDef * DMAC_x, int num);
extern void	SetDmacTxCtrl(DMAC0_TypeDef * DMAC_x);
extern void	SetDmacRxCtrl(DMAC0_TypeDef * DMAC_x);
extern FlagStatus DMAC_GetRxIdleStatus(DMAC0_TypeDef* DMAC_x);
extern FlagStatus DMAC_GetTxIdleStatus(DMAC0_TypeDef* DMAC_x);
extern ITStatus DMAC_GetAxiIRQStatus(DMAC0_TypeDef* DMAC_x);
extern void DMAC_ClearAxiIRQ(DMAC0_TypeDef* DMAC_x);
extern ITStatus DMAC_GetRxIRQStatus(DMAC0_TypeDef* DMAC_x);
extern void DMAC_SetInitStatus(DMAC0_TypeDef* DMAC_x, uint32_t data);
extern void DMAC_ClearRxIRQ(DMAC0_TypeDef* DMAC_x);
extern void TS_MAC_Configure(uint8_t *mac);
#ifdef __cplusplus
}
#endif

#endif  /* PANGO_M1_ETH_DMAC_H */


