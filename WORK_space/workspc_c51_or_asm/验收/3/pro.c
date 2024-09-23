#include <reg51.h>		 
typedef unsigned int u16;	  
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 KeyValue = 8 , hour = 12 , min = 0 , second = 0 ,flag = 0;

u8 code smgduan[19]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,  0x77,0x73,0x40,0x00};//显示0~9,的值
u8 con[9] = {10,12,   1,2,   0,0,    0,0};

void delay(u16 i)
{
	while(i--);
}

void KeyDown(void)
{
	char a=0;
	P1=0x0f;
	if(P1!=0x0f)//读取按键是否按下
	{
		delay(1000);//延时10ms进行消抖
		if(P1!=0x0f)//再次检测键盘是否按下
		{	
			//测试列
			P1=0X0F;
			switch(P1)
			{
				case(0X07):	KeyValue=0;break;
				case(0X0b):	KeyValue=1;break;
				case(0X0d): KeyValue=2;break;
				case(0X0e):	KeyValue=3;break;
			}
			//测试行
			P1=0XF0;
			switch(P1)
			{
				case(0X70):	KeyValue=KeyValue;break;
				case(0Xb0):	KeyValue=KeyValue+4;break;
				case(0Xd0): KeyValue=KeyValue+8;break;
				case(0Xe0):	KeyValue=KeyValue+12;break;
			}
			while((a<50)&&(P1!=0xf0))	 //检测按键松手检测
			{
				delay(1000);
				a++;
			}
		}
	}
}

void change()
{
	con[2] = hour /10 ;
	con[3] = hour %10 ;
	con[4] = min /10 ;
	con[5] = min % 10 ;
	con[6] = second / 10 ;
	con[7] = second % 10 ;
}

void DigDisplay()
{
	u8 i;
	for(i=0;i<8;i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//显示第0位
			case(1):
				LSA=1;LSB=0;LSC=0; break;//显示第1位
			case(2):
				LSA=0;LSB=1;LSC=0; break;//显示第2位
			case(3):
				LSA=1;LSB=1;LSC=0; break;//显示第3位
			case(4):
				LSA=0;LSB=0;LSC=1; break;//显示第4位
			case(5):
				LSA=1;LSB=0;LSC=1; break;//显示第5位
			case(6):
				LSA=0;LSB=1;LSC=1; break;//显示第6位
			case(7):
				LSA=1;LSB=1;LSC=1; break;//显示第7位	
		}
		P0=smgduan[con[i]];//发送段码
		delay(100); //间隔一段时间扫描	
		P0=0x00;//消隐
	}
}

void show()
{
    switch (KeyValue)
    {
    case 0:
        if(hour>=12)
        {
            con[0] = 11;
            con[1] = 12;
            flag = 1;
        }
        else 
        {
            con[0] = 10;
            con[1] = 12 ;
            flag = 1;
        }
        break;
    
    case 1:
        hour = (hour + 1) %24 ;
        
        break;

    case 2:
        min = (min + 1) % 60 ;
        
        break;

    case 3:
        second = (second +1 ) % 60;
        
        break;
    
    case 4:
        if(flag)
        {
            con[0] = 13;
            con[1] = 13;
            flag = 0;
        }
        break;
    
    case 5:
        hour = (hour + 23) %24 ;
        
        break;
    
    case 6:
        min = (min + 59) % 60 ;
        
        break;

    case 7:
        second = (second + 59 ) % 60;
        
        break;
    }
	change();
    DigDisplay();
	KeyValue = 8;
}



void Timer1Init()
{
	TMOD|=0X10;//选择为定时器1模式，工作方式1，仅用TR1打开启动。

	TH1=0XFC;	//给定时器赋初值，定时1ms
	TL1=0X18;	
	ET1=1;//打开定时器1中断允许
	EA=1;//打开总中断
	TR1=1;//打开定时器			
}

void clock()
{
	second++;
	if(second == 60)
	{
		second = 0;
		min ++ ;
	}
	if(min == 60)
	{
		min =0 ;
		hour ++ ;
	}
	if(hour == 24)
	{
		hour =0 ;
	}
}

void main()
{	
	Timer1Init();
	while(1)
    {
        KeyDown();
        show();
    }
}

void Timer1() interrupt 3
{
	static u16 i;
	TH1=0XFC;	//给定时器赋初值，定时1ms
	TL1=0X18;
	i++;
	if(i==1000)
	{
		clock();
		change();
		DigDisplay();
		i = 0;
	}	
}