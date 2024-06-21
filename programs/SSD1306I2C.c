#include "SSD1306I2C.h"
#include "codetab.h"

/*********************OLEDд����************************************/ 
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
/*********************OLEDд����************************************/
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
/*********************OLED ��������************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WrCmd(0xb0+y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x01);
} 
/*********************OLEDȫ��************************************/
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
/*********************OLED��λ************************************/
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
/*********************OLED��ʼ��************************************/
void OLED_Init(void)
{
	// ��ʼ��֮ǰ����ʱ����Ҫ��
	OLED_WrCmd(0xae); // �ر� OLED ���
	OLED_WrCmd(0x00); // ���õ��е�ַ
	OLED_WrCmd(0x10); // ���ø��е�ַ
	OLED_WrCmd(0x40); // ������ʼ�е�ַ��ӳ�� RAM ��ʾ��ʼ�� (0x00~0x3F)
	OLED_WrCmd(0x81); // ���öԱȶȿ��ƼĴ���
	OLED_WrCmd(Brightness); // ���� SEG �����������
	OLED_WrCmd(0xa1); // ���� SEG/��ӳ�䣬0xa0 ���ҷ��ã�0xa1 ����
	OLED_WrCmd(0xc8); // ���� COM/��ɨ�跽��0xc0 ���·��ã�0xc8 ����
	OLED_WrCmd(0xa6); // ����������ʾ
	OLED_WrCmd(0xa8); // ���ö�·���ñ��� (1 �� 64)
	OLED_WrCmd(0x3f); // 1/64 ֡
	OLED_WrCmd(0xd3); // ������ʾƫ�ƣ��ƶ�ӳ�� RAM ������ (0x00~0x3F)
	OLED_WrCmd(0x00); // ��ƫ��
	OLED_WrCmd(0xd5); // ������ʾʱ�ӷ�Ƶ��/����Ƶ��
	OLED_WrCmd(0x80); // ���÷�Ƶ�ȣ�����ʱ��Ϊ 100 ֡/��
	OLED_WrCmd(0xd9); // ����Ԥ�������
	OLED_WrCmd(0xf1); // ����Ԥ���Ϊ 15 ��ʱ�ӣ��ŵ�Ϊ 1 ��ʱ��
	OLED_WrCmd(0xda); // ���� COM ����Ӳ������
	OLED_WrCmd(0x12);
	OLED_WrCmd(0xdb); // ���� VCOMH
	OLED_WrCmd(0x40); // ���� VCOM ȡ����ƽ
	OLED_WrCmd(0x20); // ����ҳѰַģʽ (0x00/0x01/0x02)
	OLED_WrCmd(0x02);
	OLED_WrCmd(0x8d); // ���� DC-DC ����/����
	OLED_WrCmd(0x14); // ���� (0x10) ����
	OLED_WrCmd(0xa4); // �ر�������ʾ (0xa4/0xa5)
	OLED_WrCmd(0xa6); // �رշ�����ʾ (0xa6/a7)
	OLED_WrCmd(0xaf); // �� OLED ���
	OLED_Fill(0x00); // ��ʼ����
	OLED_Set_Pos(0,0);
}
/***************������������ʾ6*8һ���׼ASCII�ַ���	��ʾ�����꣨x,y����yΪҳ��Χ0��7****************/
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

/*******************������������ʾ8*16һ���׼ASCII�ַ���	 ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************/
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
/*****************������������ʾ16*16����  ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************************/
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
/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
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
