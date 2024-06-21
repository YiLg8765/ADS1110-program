#include "SSD1306I2C.h"
#include "codetab.h"

/*********************OLED写数据************************************/ 
void OLED_WrDat(unsigned char IIC_Data)
{
	I2C_Start();
	I2C_SendByte(OLED_address);
	I2C_WaitAck(0);
	I2C_SendByte(0x40);
	I2C_WaitAck(0);
	I2C_SendByte(IIC_Data);
	I2C_WaitAck(0);
	I2C_Stop();
}
/*********************OLED写命令************************************/
void OLED_WrCmd(unsigned char IIC_Command)
{
	I2C_Start();
	I2C_SendByte(OLED_address);
	I2C_WaitAck(0);
	I2C_SendByte(0x00);
	I2C_WaitAck(0);
	I2C_SendByte(IIC_Command);
	I2C_WaitAck(0);
	I2C_Stop();
}
/*********************OLED 设置坐标************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WrCmd(0xb0+y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x01);
} 
/*********************OLED全屏************************************/
void OLED_Fill(unsigned char bmp_dat) 
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(bmp_dat);
	}
}
/*********************OLED复位************************************/
void OLED_CLS(void)
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(0);
	}
}
/*********************OLED初始化************************************/
void OLED_Init(void)
{
	// 初始化之前的延时很重要！
	OLED_WrCmd(0xae); // 关闭 OLED 面板
	OLED_WrCmd(0x00); // 设置低列地址
	OLED_WrCmd(0x10); // 设置高列地址
	OLED_WrCmd(0x40); // 设置起始行地址，映射 RAM 显示起始行 (0x00~0x3F)
	OLED_WrCmd(0x81); // 设置对比度控制寄存器
	OLED_WrCmd(Brightness); // 设置 SEG 输出电流亮度
	OLED_WrCmd(0xa1); // 设置 SEG/列映射，0xa0 左右反置，0xa1 正常
	OLED_WrCmd(0xc8); // 设置 COM/行扫描方向，0xc0 上下反置，0xc8 正常
	OLED_WrCmd(0xa6); // 设置正常显示
	OLED_WrCmd(0xa8); // 设置多路复用比率 (1 到 64)
	OLED_WrCmd(0x3f); // 1/64 帧
	OLED_WrCmd(0xd3); // 设置显示偏移，移动映射 RAM 计数器 (0x00~0x3F)
	OLED_WrCmd(0x00); // 不偏移
	OLED_WrCmd(0xd5); // 设置显示时钟分频比/振荡器频率
	OLED_WrCmd(0x80); // 设置分频比，设置时钟为 100 帧/秒
	OLED_WrCmd(0xd9); // 设置预充电周期
	OLED_WrCmd(0xf1); // 设置预充电为 15 个时钟，放电为 1 个时钟
	OLED_WrCmd(0xda); // 设置 COM 引脚硬件配置
	OLED_WrCmd(0x12);
	OLED_WrCmd(0xdb); // 设置 VCOMH
	OLED_WrCmd(0x40); // 设置 VCOM 取消电平
	OLED_WrCmd(0x20); // 设置页寻址模式 (0x00/0x01/0x02)
	OLED_WrCmd(0x02);
	OLED_WrCmd(0x8d); // 设置 DC-DC 启用/禁用
	OLED_WrCmd(0x14); // 设置 (0x10) 禁用
	OLED_WrCmd(0xa4); // 关闭整个显示 (0xa4/0xa5)
	OLED_WrCmd(0xa6); // 关闭反显显示 (0xa6/a7)
	OLED_WrCmd(0xaf); // 打开 OLED 面板
	OLED_Fill(0x00); // 初始清屏
	OLED_Set_Pos(0,0);
}
/***************功能描述：显示6*8一组标准ASCII字符串	显示的坐标（x,y），y为页范围0～7****************/
void OLED_P6x8Str(unsigned char x, y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>126){x=0;y++;}
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
		OLED_WrDat(F6x8[c][i]);
		x+=6;
		j++;
	}
}

void OLED_P6x8Val(unsigned char x, y,unsigned long numvalue)
{
	unsigned char t[10];
	sprintf(t, "%lu", numvalue);
	OLED_P6x8Str(x,y,t);
}

/*******************功能描述：显示8*16一组标准ASCII字符串	 显示的坐标（x,y），y为页范围0～7****************/
void OLED_P8x16Str(unsigned char x, y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>120){x=0;y++;}
		OLED_Set_Pos(x,y);
		for(i=0;i<8;i++)
		OLED_WrDat(F8X16[c*16+i]);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		OLED_WrDat(F8X16[c*16+i+8]);
		x+=8;
		j++;
	}
}

void OLED_P8x16Val(unsigned char x, y,unsigned long numvalue)
{
	unsigned char t[10];
	sprintf(t, "%lu", numvalue);
	OLED_P8x16Str(x,y,t);
}
/*****************功能描述：显示16*16点阵  显示的坐标（x,y），y为页范围0～7****************************/
void OLED_P16x16Ch(unsigned char x, y, N)
{
	unsigned char wm=0;
	unsigned int adder=32*N;
	OLED_Set_Pos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16[adder]);
		adder += 1;
	}
	OLED_Set_Pos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16[adder]);
		adder += 1;
	} 	  	
}
/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void Draw_BMP(unsigned char x0, y0,x1, y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;

  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WrDat(BMP[j++]);
	    }
	}
}
