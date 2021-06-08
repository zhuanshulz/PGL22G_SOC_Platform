/*
 * *****************************************************************************************		
 * �ļ����ƣ�PANGO_M1_dcache.c
 * ����������DCACHE�̼��⺯��
 ******************************************************************************************
 */

#include "PANGO_M1_dcache.h"

/********************************************************************
** �������ƣ�DCACHE_Invalidate
** �������ܣ�����DCACHEˢ�¿���
** �����������
** �����������
** ���ز�������
********************************************************************/
void DCACHE_Invalidate(void)
{
	DCACHE_InvalidateRange(DCACHE_RAM_START_ADD, DCACHE_MAP_MAX_SIZE);
}

/********************************************************************
** �������ƣ�DCACHE_InvalidateRange
** �������ܣ�����ICACHEˢ��ָ��������
** ���������addr��ָ��ˢ����ʼ��ַ
**			 len��ָ��ˢ�����ݳ���	
** �����������
** ���ز�������
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
** �������ƣ�DCACHE_Flush
** �������ܣ�����DCACHE��д����
** �����������
** �����������
** ���ز�������
********************************************************************/
void DCACHE_Flush(void)
{
	DCACHE_FlushRange(DCACHE_RAM_START_ADD, DCACHE_MAP_MAX_SIZE);
}

/********************************************************************
** �������ƣ�DCACHE_FlushRange
** �������ܣ�����DCACHEָ�������ݻ�д����
** ���������addr��ָ����д��ʼ��ַ
**			 len��ָ����д���ݳ���
** �����������
** ���ز�������
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
** �������ƣ�DCACHE_GetInvalidateStatus
** �������ܣ�DCACHEˢ�����״̬���
** �����������
** �����������
** ���ز�����DCACHE״̬�Ĵ������
********************************************************************/
FlagStatus DCACHE_GetInvalidateStatus(void)
{
	return (FlagStatus)((DCACHE->STATUS & DCACHE_SR_INVALIDATE) == DCACHE_SR_INVALIDATE);
}

/********************************************************************
** �������ƣ�DCACHE_GetFlushStatus
** �������ܣ�DCACHE��д���״̬���
** �����������
** �����������
** ���ز�����DCACHE״̬�Ĵ������
********************************************************************/
FlagStatus DCACHE_GetFlushStatus(void)
{
	return (FlagStatus)((DCACHE->STATUS & DCACHE_SR_FLUSH) == DCACHE_SR_FLUSH);
}

