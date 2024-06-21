#include "ADS1110.h"

void ADS_set(unsigned char config)
{
	I2C_Start();
	I2C_SendByte(ADS_address);
	I2C_WaitAck(0);
	I2C_SendByte(config);
	I2C_WaitAck(0);
	I2C_Stop();
}

unsigned int ADS_read(void)
{
	unsigned int read=0;
	unsigned char config;
	
	I2C_Start();
	I2C_SendByte(ADS_address+1);
	I2C_WaitAck(0);
	read=I2C_ReadByte()<<8;
	I2C_SendAck(0);
	read|=I2C_ReadByte();
	I2C_SendAck(0);
	config=I2C_ReadByte();
	I2C_SendAck(0);
	I2C_Stop();
	
	return read;
}
