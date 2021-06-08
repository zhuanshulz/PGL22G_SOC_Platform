#ifndef PANGO_M1_DCACHE_H
#define PANGO_M1_DCACHE_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "PANGO_M1.h"

#define DCACHE_DDR_START_ADD	((uint32_t)0x01000000)	/* DCACHE DDR起始地址 */
#define DCACHE_RAM_START_ADD	((uint32_t)0x30000000)	/* DCACHE RAM起始地址 */
#define DCACHE_MAP_MAX_SIZE	 	((uint32_t)0x10000000)	/* DCACHE 映射范围 */
#define DCACHE_CTR_INVALIDATE  	((uint32_t)0x00000001)  /* DCACH 刷新控制位bit[0]	 */
#define DCACHE_CTR_FLUSH  		((uint32_t)0x00000002)  /* DCACH 回写控制位bit[1]	 */
#define DCACHE_SR_INVALIDATE   	((uint32_t)0x00000001)	/* DCACH 刷新完成bit[0]	 */
#define DCACHE_SR_FLUSH    		((uint32_t)0x00000002)	/* DCACH 回写完成bit[1]	 */
#define DCACHE_SR_INVALI_DONE  	((uint32_t)0x00000040)  /* DCACH 刷新操作完成状态位bit[6]	 */	 
#define DCACHE_SR_FLUSH_DONE  	((uint32_t)0x00000080)  /* DCACH 回写操作完成状态位bit[7]	 */	 

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


