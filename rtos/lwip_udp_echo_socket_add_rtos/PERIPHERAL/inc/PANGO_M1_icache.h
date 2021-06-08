#ifndef PANGO_M1_ICACHE_H
#define PANGO_M1_ICACHE_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "PANGO_M1.h"

#define ICACHE_CTR_UPDATA  	((uint32_t)0x00000001)  /* ICACH ˢ�¿���λbit[0]	 */
#define ICACHE_SR_READY    	((uint32_t)0x00000001)  /* ICACH DDRд�������bit[0]	 */
#define ICACHE_SR_UPDATA   	((uint32_t)0x00000002)	/* ICACH ˢ�����bit[1]	 */
#define ICACHE_SR_DONE  	((uint32_t)0x00000080)  /* ICACH ������ɿ���λbit[7]	 */

	 
extern void ICACHE_Invalidate(void);
extern FlagStatus ICACHE_GetReadyStatus(void);
extern FlagStatus ICACHE_GetInvalidateStatus(void);
 

#ifdef __cplusplus
}
#endif

#endif  /* PANGO_M1_ICACHE_H */


