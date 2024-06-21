# ADS1110-program-ADS1110-
ADS1110 program[ADS1110程序]

文件描述：
"prj.pdsprj"是程序仿真实例（使用proteus8.11及以上版本打开）
"project.uvproj"是底层程序应用示例
"ADS1110.h"和"ADS1110.c"是底层文件
"I2C.h"和"I2C.c"是前提文件

函数描述：

//芯片地址
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
