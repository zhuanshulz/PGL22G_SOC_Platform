/*
 * *****************************************************************************************		
 * �ļ����ƣ�PANGO_M1_icache.c
 * ����������ICACHE�̼��⺯��
 ******************************************************************************************
 */

#include "PANGO_M1_icache.h"

/********************************************************************
** �������ƣ�ICACHE_Invalidate
** �������ܣ�����ICACHEˢ�¿���
** �����������
** �����������
** ���ز�������
********************************************************************/
void ICACHE_Invalidate(void)
{
	ICACHE->CTRL = ICACHE_CTR_UPDATA;
	while(ICACHE_GetInvalidateStatus() == 1);
	ICACHE->STATUS = ICACHE_SR_DONE;
}

/********************************************************************
** �������ƣ�ICACHE_GetReadyStatus
** �������ܣ���ȡICACHE DDR����д�����״̬
** �����������
** �����������
** ���ز�����ICACHE״̬�Ĵ���ֵ
********************************************************************/
FlagStatus ICACHE_GetReadyStatus(void)
{
	return (FlagStatus)((ICACHE->STATUS & ICACHE_SR_READY) == ICACHE_SR_READY);
}

/********************************************************************
** �������ƣ�ICACHE_GetInvalidateStatus
** �������ܣ���ȡICACHEˢ�����״̬
** �����������
** �����������
** ���ز�����ICACHE״̬�Ĵ���ֵ
********************************************************************/
FlagStatus ICACHE_GetInvalidateStatus(void)
{
	return (FlagStatus)((ICACHE->STATUS & ICACHE_SR_UPDATA) == ICACHE_SR_UPDATA);
}

