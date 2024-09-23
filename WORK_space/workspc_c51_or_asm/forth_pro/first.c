#include<reg51.h>
#include <stdlib.h>
#include <string.h>
//---重定义关键词---//

#define LCD1602_DATAPINS P0
sbit LCD1602_E=P2^7;
sbit LCD1602_RW=P2^5;
sbit LCD1602_RS=P2^6;

void Lcd1602_Delay1ms(unsigned int c);   //误差 0us

void LcdWriteCom(unsigned char com);
	
void LcdWriteData(unsigned char dat);
void LcdInit();	
#define GPIO_KEY P1

unsigned char KeyValue;
unsigned char KeyState;

unsigned char dat[]="0123456789ABCDEF";
unsigned char nums[20];
unsigned char re[10];
int count = 0;

void Delay10ms();  
void KeyDown();		
void delay(unsigned char i)
{
	while(i--);	
}

void main(void)
{
	unsigned char i;
	LcdInit();
	KeyState=0;
	while(1)
	{
		KeyDown();
		if(KeyState)
		{
			KeyState=0;
			LcdWriteCom(0x80);
            nums[count] = KeyValue;
			count++;
			for(i = 0 ; i < count ; i++)
                LcdWriteData(dat[nums[i]]);
		}
		
	}				
}

void KeyDown(void)
{
	char a;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)
	{
		Delay10ms();
		if(GPIO_KEY!=0x0f)
		{
			KeyState=1;
			//测试列
			GPIO_KEY=0X0F;
// 			Delay10ms();
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=0;break;
				case(0X0b):	KeyValue=1;break;
				case(0X0d): KeyValue=2;break;
				case(0X0e):	KeyValue=3;break;
//				default:	KeyValue=17;	//检测出错回复17意思是把数码管全灭掉。
			}
			//测试行
			GPIO_KEY=0XF0;
			Delay10ms();
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue;break;
				case(0Xb0):	KeyValue=KeyValue+4;break;
				case(0Xd0): KeyValue=KeyValue+8;break;
				case(0Xe0):	KeyValue=KeyValue+12;break;
//				default:	KeyValue=17;
			}
			while((a<50)&&(GPIO_KEY!=0xf0))	 //检测按键松手检测
			{
				Delay10ms();
				a++;
			}
			a=0;
		}
	}
}

void Delay10ms(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}

void LcdWriteCom(unsigned char com)	  //写入命令
{
	LCD1602_E = 0;	 //使能清零
	LCD1602_RS = 0;	 //选择写入命令
	LCD1602_RW = 0;	 //选择写入

	LCD1602_DATAPINS = com;	//由于4位的接线是接到P0口的高四位，所以传送高四位不用改
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	 //写入时序
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

//	Lcd1602_Delay1ms(1);
	LCD1602_DATAPINS = com << 4; //发送低四位
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	 //写入时序
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
void Lcd1602_Delay1ms(unsigned int c)   //误差 0us
{
    unsigned char a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	}
    	
}

void LcdWriteData(unsigned char dat)			//写入数据
{
	LCD1602_E = 0;	  //使能清零
	LCD1602_RS = 1;	  //选择写入数据
	LCD1602_RW = 0;	  //选择写入

	LCD1602_DATAPINS = dat;	//由于4位的接线是接到P0口的高四位，所以传送高四位不用改
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	  //写入时序
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

	LCD1602_DATAPINS = dat << 4; //写入低四位
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	  //写入时序
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
void LcdInit()						  //LCD初始化子程序
{
	LcdWriteCom(0x32);	 //将8位总线转为4位总线
	LcdWriteCom(0x28);	 //在四位线下的初始化
	LcdWriteCom(0x0c);  //开显示不显示光标
	LcdWriteCom(0x06);  //写一个指针加1
	LcdWriteCom(0x01);  //清屏
	LcdWriteCom(0x80);  //设置数据指针起点
}