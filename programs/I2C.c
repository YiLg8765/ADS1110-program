#include "I2C.h"

unsigned int wait_flag=0;

void I2C_Start(void)
{
	PIN_SDA_IIC = 1;
	PIN_SCL_IIC = 1;
	PIN_SDA_IIC = 0;
	PIN_SCL_IIC = 0;
}

void I2C_Stop(void)
{
	PIN_SCL_IIC = 0;
	PIN_SDA_IIC = 0;
	PIN_SCL_IIC = 1;
	PIN_SDA_IIC = 1;
}

void I2C_SendAck(bit ackbit)
{
	PIN_SCL_IIC = 0;
	PIN_SDA_IIC = ackbit;
	PIN_SCL_IIC = 1;
	PIN_SCL_IIC = 0;
	PIN_SDA_IIC = 1;
}

void I2C_WaitAck(bit ackbit)
{
	PIN_SCL_IIC  = 1;
	while(PIN_SDA_IIC!=ackbit)
	{
		wait_flag++;
		if(wait_flag>65534)
		{
			wait_flag=0;
			break;
		}
	}
	PIN_SCL_IIC = 0;
}

void I2C_SendByte(unsigned char byt)
{
	unsigned char i;
	for(i=0; i<8; i++)
	{
		PIN_SCL_IIC  = 0;
		if(byt & 0x80) PIN_SDA_IIC  = 1;
		else PIN_SDA_IIC  = 0;
		PIN_SCL_IIC = 1;
		byt <<= 1;
	}
	PIN_SCL_IIC  = 0;
}

unsigned char I2C_ReadByte(void)
{
	unsigned char i, dat;
	for(i=0; i<8; i++)
	{
		PIN_SCL_IIC = 1;
		dat <<= 1;
		if(PIN_SDA_IIC) dat |= 1;
		PIN_SCL_IIC = 0;
	}
	return dat;
}
