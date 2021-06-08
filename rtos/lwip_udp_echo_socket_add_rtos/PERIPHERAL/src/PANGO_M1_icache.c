/*
 * *****************************************************************************************		
 * 文件名称：PANGO_M1_icache.c
 * 功能描述：ICACHE固件库函数
 ******************************************************************************************
 */

#include "PANGO_M1_icache.h"

/********************************************************************
** 函数名称：ICACHE_Invalidate
** 函数功能：设置ICACHE刷新控制
** 输入参数：无
** 输出参数：无
** 返回参数：无
********************************************************************/
void ICACHE_Invalidate(void)
{
	ICACHE->CTRL = ICACHE_CTR_UPDATA;
	while(ICACHE_GetInvalidateStatus() == 1);
	ICACHE->STATUS = ICACHE_SR_DONE;
}

/********************************************************************
** 函数名称：ICACHE_GetReadyStatus
** 函数功能：读取ICACHE DDR数据写入完成状态
** 输入参数：无
** 输出参数：无
** 返回参数：ICACHE状态寄存器值
********************************************************************/
FlagStatus ICACHE_GetReadyStatus(void)
{
	return (FlagStatus)((ICACHE->STATUS & ICACHE_SR_READY) == ICACHE_SR_READY);
}

/********************************************************************
** 函数名称：ICACHE_GetInvalidateStatus
** 函数功能：读取ICACHE刷新完成状态
** 输入参数：无
** 输出参数：无
** 返回参数：ICACHE状态寄存器值
********************************************************************/
FlagStatus ICACHE_GetInvalidateStatus(void)
{
	return (FlagStatus)((ICACHE->STATUS & ICACHE_SR_UPDATA) == ICACHE_SR_UPDATA);
}

