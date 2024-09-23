#include <reg51.h>
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

unsigned char oper_state;
unsigned char MY_oper;

unsigned char dat[]="0123456789ABCDEF+-*/()=";
unsigned char nums[20];
unsigned char re[8];
int count = 0;

sbit key1=P3^0;
sbit key2=P3^1;
sbit key3=P3^2;
sbit key4=P3^3;
sbit key5=P3^4;
sbit key6=P3^5;
sbit key7=P3^6;
sbit key8=P3^7;

void Delay10ms();  
void KeyDown();		
void delay(unsigned char i)
{
	while(i--);	
}

void operater_down()
{
	if(key1 == 0)		  
	{	
		delay(1000);   
		if(key1 == 0)	
		{
			oper_state = 1;
			MY_oper = 16 ;
		}
		while( !key1 );	 
	}	
	if(key2 == 0)		  
	{	
		delay(1000);
		if(key2 == 0)	
		{
			oper_state = 1;
			MY_oper = 17 ;
		}
		while(!key2);	 
	}	
	if(key3 == 0)		  
	{	
		delay(1000);
		if(key3 == 0)	
		{
			oper_state = 1;
			MY_oper = 18 ;
		}
		while(!key3);	 
	}	
	if(key4 == 0)		  
	{	
		delay(1000);
		if(key4 == 0)	
		{
			oper_state = 1;
			MY_oper = 19 ;
		}
		while(!key4);	 
	}	
	if(key5 == 0)		  
	{	
		delay(1000); 
		if(key5 == 0)	
		{
			oper_state = 1;
			MY_oper = 20 ;
		}
		while(!key5);	 
	}	
	// if(key6 == 0)		  
	// {	
	// 	delay(2000);
	// 	if(key6 == 0)	
	// 	{
	// 		oper_state = 1;
	// 		MY_oper = 21 ;
	// 	}
	// 	while(!key6);	 
	// }	
	if(key7 == 0)		  
	{	
		delay(1000);
		if(key7 == 0)	
		{
			oper_state = 1;
			MY_oper = 21 ;
		}
		while(!key7);	 
	}	
	if(key8 == 0)		  
	{	
		delay(1000);  
		if(key8 == 0)	
		{
			oper_state = 1;
			MY_oper = 22 ;
		}
		while(!key8);	 
	}	
}

void main(void)
{
	unsigned char i;
	LcdInit();
	KeyState=0;
	oper_state = 0;
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

		operater_down();

		if(oper_state)
		{
            nums[count] = MY_oper ;
            LcdWriteCom(0x80);
            count++;
            for(i = 0 ; i < count ; i++)
                LcdWriteData(dat[nums[i]]);
            oper_state = 0 ;
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