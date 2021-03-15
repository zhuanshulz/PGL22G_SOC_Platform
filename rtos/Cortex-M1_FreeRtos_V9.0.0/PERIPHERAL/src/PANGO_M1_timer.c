/*
 * *****************************************************************************************		
 * �ļ����ƣ�PANGO_M1_timer.c
 * ����������TIMER�̼��⺯��
 ******************************************************************************************
 */

#include "PANGO_M1_timer.h"

/********************************************************************
** �������ƣ�TIMER_Init
** �������ܣ���ʱ���жϼĴ�����ʼ���������ж�ʹ�ܡ��жϴ�����ʽ����������С��
** ���������TIMER_TypeDef��TIMER�Ĵ����ṹ��ָ��
**           TIMER_InitTypeDef��TIMER��ʼ���˿ڲ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void TIMER_Init(TIMER_TypeDef* TIMERx,TIMER_InitTypeDef* TIMER_InitStruct)
{
	TIMERx->CTRL = 0;														  	/* �������мĴ��� */
	TIMERx->VALUE = 0;
	TIMERx->RELOAD = 0;
	TIMERx->INTCLEAR = 0;

	TIMERx->VALUE = TIMER_InitStruct->Reload;									/* ����VALUE�Ĵ��� */  
	TIMERx->RELOAD = TIMER_InitStruct->Reload;									/* ����RELOAD�Ĵ��� */  
	TIMERx->CTRL |= TIMER_CTRL_EN;												/* ʹ�ܶ�ʱ�� */

	if(TIMER_InitStruct->TIMER_Int == ENABLE)									/* �ж��Ƿ���Ҫʹ�ܶ�ʱ���ж� */
	{
		TIMERx->CTRL |= TIMER_CTRL_IRQEN;
	}

	if(TIMER_InitStruct->TIMER_Exti == TIMER_DISABLE)							/* �ж��Ƿ���Ҫ��ֹ�ⲿ������ʱ���ж� */
	{
		TIMERx->CTRL &= ~(TIMER_CTRL_SELEXTEN |TIMER_CTRL_SELEXTEN );			
	}

	if(TIMER_InitStruct->TIMER_Exti == TIMER_EXTI_EN)							/* �ж��Ƿ���Ҫʹ���ⲿ�����ж� */
	{
		TIMERx->CTRL |= TIMER_CTRL_SELEXTEN;									
	}
	else if(TIMER_InitStruct->TIMER_Exti == TIMER_EXTI_CLK)						/* �ж��Ƿ���Ҫ�ڲ�ʱ������ */
	{
		TIMERx->CTRL |= TIMER_CTRL_SELEXTCLK;
	}
}

/********************************************************************
** �������ƣ�TIMER_StartTimer
** �������ܣ�������ʱ���ж�
** ���������TIMER_TypeDef��TIMER�Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void TIMER_StartTimer(TIMER_TypeDef* TIMERx)
{
	TIMERx->CTRL |= TIMER_CTRL_EN;
}

/********************************************************************
** �������ƣ�TIMER_StopTimer
** �������ܣ�ֹͣ��ʱ���ж�
** ���������TIMER_TypeDef��TIMER�Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void TIMER_StopTimer(TIMER_TypeDef* TIMERx)
{
	TIMERx->CTRL &= ~TIMER_CTRL_EN;
}

/********************************************************************
** �������ƣ�TIMER_GetIRQStatus
** �������ܣ���ȡ��ʱ���ж�״̬�Ĵ���ֵ
** ���������TIMER_TypeDef��TIMER�Ĵ����ṹ��ָ��
** �����������
** ���ز������ж�״̬�Ĵ���ֵ
********************************************************************/
ITStatus TIMER_GetIRQStatus(TIMER_TypeDef* TIMERx)
{
	return (ITStatus)(TIMERx->INTSTATUS);
}

/********************************************************************
** �������ƣ�TIMER_ClearIRQ
** �������ܣ������ʱ���ж�
** ���������TIMER_TypeDef��TIMER�Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void TIMER_ClearIRQ(TIMER_TypeDef* TIMERx)
{
	TIMERx->INTCLEAR = TIMER_INTCLEAR;
}

/********************************************************************
** �������ƣ�TIMER_GetReload
** �������ܣ���ȡ��ʱ�����¼���ֵ�����¼���ֵ�Ƕ�ʱ���ڷ�����������õ�ֵ
** ���������TIMER_TypeDef��TIMER�Ĵ����ṹ��ָ��
** �����������
** ���ز�������ʱ�����¼���ֵ
********************************************************************/
uint32_t TIMER_GetReload(TIMER_TypeDef* TIMERx)
{
	return TIMERx->RELOAD;
}

/********************************************************************
** �������ƣ�TIMER_SetReload
** �������ܣ����ö�ʱ�����¼���ֵ�����¼���ֵ�Ƕ�ʱ���ڷ�����������õ�ֵ
** ���������TIMER_TypeDef��TIMER�Ĵ����ṹ��ָ��
**			  value�����¼���ֵ
** �����������
** ���ز�������
********************************************************************/
void TIMER_SetReload(TIMER_TypeDef* TIMERx,uint32_t value)
{
	TIMERx->RELOAD = value;
}

/********************************************************************
** �������ƣ�TIMER_GetValue
** �������ܣ���ȡ��ʱ����ǰ����ֵ
** ���������TIMER_TypeDef��TIMER�Ĵ����ṹ��ָ��
** �����������
** ���ز�������ʱ����ǰ����ֵ
********************************************************************/
uint32_t TIMER_GetValue(TIMER_TypeDef* TIMERx)
{
	return TIMERx->VALUE;
}

/********************************************************************
** �������ƣ�TIMER_SetValue
** �������ܣ����ö�ʱ����ǰ����ֵ
** ���������TIMER_TypeDef��TIMER�Ĵ����ṹ��ָ��
**			  value���¼���ֵ
** �����������
** ���ز�������
********************************************************************/
void TIMER_SetValue(TIMER_TypeDef* TIMERx,uint32_t value)
{
	TIMERx->VALUE = value;
}

/********************************************************************
** �������ƣ�TIMER_EnableIRQ
** �������ܣ�ʹ�ܶ�ʱ���ж�����
** ���������TIMER_TypeDef��TIMER�Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void TIMER_EnableIRQ(TIMER_TypeDef* TIMERx)
{
	TIMERx->CTRL |= TIMER_CTRL_IRQEN;
}

/********************************************************************
** �������ƣ�TIMER_DisableIRQ
** �������ܣ���ֹ��ʱ���ж�����
** ���������TIMER_TypeDef��TIMER�Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void TIMER_DisableIRQ(TIMER_TypeDef* TIMERx)
{
	TIMERx->CTRL &= ~TIMER_CTRL_IRQEN;
}

/********************************************************************
** �������ƣ�TIMER_SelExtEnable
** �������ܣ�ʹ���ⲿ������ʱ���ж�
** ���������TIMER_TypeDef��TIMER�Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void TIMER_SelExtEnable(TIMER_TypeDef *TIMER)
{
	TIMER->CTRL = ~(TIMER_CTRL_SELEXTEN |TIMER_CTRL_SELEXTCLK );
	TIMER->CTRL |= TIMER_CTRL_SELEXTEN;    
}

/********************************************************************
** �������ƣ�TIMER_SelExtClock
** �������ܣ�ѡ���ⲿ���붨ʱ���ж�ʱ��
** ���������TIMER_TypeDef��TIMER�Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void TIMER_SelExtClock(TIMER_TypeDef *TIMER)
{
	TIMER->CTRL = ~(TIMER_CTRL_SELEXTEN |TIMER_CTRL_SELEXTCLK );
	TIMER->CTRL |= TIMER_CTRL_SELEXTCLK;    
}

