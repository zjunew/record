/* 此实验下载完成程序后，可以不用拔掉BOOT1短接帽实验现象能正常显示 
	J21要接P10，如果接的是VCC那侧会影响显示的*/

#include "public.h"
#define KEY (GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15)
#define SEG (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7)

u8 m,k;

u8 smg[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
        0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};// 段选

void GPIOINIT()	   //端口初始化
{

/*********定义一个GPIO_InitTypeDef 类型的结构体**********/
	GPIO_InitTypeDef GPIO_InitStructure;

/*********选择要控制的GPIOx的引脚**********/
	GPIO_InitStructure.GPIO_Pin=SEG;

/*********设置引脚速率为50MHZ**********/
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;

/*********设置引脚模式为通用推完输出**********/
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;

/*初始化相应的GPIO*/
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable , ENABLE);		 //Changes the mapping of the specified pin.
   
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;

	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //推挽输出

	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;

	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//上拉输入

	GPIO_Init(GPIOB,&GPIO_InitStructure);	
}
void RCCINIT()	 //系统时钟配置
{	
	SystemInit();					//系统时钟初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		  //打开GPIOB的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	      //打开GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//管脚复用功能时钟打开
}
void keyscan()
{
	u16 value;
	u8 h1,h2,h3,h4,key;
	GPIO_Write(GPIOB,(u16)(0xfe<<8));  //判断第一行那个按键按下
	value=GPIO_ReadInputData(GPIOB);
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

	GPIO_Write(GPIOB,(u16)(0xfd<<8));  //判断第2行那个按键按下
	value=GPIO_ReadInputData(GPIOB);
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

	GPIO_Write(GPIOB,(u16)(0xfb<<8));  //判断第3行那个按键按下
	value=GPIO_ReadInputData(GPIOB);
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

	GPIO_Write(GPIOB,(u16)(0xf7<<8));  //判断第4行那个按键按下
	value=GPIO_ReadInputData(GPIOB);
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
int main()
{
	RCCINIT();
	GPIOINIT();
	GPIO_Write(GPIOA,(u16)(~smg[0]));
	while(1)
	{
		keyscan();						//不断的扫描按键
	}		
}
