#ifndef PANGO_M1_ICACHE_H
#define PANGO_M1_ICACHE_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "PANGO_M1.h"

#define ICACHE_CTR_UPDATA  	((uint32_t)0x00000001)  /* ICACH 刷新控制位bit[0]	 */
#define ICACHE_SR_READY    	((uint32_t)0x00000001)  /* ICACH DDR写数据完成bit[0]	 */
#define ICACHE_SR_UPDATA   	((uint32_t)0x00000002)	/* ICACH 刷新完成bit[1]	 */
#define ICACHE_SR_DONE  	((uint32_t)0x00000080)  /* ICACH 操作完成控制位bit[7]	 */

	 
extern void ICACHE_Invalidate(void);
extern FlagStatus ICACHE_GetReadyStatus(void);
extern FlagStatus ICACHE_GetInvalidateStatus(void);
 

#ifdef __cplusplus
}
#endif

#endif  /* PANGO_M1_ICACHE_H */


