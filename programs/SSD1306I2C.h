#ifndef SSD1306I2C_H
#define SSD1306I2C_H

#include <reg51.h>
#include <stdio.h>
#include "I2C.h"

sbit SCL=P1^1; //串行时钟
sbit SDA=P1^0; //串行数据

#define high 1
#define low 0

#define OLED_address 0x78
#define Brightness 0xCF
#define X_WIDTH 128
#define Y_WIDTH 64

void OLED_WrDat(unsigned char IIC_Data);
void OLED_WrCmd(unsigned char IIC_Command);
void OLED_Set_Pos(unsigned char x, unsigned char y) ;
void OLED_Fill(unsigned char bmp_dat);
void OLED_CLS(void);

void OLED_Init(void);
void OLED_P6x8Str(unsigned char x, y,unsigned char ch[]);
void OLED_P6x8Val(unsigned char x, y,unsigned long numvalue);
void OLED_P8x16Str(unsigned char x, y,unsigned char ch[]);
void OLED_P8x16Val(unsigned char x, y,unsigned long numvalue);
void OLED_P16x16Ch(unsigned char x, y, N);
void Draw_BMP(unsigned char x0, y0,x1, y1,unsigned char BMP[]);

#endif