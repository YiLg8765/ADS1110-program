#ifndef _I2C_H_
#define _I2C_H_

#include <reg51.h>

sbit PIN_SDA_IIC = P1^1;
sbit PIN_SCL_IIC = P1^0;

void I2C_Start(void);
void I2C_Stop(void);
void I2C_WaitAck(bit ackbit);
void I2C_SendAck(bit ackbit);
void I2C_SendByte(unsigned char byt);
unsigned char I2C_ReadByte(void);

#endif