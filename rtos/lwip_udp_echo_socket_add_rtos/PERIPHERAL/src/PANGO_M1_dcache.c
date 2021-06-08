/*
 * *****************************************************************************************		
 * 文件名称：PANGO_M1_dcache.c
 * 功能描述：DCACHE固件库函数
 ******************************************************************************************
 */

#include "PANGO_M1_dcache.h"

/********************************************************************
** 函数名称：DCACHE_Invalidate
** 函数功能：设置DCACHE刷新控制
** 输入参数：无
** 输出参数：无
** 返回参数：无
********************************************************************/
void DCACHE_Invalidate(void)
{
	DCACHE_InvalidateRange(DCACHE_RAM_START_ADD, DCACHE_MAP_MAX_SIZE);
}

/********************************************************************
** 函数名称：DCACHE_InvalidateRange
** 函数功能：设置ICACHE刷新指定段数据
** 输入参数：addr：指定刷新起始地址
**			 len：指定刷新数据长度	
** 输出参数：无
** 返回参数：无
********************************************************************/
void DCACHE_InvalidateRange(uint32_t addr, uint32_t len)
{
	DCACHE->START_ADDR = addr;
	DCACHE->LEN = len;
	DCACHE->CTRL = DCACHE_CTR_INVALIDATE;
	while(DCACHE_GetInvalidateStatus() == 1);
	DCACHE->STATUS = DCACHE_SR_INVALI_DONE;
}

/********************************************************************
** 函数名称：DCACHE_Flush
** 函数功能：设置DCACHE回写控制
** 输入参数：无
** 输出参数：无
** 返回参数：无
********************************************************************/
void DCACHE_Flush(void)
{
	DCACHE_FlushRange(DCACHE_RAM_START_ADD, DCACHE_MAP_MAX_SIZE);
}

/********************************************************************
** 函数名称：DCACHE_FlushRange
** 函数功能：设置DCACHE指定段数据回写控制
** 输入参数：addr：指定回写起始地址
**			 len：指定回写数据长度
** 输出参数：无
** 返回参数：无
********************************************************************/
void DCACHE_FlushRange(uint32_t addr, uint32_t len)
{
	DCACHE->START_ADDR = addr;
	DCACHE->LEN = len;
	DCACHE->CTRL = DCACHE_CTR_FLUSH;
	while(DCACHE_GetFlushStatus() == 1);
	DCACHE->STATUS = DCACHE_SR_FLUSH_DONE;
}

/********************************************************************
** 函数名称：DCACHE_GetInvalidateStatus
** 函数功能：DCACHE刷新完成状态检测
** 输入参数：无
** 输出参数：无
** 返回参数：DCACHE状态寄存器检测
********************************************************************/
FlagStatus DCACHE_GetInvalidateStatus(void)
{
	return (FlagStatus)((DCACHE->STATUS & DCACHE_SR_INVALIDATE) == DCACHE_SR_INVALIDATE);
}

/********************************************************************
** 函数名称：DCACHE_GetFlushStatus
** 函数功能：DCACHE回写完成状态检测
** 输入参数：无
** 输出参数：无
** 返回参数：DCACHE状态寄存器检测
********************************************************************/
FlagStatus DCACHE_GetFlushStatus(void)
{
	return (FlagStatus)((DCACHE->STATUS & DCACHE_SR_FLUSH) == DCACHE_SR_FLUSH);
}

