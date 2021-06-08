#ifndef PANGO_M1_ETH_BUFFER_H
#define PANGO_M1_ETH_BUFFER_H

#ifdef __cplusplus
 extern "C" {
#endif
#include <stdbool.h>
#include "PANGO_M1.h"

#define DESCRIPTOR_BUF_SIZE 			1600						/* ������(TX/RX)��������С */
#define DESCRIPTOR_TX_BUF_CNT 			2							/* TX���������� */
#define DESCRIPTOR_RX_BUF_CNT 			32							/* RX���������� */
#define DESCRIPTOR_TX_BUF_BASE 			0x30000000					/* TX����������������ַ */
#define DESCRIPTOR_RX_BUF_BASE 			(DESCRIPTOR_TX_BUF_BASE + DESCRIPTOR_TX_BUF_CNT*BUF_BOUNDARY_SIZE)/* RX����������������ַ */
#define BUF_BOUNDARY_SIZE 				4*1024						/* 4K�߽��С */
	 
typedef struct 	_DESCRIPTOR_BUF_
{
	char *data_buf;													/* ������������ */
	int data_len;													/* ���ݳ��� */
	bool data_state;												/* ���ݿɲ�״̬��־ */
	bool data_error;												/* ���ݳ����־ */
}DESCRIPTOR_BUF;

typedef struct 	_CURRENT_DESCRIPTOR_NUM_
{
	int buf_size;													/* ��������������С */
	int max_tx_num;													/* TX����������� */
	int max_rx_num;													/* RX����������� */
	int tx_num;														/* ��ǰ�ɲ�����TX�������� */
	int rx_num;														/* ��ǰ�ɲ�����RX�������� */
}CURRENT_DESCRIPTOR_NUM;

extern DESCRIPTOR_BUF eth_tx_buf[DESCRIPTOR_TX_BUF_CNT];
extern DESCRIPTOR_BUF eth_rx_buf[DESCRIPTOR_RX_BUF_CNT];
extern CURRENT_DESCRIPTOR_NUM descriptor_num;

extern void eth_buf_init(void);
extern void eth_tx_buf_init(void);
extern void eth_rx_buf_init(void);
extern bool eth_tx_data(char * data, int len);
extern void eth_tx_buf_flush(CURRENT_DESCRIPTOR_NUM * num, int len);
extern void eth_rx_buf_invalidate(CURRENT_DESCRIPTOR_NUM * num);
extern void eth_rx_buf_flush(CURRENT_DESCRIPTOR_NUM * num, int len);
extern void clear_eth_rx_buf(CURRENT_DESCRIPTOR_NUM * num);

#ifdef __cplusplus
}
#endif

#endif  /* PANGO_M1_ETH_BUFFER_H */


