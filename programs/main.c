#include <reg51.h>
#include <stdio.h>
#include "SSD1306I2C.h"
#include "ADS1110.h"

sbit ctrl1=P1^2;
sbit ctrl2=P1^3;

unsigned char sec_flag=0;
unsigned int temp_read=0;
unsigned int humi_read=0;
char t[8];
bit ctrl;

void Timer_init()
{
	TMOD=0x11;
	TH0=0;
	TL0=0;
	ET0=TR0=1;
	TH1=0;
	TL1=0;
	ET1=TR1=1;
	EA=1;
}

void t0() interrupt 1
{
	TH0=0xF0;
	TL0=0xBD;
	ET0=TR0=1;
	if(!(sec_flag%128))
	{
		if(ctrl)
		{
			temp_read=ADS_read();
			sprintf(t, "%.4f",temp_read/(float)160-0.2312);
			OLED_P8x16Str(0,2,t);
			ctrl1=0;ctrl2=1;
		}
		else
		{
			humi_read=ADS_read();
			sprintf(t, "%.4f",(humi_read-6013)/252.5);
			OLED_P8x16Str(0,6,t);
			ctrl1=1;ctrl2=0;
		}
		ctrl=~ctrl;
	}
	sec_flag++;
}

void t1() interrupt 3
{
	TH1=0;
	TL1=0;
	ET1=TR1=1;
	
}

void main()
{
	OLED_Init();
	OLED_P8x16Str(0,0,"Temperature:");
	OLED_P8x16Str(0,4,"Humidity:");
	
	ADS_set(BITS_16|GAIN_1);
	ctrl1=0;ctrl2=1;
	
	Timer_init();
	while(1)
	{
		
	}
}