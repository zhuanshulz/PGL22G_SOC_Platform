#ifndef PANGO_I2C_EEPROM_H
#define PANGO_I2C_EEPROM_H

#ifdef __cplusplus
	extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "PANGO_M1.h"

#define EEPROM_ADDRESS 		0XA0
#define EEPROM_SPEED	 	400									//400KHz
#define EEPROM_IRQ	 		1									//iic中断使能标志1：打开；0：关闭
#define EEP_Firstpage 		0x00
#define EEP_Randompage 		0x06
#define I2C_PageSize 		64 									//24128 is capable of an 64-byte page write
		
void I2C_EE_BufferWrite(I2C_TypeDef *i2c, uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
uint8_t I2C_EE_ByteRead(I2C_TypeDef *i2c, uint16_t ReadAddr);
void I2C_EE_BytesRead(I2C_TypeDef *i2c, uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead);		
void I2C_EE_BufferRead(I2C_TypeDef *i2c, uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead);
void I2C_EE_PageWrite(I2C_TypeDef *i2c, uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
void I2C_EE_BytesWrite(I2C_TypeDef *i2c, uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
void I2C_EE_ByteWrite(I2C_TypeDef *i2c, uint8_t data, uint16_t WriteAddr);
		
		
#ifdef __cplusplus
}
#endif

#endif /* PANGO_IIC_EEPROM_H */

