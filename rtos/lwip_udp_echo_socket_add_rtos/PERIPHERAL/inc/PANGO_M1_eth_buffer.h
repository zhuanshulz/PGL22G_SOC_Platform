#ifndef PANGO_M1_ETH_BUFFER_H
#define PANGO_M1_ETH_BUFFER_H

#ifdef __cplusplus
 extern "C" {
#endif
#include <stdbool.h>
#include "PANGO_M1.h"

#define DESCRIPTOR_BUF_SIZE 			1600						/* 描述符(TX/RX)缓存区大小 */
#define DESCRIPTOR_TX_BUF_CNT 			2							/* TX描述符个数 */
#define DESCRIPTOR_RX_BUF_CNT 			32							/* RX描述符个数 */
#define DESCRIPTOR_TX_BUF_BASE 			0x30000000					/* TX描述符缓存区基地址 */
#define DESCRIPTOR_RX_BUF_BASE 			(DESCRIPTOR_TX_BUF_BASE + DESCRIPTOR_TX_BUF_CNT*BUF_BOUNDARY_SIZE)/* RX描述符缓存区基地址 */
#define BUF_BOUNDARY_SIZE 				4*1024						/* 4K边界大小 */
	 
typedef struct 	_DESCRIPTOR_BUF_
{
	char *data_buf;													/* 描述符缓存区 */
	int data_len;													/* 数据长度 */
	bool data_state;												/* 数据可操状态标志 */
	bool data_error;												/* 数据出错标志 */
}DESCRIPTOR_BUF;

typedef struct 	_CURRENT_DESCRIPTOR_NUM_
{
	int buf_size;													/* 描述符缓存区大小 */
	int max_tx_num;													/* TX描述符最大编号 */
	int max_rx_num;													/* RX描述符最大编号 */
	int tx_num;														/* 当前可操作的TX描述符号 */
	int rx_num;														/* 当前可操作的RX描述符号 */
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


