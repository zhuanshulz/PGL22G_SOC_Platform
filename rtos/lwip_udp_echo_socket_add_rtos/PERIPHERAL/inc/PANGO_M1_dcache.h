#ifndef PANGO_M1_DCACHE_H
#define PANGO_M1_DCACHE_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "PANGO_M1.h"

#define DCACHE_DDR_START_ADD	((uint32_t)0x01000000)	/* DCACHE DDR��ʼ��ַ */
#define DCACHE_RAM_START_ADD	((uint32_t)0x30000000)	/* DCACHE RAM��ʼ��ַ */
#define DCACHE_MAP_MAX_SIZE	 	((uint32_t)0x10000000)	/* DCACHE ӳ�䷶Χ */
#define DCACHE_CTR_INVALIDATE  	((uint32_t)0x00000001)  /* DCACH ˢ�¿���λbit[0]	 */
#define DCACHE_CTR_FLUSH  		((uint32_t)0x00000002)  /* DCACH ��д����λbit[1]	 */
#define DCACHE_SR_INVALIDATE   	((uint32_t)0x00000001)	/* DCACH ˢ�����bit[0]	 */
#define DCACHE_SR_FLUSH    		((uint32_t)0x00000002)	/* DCACH ��д���bit[1]	 */
#define DCACHE_SR_INVALI_DONE  	((uint32_t)0x00000040)  /* DCACH ˢ�²������״̬λbit[6]	 */	 
#define DCACHE_SR_FLUSH_DONE  	((uint32_t)0x00000080)  /* DCACH ��д�������״̬λbit[7]	 */	 

extern void DCACHE_Invalidate(void);	 
extern void DCACHE_InvalidateRange(uint32_t addr, uint32_t len);
extern void DCACHE_Flush(void);
extern void DCACHE_FlushRange(uint32_t addr, uint32_t len);
extern FlagStatus DCACHE_GetInvalidateStatus(void);
extern FlagStatus DCACHE_GetFlushStatus(void);
#ifdef __cplusplus
}
#endif

#endif  /* PANGO_M1_DCACHE_H */


