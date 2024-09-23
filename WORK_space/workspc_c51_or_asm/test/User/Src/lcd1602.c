#include "lcd1602.h"
void LCDGPIOINIT()	 //LCD1602的端口初始化
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=DATA|rs|rw|e;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
void LCDRCCINIT()
{
	SystemInit();//打开系统72M时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //打开端口B的时钟
}
u8 readbusy()	//忙信号检测
{		
	u8 f;	
	GPIO_ResetBits(GPIOB,rs);		
	GPIO_SetBits(GPIOB,rw);
	GPIO_SetBits(GPIOB,e);	
	f=((GPIO_ReadInputData(GPIOB)&0X8000));
	delayms(10);
	GPIO_ResetBits(GPIOB,e);
	return f;		
}
//void lcdwrc(u8 c)
//{	
//	while(readbusy());
//	GPIO_ResetBits(GPIOB,rs);		
//	GPIO_ResetBits(GPIOB,rw);
//	GPIO_ResetBits(GPIOB,e);
//	delayms(1);
//	GPIOB->BSRR = c<<8 & 0xf000;  //将数据送到P0口 
//    GPIOB->BRR = ((~c)<<8) & 0xf000;
//
//	delayms(1);
//	GPIO_SetBits(GPIOB,e);
//	delayms(1);
//	GPIO_ResetBits(GPIOB,e);
//	delayms(1);
//}

void lcdwrc4bit(long c)			//4字节的写入数据
{	
	while(readbusy());
	GPIO_ResetBits(GPIOB,rs);		
	GPIO_ResetBits(GPIOB,rw);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);
	GPIOB->BSRR = c<<8 & 0xf000;  //将数据送到P0口 
    GPIOB->BRR = ((~c)<<8) & 0xf000;
	delayms(1);
	GPIO_SetBits(GPIOB,e);
	delayms(1);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);

	GPIOB->BSRR = c<<12 & 0xf000;  //将数据送到P0口 
    GPIOB->BRR = ((~c)<<12) & 0xf000;
	delayms(1);
	GPIO_SetBits(GPIOB,e);
	delayms(1);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);
}

void lcdwrd(long dat)			   //4字节的读出数据
{
	while(readbusy());		
	GPIO_SetBits(GPIOB,rs);		
	GPIO_ResetBits(GPIOB,rw);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);
	GPIOB->BSRR = dat<<8 & 0xf000;  //将数据送到P0口 
    GPIOB->BRR = ((~dat)<<8) & 0xf000;
	delayms(1);
	GPIO_SetBits(GPIOB,e);
	delayms(1);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);
	GPIOB->BSRR = dat<<12 & 0xf000;  //将数据送到P0口 
    GPIOB->BRR = ((~dat)<<12) & 0xf000;
	delayms(1);
	GPIO_SetBits(GPIOB,e);
	delayms(1);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);
	GPIO_ResetBits(GPIOB,rs);
}
void lcdinit()				   //LCD1602的初始化
{
	delayms(15);
	lcdwrc4bit(0x32);
	delayms(5);	
	lcdwrc4bit(0x28);
	delayms(5);
	lcdwrc4bit(0x08);
	delayms(5);
	lcdwrc4bit(0x01);
	delayms(5);
	lcdwrc4bit(0x06);
	delayms(5);
	lcdwrc4bit(0x0c);
	delayms(5);
}
