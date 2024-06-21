#ifndef _ADS1110_H_
#define _ADS1110_H_

#include <reg51.h>
#include "I2C.h"

#define ADS_address 0x90

//���뱶��
#define GAIN_1 0x00 //ϵ��1
#define GAIN_2 0x01 //ϵ��2
#define GAIN_4 0x02 //ϵ��4
#define GAIN_8 0x03 //ϵ��8

//���ݱ���
#define BITS_16 0x0C //ϵ��16
#define BITS_15 0x08 //ϵ��8
#define BITS_14 0x04 //ϵ��4
#define BITS_12 0x00 //ϵ��1

//ϵ��Ϊ˫ϵ��������
//����Ϊ32.768/ϵ��

//�趨���������뱶��|���ݱ���
void ADS_set(unsigned char config);
//��ȡ����
unsigned int ADS_read(void);

#endif