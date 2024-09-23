#include <reg51.h>//51头文件

sbit key1=P3^0;//与键盘连接的IO设置为key1

unsigned char key();//独立键盘函数声明

void delay(unsigned char i)
{
	while(i--);	
}

void main()
{
	while(1)
	{
		if(1==key())//判断返回值是否为1
		{
			P1=~P1;
		}
	}
}

unsigned char key()//独立键盘按键函数
{
	unsigned char temp=0;
	if(key1==0)//判断是否按下键盘
	{
		delay(10);//消抖
		if(key1==0)//再次判断是否按下键盘
		{
			temp=1;//键盘按下，中间值temp赋为1
		}while(key1==0);//松手等待
	}
	return temp;//返回中间值
}