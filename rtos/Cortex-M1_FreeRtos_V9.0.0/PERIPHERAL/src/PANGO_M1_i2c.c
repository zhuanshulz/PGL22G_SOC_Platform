/*
 * ***************************************************************************************** 		
 * �ļ����ƣ�PANGO_M1_iic.c
 * ����������IIC�̼��⺯��
 ******************************************************************************************
 */

#include "PANGO_M1_i2c.h"

/********************************************************************
** �������ƣ�I2C_Init
** �������ܣ�IIC�˿ڳ�ʼ���������ж�ʹ�ܺ����ʵ�
** ���������I2C_TypeDef��IIC�Ĵ����ṹ��ָ��
**           speed��IIC����
**           irq_en��IIC�ж�ʹ�ܱ�־��0����ֹ�жϣ�1��ʹ���ж�
** �����������
** ���ز�������ʼ�����
********************************************************************/
ErrorStatus I2C_Init(I2C_TypeDef * I2Cx, uint16_t speed, uint8_t irq_en)
{
	uint16_t temp_save;
	
	if(irq_en >= 1)
	{
		I2C_InterruptOpen(I2Cx);
	}
	else
	{
		I2C_InterruptClose(I2Cx);
	}
	I2C_Enable(I2Cx);
	
	temp_save=I2C_Rate_Set(I2Cx,speed);
	
	if((I2Cx->CTR&I2C_CTR_EN)&&(I2Cx->PRER == (uint32_t) (temp_save&I2C_CTR_PERE)))
	{
		return SUCCESS;
	}
	else
	{
		return ERROR;
	}
}

/********************************************************************
** �������ƣ�I2C_UnEnable
** �������ܣ��ر�iic�ӿ�
** ���������I2C_TypeDef��IIC�Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void I2C_UnEnable(I2C_TypeDef * I2Cx)
{
	I2Cx->CTR = ~I2C_CTR_EN;
}

/********************************************************************
** �������ƣ�I2C_Enable
** �������ܣ�ʹ��iic�ӿ�
** ���������I2C_TypeDef��IIC�Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void I2C_Enable(I2C_TypeDef * I2Cx)
{
	I2Cx->CTR |= I2C_CTR_EN ;
}
 
/********************************************************************
** �������ƣ�I2C_Rate_Set
** �������ܣ�����IIC����
** ���������I2C_TypeDef��IIC�Ĵ����ṹ��ָ��
**           Rate��IIC����
** �����������
** ���ز�����ָʾ��ʼ����Ĵ���״̬
********************************************************************/
uint16_t I2C_Rate_Set(I2C_TypeDef * I2Cx,uint16_t Rate)
{
	uint16_t     prescal = 0;

	prescal =    (uint32_t) (SystemCoreClock/(5000*Rate)-1);
	I2Cx->PRER = (prescal&I2C_CTR_PERE);

	return       prescal;
}

/********************************************************************
** �������ƣ�Delay_ms_i2c
** �������ܣ�ms��ʱ
** ���������delay_ms����ʱ����
** �����������
** ���ز�����ָʾ��ʼ����Ĵ���״̬
********************************************************************/
void Delay_ms_i2c(__IO uint32_t delay_ms)
{
	for(delay_ms=delay_ms*32500; delay_ms != 0; delay_ms--);
}
 
/********************************************************************
** �������ƣ�I2C_SendByte
** �������ܣ�ͨ��IIC���߽ӿڷ���һ���ֽ�
** ���������I2C_TypeDef��IIC�Ĵ����ṹ��ָ��
**           slv_address��IIC�ӻ�����ַ
**           data_address��IIC�ӻ����ݵ�ַ
**           data��д����ֽ�����
** �����������
** ���ز�������
********************************************************************/
void I2C_SendByte(I2C_TypeDef *i2c ,uint8_t slv_address,uint8_t data_address,uint8_t data)
{
	i2c->TXR = slv_address | 0;
	i2c->CR = I2C_CMD_STA|I2C_CMD_WR;
	while(i2c->SR&I2C_SR_TIP);												
	while(i2c->SR&I2C_SR_RXACK);											


	i2c->TXR = data_address;	
	i2c->CR = (I2C_CMD_WR);
	while(i2c->SR&I2C_SR_TIP);												
	while(i2c->SR&I2C_SR_RXACK);											
	
	i2c->TXR = data;
	i2c->CR |= (I2C_CMD_STO|I2C_CMD_WR);
	while(i2c->SR&I2C_SR_TIP);												
	while(i2c->SR&I2C_SR_RXACK);											
	while(i2c->SR&I2C_SR_BUSY);
	
	Delay_ms_i2c(3);														
}

/********************************************************************
** �������ƣ�I2C_ReceiveByte
** �������ܣ�ͨ��IIC���߽ӿڶ�ȡһ���ֽ�
** ���������I2C_TypeDef��IIC�Ĵ����ṹ��ָ��
**           slv_address��IIC�ӻ�����ַ
**           data_address��IIC�ӻ����ݵ�ַ
** �����������
** ���ز�������ȡ���ֽ�����
********************************************************************/
uint8_t I2C_ReceiveByte(I2C_TypeDef *i2c ,uint8_t slv_address,uint8_t data_addr)
{
	uint8_t data=0;
	
	i2c->TXR = slv_address | 0;
	i2c->CR = I2C_CMD_STA|I2C_CMD_WR;	
	while(i2c->SR&I2C_SR_TIP);
	while(i2c->SR&I2C_SR_RXACK);										
	
	i2c->TXR = data_addr;
	i2c->CR = I2C_CMD_WR;												
	while(i2c->SR&I2C_SR_TIP);											
	while(i2c->SR&I2C_SR_RXACK);										
	
	i2c->TXR = slv_address | 1;	
	i2c->CR = (I2C_CMD_STA|I2C_CMD_WR);
	while(i2c->SR&I2C_SR_TIP);
	while(i2c->SR&I2C_SR_RXACK);										

	i2c->CR = (I2C_CMD_ACK|I2C_CMD_STO|I2C_CMD_RD);						
	while(i2c->SR&I2C_SR_TIP);
	data = i2c->RXR;
	Delay_ms_i2c(3);
	
    return data;
}

/********************************************************************
** �������ƣ�I2C_SendBytes
** �������ܣ�ͨ��IIC���߽ӿڷ���һ���ַ���
** ���������I2C_TypeDef��IIC�Ĵ����ṹ��ָ��
**           slv_address��IIC�ӻ�����ַ
**           data_address��IIC�ӻ����ݵ�ַ
**           *data��д����ַ�������
**           data_num��д������ݳ���
** �����������
** ���ز�������
********************************************************************/
void I2C_SendBytes(I2C_TypeDef *i2c ,uint8_t slv_address,uint8_t data_start_address,uint8_t *data,int32_t data_num)
{
	int32_t i;
	
	for(i=0;i<data_num;i++)
	{
		I2C_SendByte(i2c,slv_address,data_start_address+i,data[i]);
	}
}

/********************************************************************
** �������ƣ�I2C_ReadBytes
** �������ܣ�ͨ��IIC���߽ӿڶ�ȡһ���ַ���
** ���������I2C_TypeDef��IIC�Ĵ����ṹ��ָ��
**           slv_address��IIC�ӻ�����ַ
**           data_address��IIC�ӻ����ݵ�ַ
**           data_num����ȡ�����ݳ���
** ���������*data����ȡ���ַ�������
** ���ز�������
********************************************************************/
void I2C_ReadBytes(I2C_TypeDef *i2c ,uint8_t slv_address,uint8_t data_start_address,uint8_t *data,int32_t data_num)
{
	int32_t i;
	
	for(i=0;i<data_num;i++)
	{
		data[i]=I2C_ReceiveByte(i2c,slv_address,data_start_address+i);
	}
}

/********************************************************************
** �������ƣ�I2C_InterruptOpen
** �������ܣ���IIC�ж�
** ���������I2C_TypeDef��IIC�Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void I2C_InterruptOpen(I2C_TypeDef * I2Cx)
{
	I2Cx->CTR |= I2C_CTR_IEN;
}

/********************************************************************
** �������ƣ�I2C_InterruptClose
** �������ܣ��ر�IIC�ж�
** ���������I2C_TypeDef��IIC�Ĵ����ṹ��ָ��
** �����������
** ���ز�������
********************************************************************/
void I2C_InterruptClose(I2C_TypeDef * I2Cx)
{
	I2Cx->CTR &= ~I2C_CTR_IEN;
}
