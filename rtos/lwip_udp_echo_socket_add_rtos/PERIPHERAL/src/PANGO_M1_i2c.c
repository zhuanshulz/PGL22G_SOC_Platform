/*
 * ***************************************************************************************** 		
 * 文件名称：PANGO_M1_iic.c
 * 功能描述：IIC固件库函数
 ******************************************************************************************
 */

#include "PANGO_M1_i2c.h"

/********************************************************************
** 函数名称：I2C_Init
** 函数功能：IIC端口初始化，包括中断使能和速率等
** 输入参数：I2C_TypeDef：IIC寄存器结构体指针
**           speed：IIC速率
**           irq_en：IIC中断使能标志，0：禁止中断；1：使能中断
** 输出参数：无
** 返回参数：初始化结果
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
** 函数名称：I2C_UnEnable
** 函数功能：关闭iic接口
** 输入参数：I2C_TypeDef：IIC寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void I2C_UnEnable(I2C_TypeDef * I2Cx)
{
	I2Cx->CTR = ~I2C_CTR_EN;
}

/********************************************************************
** 函数名称：I2C_Enable
** 函数功能：使能iic接口
** 输入参数：I2C_TypeDef：IIC寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void I2C_Enable(I2C_TypeDef * I2Cx)
{
	I2Cx->CTR |= I2C_CTR_EN ;
}
 
/********************************************************************
** 函数名称：I2C_Rate_Set
** 函数功能：设置IIC速率
** 输入参数：I2C_TypeDef：IIC寄存器结构体指针
**           Rate：IIC速率
** 输出参数：无
** 返回参数：指示初始程序的错误状态
********************************************************************/
uint16_t I2C_Rate_Set(I2C_TypeDef * I2Cx,uint16_t Rate)
{
	uint16_t     prescal = 0;

	prescal =    (uint32_t) (SystemCoreClock/(5000*Rate)-1);
	I2Cx->PRER = (prescal&I2C_CTR_PERE);

	return       prescal;
}

/********************************************************************
** 函数名称：Delay_ms_i2c
** 函数功能：ms延时
** 输入参数：delay_ms：延时参数
** 输出参数：无
** 返回参数：指示初始程序的错误状态
********************************************************************/
void Delay_ms_i2c(__IO uint32_t delay_ms)
{
	for(delay_ms=delay_ms*32500; delay_ms != 0; delay_ms--);
}
 
/********************************************************************
** 函数名称：I2C_SendByte
** 函数功能：通过IIC总线接口发送一个字节
** 输入参数：I2C_TypeDef：IIC寄存器结构体指针
**           slv_address：IIC从机基地址
**           data_address：IIC从机数据地址
**           data：写入的字节数据
** 输出参数：无
** 返回参数：无
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
** 函数名称：I2C_ReceiveByte
** 函数功能：通过IIC总线接口读取一个字节
** 输入参数：I2C_TypeDef：IIC寄存器结构体指针
**           slv_address：IIC从机基地址
**           data_address：IIC从机数据地址
** 输出参数：无
** 返回参数：读取的字节数据
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
** 函数名称：I2C_SendBytes
** 函数功能：通过IIC总线接口发送一个字符串
** 输入参数：I2C_TypeDef：IIC寄存器结构体指针
**           slv_address：IIC从机基地址
**           data_address：IIC从机数据地址
**           *data：写入的字符串数据
**           data_num：写入的数据长度
** 输出参数：无
** 返回参数：无
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
** 函数名称：I2C_ReadBytes
** 函数功能：通过IIC总线接口读取一个字符串
** 输入参数：I2C_TypeDef：IIC寄存器结构体指针
**           slv_address：IIC从机基地址
**           data_address：IIC从机数据地址
**           data_num：读取的数据长度
** 输出参数：*data：读取的字符串数据
** 返回参数：无
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
** 函数名称：I2C_InterruptOpen
** 函数功能：打开IIC中断
** 输入参数：I2C_TypeDef：IIC寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void I2C_InterruptOpen(I2C_TypeDef * I2Cx)
{
	I2Cx->CTR |= I2C_CTR_IEN;
}

/********************************************************************
** 函数名称：I2C_InterruptClose
** 函数功能：关闭IIC中断
** 输入参数：I2C_TypeDef：IIC寄存器结构体指针
** 输出参数：无
** 返回参数：无
********************************************************************/
void I2C_InterruptClose(I2C_TypeDef * I2Cx)
{
	I2Cx->CTR &= ~I2C_CTR_IEN;
}
