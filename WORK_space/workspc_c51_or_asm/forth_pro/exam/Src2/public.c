#include "public.h"
void delay(u32 i)
{
	while(i--);	
}
void delayms(u32 i)
{
	u32 temp;
	SysTick->LOAD=9000*i;
	SysTick->CTRL=0x01;
	SysTick->VAL=0x00;
	do
	{	
		temp=SysTick->CTRL;	
	}
	while((temp&0x01)&&(!(temp&(1<<16))));
	SysTick->CTRL=0x00;
	SysTick->VAL=0x00;
}
void delayus(u32 i)
{
	u32 temp;
	SysTick->LOAD=9*i;
	SysTick->CTRL=0x01;
	SysTick->VAL=0x00;
	do
	{	
		temp=SysTick->CTRL;	
	}
	while((temp&0x01)&&(!(temp&(1<<16))));
	SysTick->CTRL=0x00;
	SysTick->VAL=0x00;
}

	