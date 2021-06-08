/*
 * *****************************************************************************************		
 * �ļ����ƣ�PANGO_M1_gpio.c
 * ����������GPIO�̼��⺯��
 ******************************************************************************************
 */

#include "PANGO_M1_gpio.h"

/********************************************************************
** �������ƣ�GPIO_Init
** �������ܣ�GPIO�˿ڳ�ʼ���������˿�������������Լ��ж�
** ���������GPIO_TypeDef��GPIO�Ĵ����ṹ��ָ��
**           GPIO_InitTypeDef��GPIO��ʼ���˿ڲ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void GPIO_Init(GPIO_TypeDef* GPIOx,GPIO_InitTypeDef* GPIO_InitStruct)
{
	uint32_t GPIO_Pin = GPIO_InitStruct->GPIO_Pin;
	GPIOMode_TypeDef GPIO_Mode = GPIO_InitStruct->GPIO_Mode;
	GPIOInt_TypeDef GPIO_Int = GPIO_InitStruct->GPIO_Int;

	/* ����GPIOģʽ�Ĵ��� */
	if(GPIO_Mode == GPIO_Mode_IN)
	{
		GPIOx->OUTENCLR = GPIO_Pin;
	}
	else if(GPIO_Mode == GPIO_Mode_OUT)
	{
		GPIOx->OUTENSET = GPIO_Pin;
	}
	else if(GPIO_Mode == GPIO_Mode_AF)
	{
		GPIOx->ALTFUNCSET = GPIO_Pin;
	}

	/* ����GPIO�жϼĴ��� */
	if(GPIO_Int == GPIO_Int_Low_Level)
	{
		GPIOx->INTENSET |= GPIO_Pin;
		GPIOx->INTTYPECLR |= GPIO_Pin;
		GPIOx->INTPOLCLR |= GPIO_Pin;
	}
	else if(GPIO_Int == GPIO_Int_High_Level)
	{
		GPIOx->INTENSET |= GPIO_Pin;
		GPIOx->INTTYPECLR |= GPIO_Pin;
		GPIOx->INTPOLSET |= GPIO_Pin;
	}
	else if(GPIO_Int == GPIO_Int_Falling_Edge)
	{
		GPIOx->INTENSET |= GPIO_Pin;
		GPIOx->INTTYPESET |= GPIO_Pin;
		GPIOx->INTPOLCLR |= GPIO_Pin;
	}
	else if(GPIO_Int == GPIO_Int_Rising_Edge)
	{
		GPIOx->INTENSET |= GPIO_Pin;
		GPIOx->INTPOLSET |= GPIO_Pin;
		GPIOx->INTTYPESET |= GPIO_Pin;
	}
}

/********************************************************************
** �������ƣ�GPIO_SetOutEnable
** �������ܣ�����GPIO�˿�Ϊ���ģʽ��������Ӧ��GPIO����Ϊ1����������Ϊ���ģʽ
** ���������GPIO_TypeDef��GPIO�Ĵ����ṹ��ָ��
**           GPIO_Pin��GPIO���ű��
** �����������
** ���ز�������
********************************************************************/
void GPIO_SetOutEnable(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->OUTENSET = GPIO_Pin;
}

/********************************************************************
** �������ƣ�GPIO_ClrOutEnable
** �������ܣ�����GPIO�˿�Ϊ����ģʽ��������Ӧ��GPIO����Ϊ1����������Ϊ����ģʽ
** ���������GPIO_TypeDef��GPIO�Ĵ����ṹ��ָ��
**           GPIO_Pin��GPIO���ű��GPIO_Pin_0-GPIO_Pin_15
** �����������
** ���ز�������
********************************************************************/
void GPIO_ClrOutEnable(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->OUTENCLR = GPIO_Pin;
}

/********************************************************************
** �������ƣ�GPIO_SetBit
** �������ܣ�����GPIO�˿����Ϊ��1�����ߵ�ƽ
** ���������GPIO_TypeDef��GPIO�Ĵ����ṹ��ָ��
**           GPIO_Pin��GPIO���ű��GPIO_Pin_0-GPIO_Pin_15
** �����������
** ���ز�������
********************************************************************/
void GPIO_SetBit(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->DATAOUT |= GPIO_Pin;
}

/********************************************************************
** �������ƣ�GPIO_ResetBit
** �������ܣ�����GPIO�˿����Ϊ��0�����͵�ƽ
** ���������GPIO_TypeDef��GPIO�Ĵ����ṹ��ָ��
**           GPIO_Pin��GPIO���ű��GPIO_Pin_0-GPIO_Pin_15
** �����������
** ���ز�������
********************************************************************/
void GPIO_ResetBit(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->DATAOUT &= ~GPIO_Pin;
}

/********************************************************************
** �������ƣ�GPIO_WriteBits
** �������ܣ�����GPIO�Ķ˿�ֵ����������
** ���������GPIO_TypeDef��GPIO�Ĵ����ṹ��ָ��
**           value����Ҫ����GPIO������ֵ
** �����������
** ���ز�������
********************************************************************/
void GPIO_WriteBits(GPIO_TypeDef* GPIOx,uint32_t value)
{
	GPIOx->DATAOUT = value;
}

/********************************************************************
** �������ƣ�GPIO_ReadBits
** �������ܣ���ȡGPIO�Ķ˿�ֵ��������ȡ
** ���������GPIO_TypeDef��GPIO�Ĵ����ṹ��ָ��
** �����������
** ���ز�����GPIO�˿�ֵ
********************************************************************/
uint32_t GPIO_ReadBits(GPIO_TypeDef* GPIOx)
{
	return GPIOx->DATA; 
}

/********************************************************************
** �������ƣ�GPIO_GetOutEnable
** �������ܣ���ȡGPIO�Ķ˿����ͣ�����������
** ���������GPIO_TypeDef��GPIO�Ĵ����ṹ��ָ��
** �����������
** ���ز�����GPIO�˿����ͣ���1����ʾ�������0����ʾ����
********************************************************************/
uint32_t GPIO_GetOutEnable(GPIO_TypeDef* GPIOx)
{
	return GPIOx->OUTENSET;
}

/********************************************************************
** �������ƣ�GPIO_SetAltFunc
** �������ܣ�ʹ�������滻���ܣ�����Ӧ���ű��λ����Ϊ1�������滻���ܣ�
		  �����������ĵ�1λ����Ϊ1��������1����Ϊ�����滻����
** ���������GPIO_TypeDef��GPIO�Ĵ����ṹ��ָ��
**           GPIO_Pin��GPIO���ű��GPIO_Pin_0-GPIO_Pin_15
** �����������
** ���ز�������
********************************************************************/
void GPIO_SetAltFunc(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->ALTFUNCSET = GPIO_Pin;
}

/********************************************************************
** �������ƣ�GPIO_ClrAltFunc
** �������ܣ���ֹ�����滻���ܣ�����Ӧ���ű��λ����Ϊ1�������滻���ܣ�
		  �����������ĵ�1λ����Ϊ1��������1����Ϊԭʼ���ģʽ
** ���������GPIO_TypeDef��GPIO�Ĵ����ṹ��ָ��
**           GPIO_Pin��GPIO���ű��GPIO_Pin_0-GPIO_Pin_15
** �����������
** ���ز�������
********************************************************************/
void GPIO_ClrAltFunc(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->ALTFUNCCLR = GPIO_Pin;
}

/********************************************************************
** �������ƣ�GPIO_GetAltFunc
** �������ܣ���ȡGPIO�Ķ˿������Ƿ�����Ϊ����������ܻ�ԭʼ�������
** ���������GPIO_TypeDef��GPIO�Ĵ����ṹ��ָ��
** �����������
** ���ز�����GPIO�˿����ͣ���1����ʾ�滻����
********************************************************************/
uint32_t GPIO_GetAltFunc(GPIO_TypeDef* GPIOx)
{
	return GPIOx->ALTFUNCSET;
}

/********************************************************************
** �������ƣ�GPIO_IntClear
** �������ܣ����ָ�����ŵ��жϱ�־
** ���������GPIO_TypeDef��GPIO�Ĵ����ṹ��ָ��
**           GPIO_Pin��GPIO���ű��GPIO_Pin_0-GPIO_Pin_15
** �����������
** ���ز�������
********************************************************************/
void GPIO_IntClear(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->INTCLEAR |= GPIO_Pin;
}

/********************************************************************
** �������ƣ�GPIO_GetIntStatus
** �������ܣ���ȡGPIO���ж�����״̬
** ���������GPIO_TypeDef��GPIO�Ĵ����ṹ��ָ��
** �����������
** ���ز�����GPIO�˿��ж�״̬
********************************************************************/
uint32_t GPIO_GetIntStatus(GPIO_TypeDef* GPIOx)
{
	return GPIOx->INTSTATUS;
}

/********************************************************************
** �������ƣ�GPIO_SetIntEnable
** �������ܣ�ʹ��ָ��GPIO���ж�
** ���������GPIO_TypeDef��GPIO�Ĵ����ṹ��ָ��
**           GPIO_Pin��GPIO���ű��GPIO_Pin_0-GPIO_Pin_15
** �����������
** ���ز�����GPIO�˿����ж�״̬
********************************************************************/
uint32_t GPIO_SetIntEnable(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->INTENSET |= GPIO_Pin;
	return GPIOx->INTENSET;
}

/********************************************************************
** �������ƣ�GPIO_ClrIntEnable
** �������ܣ�����ָ��GPIO���ж�
** ���������GPIO_TypeDef��GPIO�Ĵ����ṹ��ָ��
**           GPIO_Pin��GPIO���ű��GPIO_Pin_0-GPIO_Pin_15
** �����������
** ���ز�����GPIO�˿����ж�״̬
********************************************************************/
uint32_t GPIO_ClrIntEnable(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->INTENCLR |= GPIO_Pin;
	return GPIOx->INTENCLR;
}

/********************************************************************
** �������ƣ�GPIO_SetIntHighLevel
** �������ܣ�����GPIO���ж�Ϊ�ߵ�ƽ����
** ���������GPIO_TypeDef��GPIO�Ĵ����ṹ��ָ��
**           GPIO_Pin��GPIO���ű��GPIO_Pin_0-GPIO_Pin_15
** �����������
** ���ز�������
********************************************************************/
void GPIO_SetIntHighLevel(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->INTENSET |= GPIO_Pin;    /* Set INT Enable bit */
	GPIOx->INTTYPECLR |= GPIO_Pin; /* Clear INT TYPE bit */
	GPIOx->INTPOLSET |= GPIO_Pin;  /* Set INT POLarity bit */
}

/********************************************************************
** �������ƣ�GPIO_SetIntRisingEdge
** �������ܣ�����GPIO���ж�Ϊ�����ش���
** ���������GPIO_TypeDef��GPIO�Ĵ����ṹ��ָ��
**           GPIO_Pin��GPIO���ű��GPIO_Pin_0-GPIO_Pin_15
** �����������
** ���ز�������
********************************************************************/
void GPIO_SetIntRisingEdge(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->INTENSET |= GPIO_Pin;   /* Set INT Enable bit */
	GPIOx->INTTYPESET |= GPIO_Pin; /* Set INT TYPE bit */
	GPIOx->INTPOLSET |= GPIO_Pin;  /* Set INT POLarity bit */
}

/********************************************************************
** �������ƣ�GPIO_SetIntLowLevel
** �������ܣ�����GPIO���ж�Ϊ�͵�ƽ����
** ���������GPIO_TypeDef��GPIO�Ĵ����ṹ��ָ��
**           GPIO_Pin��GPIO���ű��GPIO_Pin_0-GPIO_Pin_15
** �����������
** ���ز�������
********************************************************************/
void GPIO_SetIntLowLevel(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->INTENSET |= GPIO_Pin;    /* Set INT Enable bit */
	GPIOx->INTTYPECLR |= GPIO_Pin;  /* Clear INT TYPE bit */
	GPIOx->INTPOLCLR |= GPIO_Pin;   /* Clear INT POLarity bit */
}

/********************************************************************
** �������ƣ�GPIO_SetIntFallingEdge
** �������ܣ�����GPIO���ж�Ϊ�½��ش���
** ���������GPIO_TypeDef��GPIO�Ĵ����ṹ��ָ��
**           GPIO_Pin��GPIO���ű��GPIO_Pin_0-GPIO_Pin_15
** �����������
** ���ز�������
********************************************************************/
void GPIO_SetIntFallingEdge(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin)
{
	GPIOx->INTENSET |= GPIO_Pin;    /* Set INT Enable bit */
	GPIOx->INTTYPESET |= GPIO_Pin;  /* Set INT TYPE bit */
	GPIOx->INTPOLCLR |= GPIO_Pin;   /* Clear INT POLarity bit */
}

/********************************************************************
** �������ƣ�GPIO_MaskedWrite
** �������ܣ�ʹ���û����������������˿������ָ����ֵ��ִ���������
** ���������GPIO_TypeDef��GPIO�Ĵ����ṹ��ָ��
**           value��GPIO�������ָ���˿ڵ�ֵ
**           mask��GPIO��������˿�����
** �����������
** ���ز�������
********************************************************************/
void GPIO_MaskedWrite(GPIO_TypeDef* GPIOx,uint32_t value,uint32_t mask)
{
	GPIOx->MASKLOWBYTE[0x00FF & mask] = value;
	GPIOx->MASKHIGHBYTE[((0xFF00 & mask) >> 8)] = value;
}

