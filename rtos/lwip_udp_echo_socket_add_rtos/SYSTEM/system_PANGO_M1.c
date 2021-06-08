/*
 * *****************************************************************************************
 * �ļ����ƣ�system_PANGO_M1.c
 * ����������ϵͳ��ʼ���̼��⺯��
 ******************************************************************************************
 */

#include "PANGO_M1.h"

/*----------------------------------------------------------------------------
  ����ϵͳʱ��
 *----------------------------------------------------------------------------*/
#define  XTAL            (125000000UL)     	/* ����Ƶ�� */

#define  SYSTEM_CLOCK    (XTAL)       		/* 100MHz  */

uint32_t SystemCoreClock = SYSTEM_CLOCK;  	/* ϵͳ�ں�ʱ�� */

/********************************************************************
** �������ƣ�SystemCoreClockUpdate
** �������ܣ�����ϵͳ�ں�ʱ��
** �����������
** �����������
** ���ز�������
********************************************************************/
void SystemCoreClockUpdate (void)
{
  SystemCoreClock = SYSTEM_CLOCK;
}

/********************************************************************
** �������ƣ�SystemInit
** �������ܣ�ϵͳ��ʼ������
** �����������
** �����������
** ���ز�������
********************************************************************/
void SystemInit (void)
{
	SystemCoreClock = SYSTEM_CLOCK;
		GPIO0->DATA = 0;
	GPIO0->DATAOUT = 0;
	GPIO0->OUTENSET = 0;
	GPIO0->OUTENCLR = 0;
	GPIO0->ALTFUNCSET = 0;
	GPIO0->ALTFUNCCLR = 0;
	GPIO0->INTENSET = 0;
	GPIO0->INTENCLR = 0;
	GPIO0->INTTYPESET = 0;
	GPIO0->INTTYPECLR = 0;
	GPIO0->INTPOLSET = 0;
	GPIO0->INTPOLCLR = 0;
	GPIO0->INTCLEAR = 0;
	for(int pos = 0;pos < 256;pos++)
	{
		GPIO0->MASKLOWBYTE[pos] = 0;
		GPIO0->MASKHIGHBYTE[pos] = 0;
	}
}
