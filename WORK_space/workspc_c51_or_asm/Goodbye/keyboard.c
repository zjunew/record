#include"public.h"
u8 smg[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
        0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
void keyscan()
{
	u16 value;
	u8 h1,h2,h3,h4,key;
	GPIO_Write(GPIOA,(u16)(0xfe<<8));  //判断第一行那个按键按下
	value=GPIO_ReadInputData(GPIOA);
	h1=(u8)(value>>8);
	if(h1!=0xfe)		 
	{
		delayms(200);	  //消抖
		if(h1!=0xfe)
		{
			key=h1&0xf0;
			switch(key)		
			{
				case 0xe0: GPIO_Write(GPIOA,(u16)(~smg[0]));break;
				case 0xd0: GPIO_Write(GPIOA,(u16)(~smg[1]));break;
				case 0xb0: GPIO_Write(GPIOA,(u16)(~smg[2]));break;
				case 0x70: GPIO_Write(GPIOA,(u16)(~smg[3]));break;
			}
		}
	//	while(h1!=0xfe);
	}

	GPIO_Write(GPIOA,(u16)(0xfd<<8));  //判断第2行那个按键按下
	value=GPIO_ReadInputData(GPIOA);
	h2=(u8)(value>>8);
	if(h2!=0xfd)		 
	{
		delayms(200);
		if(h2!=0xfd)
		{
			key=h2&0xf0;
			switch(key)		
			{
				case 0xe0: GPIO_Write(GPIOA,(u16)(~smg[4]));break;
				case 0xd0: GPIO_Write(GPIOA,(u16)(~smg[5]));break;
				case 0xb0: GPIO_Write(GPIOA,(u16)(~smg[6]));break;
				case 0x70: GPIO_Write(GPIOA,(u16)(~smg[7]));break;
			}
		}
	//	while(h2!=0xfd);
	}

	GPIO_Write(GPIOA,(u16)(0xfb<<8));  //判断第3行那个按键按下
	value=GPIO_ReadInputData(GPIOA);
	h3=(u8)(value>>8);
	if(h3!=0xfb)		 
	{
		delayms(200);
		if(h3!=0xfb)
		{
			key=h3&0xf0;
			switch(key)		
			{
				case 0xe0: GPIO_Write(GPIOA,(u16)(~smg[8]));break;
				case 0xd0: GPIO_Write(GPIOA,(u16)(~smg[9]));break;
				case 0xb0: GPIO_Write(GPIOA,(u16)(~smg[10]));break;
				case 0x70: GPIO_Write(GPIOA,(u16)(~smg[11]));break;
			}
		}
	//	while(h3!=0xfb);
	}

	GPIO_Write(GPIOA,(u16)(0xf7<<8));  //判断第4行那个按键按下
	value=GPIO_ReadInputData(GPIOA);
	h4=(u8)(value>>8);
	if(h4!=0xf7)		 
	{
		delayms(200);
		if(h4!=0xf7)
		{
			key=h4&0xf0;
			switch(key)		
			{
				case 0xe0: GPIO_Write(GPIOA,(u16)(~smg[12]));break;
				case 0xd0: GPIO_Write(GPIOA,(u16)(~smg[13]));break;
				case 0xb0: GPIO_Write(GPIOA,(u16)(~smg[14]));break;
				case 0x70: GPIO_Write(GPIOA,(u16)(~smg[15]));break;
			}
		}
	//	while(h4!=0xf7);
	}
}