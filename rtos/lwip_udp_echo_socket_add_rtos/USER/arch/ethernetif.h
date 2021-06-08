#ifndef __ETHERNETIF_H__
#define __ETHERNETIF_H__

#include "lwip/sys.h"
#include "lwip/err.h"
#include "lwip/netif.h"

#define DARA_PACKAGE_MIN_SIZE 				( 60 )								/* ²»°üº¬CRC */

#define NETIF_MTU							( 1500 )

#define NETIF_IN_TASK_STACK_SIZE			( 1024*2 )
#define NETIF_IN_TASK_PRIORITY			  	( 4 )

#define NETIF_OUT_TASK_STACK_SIZE			( 1024*2 )
#define NETIF_OUT_TASK_PRIORITY			  	( 4 )

extern xSemaphoreHandle s_xSemaphore;

/* Exported functions ------------------------------------------------------- */
err_t ethernetif_init(struct netif *netif);

void ethernetif_input(void *pParams);
void ethernet_link_check_state(struct netif *netif);

u32_t sys_jiffies(void);
u32_t sys_now(void);

#endif
