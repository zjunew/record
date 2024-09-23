#include "iic.h"
void IICGPIOINIT()	  //SCL端口初始化
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=scl;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure); 	
}
void SDAOUTINT()	  //SDA输出端口初始化
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=sda;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
}
void SDAININT()		  //SDA输入端口初始化
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=sda;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
void IICRCCINIT() //系统初始化
{
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
}
void start()		//启动
{
	GPIO_SetBits(GPIOB,scl);
	SDAOUTINT();
	GPIO_SetBits(GPIOB,sda);
	delayus(100);
	GPIO_ResetBits(GPIOB,sda);
	delayus(100);
}
void stop()		 //停止
{
	GPIO_ResetBits(GPIOB,scl);
	SDAOUTINT();
	GPIO_ResetBits(GPIOB,sda);
	delayus(100);
	GPIO_SetBits(GPIOB,scl);
	GPIO_SetBits(GPIOB,sda);
	delayus(100);
}
void ack()			   //启动写入数据的函数
{
	GPIO_ResetBits(GPIOB,scl);
	delayus(100);
	SDAOUTINT();
	GPIO_SetBits(GPIOB,sda);
	delayus(100);
	GPIO_SetBits(GPIOB,scl);
	GPIO_ResetBits(GPIOB,sda);
	delayus(100);
	GPIO_SetBits(GPIOB,sda);
	delayus(100);
	GPIO_ResetBits(GPIOB,scl);	
}
void notack()				//终止写入数据的函数
{
	GPIO_ResetBits(GPIOB,scl);
	delayus(100);
	SDAOUTINT();
	GPIO_SetBits(GPIOB,sda);
	GPIO_SetBits(GPIOB,scl);
	delayus(100);
	GPIO_ResetBits(GPIOB,scl);
	delayus(100);	
}
void wrbyte(u8 dat)			//写八位数据
{
	u8 i;
	GPIO_ResetBits(GPIOB,scl);
	delayus(100);
	SDAOUTINT();
	for(i=0;i<8;i++)
	{
		if(((dat&0x80)>>7)==1)	
			GPIO_SetBits(GPIOB,sda);
		else
			GPIO_ResetBits(GPIOB,sda);
		dat<<=1;
		GPIO_SetBits(GPIOB,scl);
		delayus(100);
		GPIO_ResetBits(GPIOB,scl);
		delayus(100);		
	}
}
void wrbytes(u8 add,u8 dat)		  //写数据
{
	start();
	wrbyte(0xa0);
	ack();
	wrbyte(add);
	ack();
	wrbyte(dat);
	ack();
	stop();	
}
u8 rdbyte()			  //读字节
{
	u8 value=0,i;
	GPIO_SetBits(GPIOB,scl);
	delayus(100);
	SDAININT();
	for(i=0;i<8;i++)
	{
		value<<=1;
		if(GPIO_ReadInputDataBit(GPIOB,sda)==1)
		{
			value|=0x01;
		}
		GPIO_ResetBits(GPIOB,scl);
		delayus(100);
		GPIO_SetBits(GPIOB,scl);
		delayus(100);
	}
	return value;
}
u8 rdbytes(u8 add)		   //读地址
{
	u8 a=0;
	start();
	wrbyte(0xa0);
	ack();
	wrbyte(add);
	ack();
	start();
	wrbyte(0xa1);
	ack();
	a=rdbyte();
	notack();
	stop();
	return a;	
} 
