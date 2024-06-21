#ifndef _ADS1110_H_
#define _ADS1110_H_

#include <reg51.h>
#include "I2C.h"

#define ADS_address 0x90

//输入倍率
#define GAIN_1 0x00 //系数1
#define GAIN_2 0x01 //系数2
#define GAIN_4 0x02 //系数4
#define GAIN_8 0x03 //系数8

//数据比特
#define BITS_16 0x0C //系数16
#define BITS_15 0x08 //系数8
#define BITS_14 0x04 //系数4
#define BITS_12 0x00 //系数1

//系数为双系数积倒数
//量程为32.768/系数

//设定参数，输入倍率|数据比特
void ADS_set(unsigned char config);
//读取数据
unsigned int ADS_read(void);

#endif