/* 下载完成程序后拔掉BOOT1在开电源 ，否则试验现象不能实现 */

#include "public.h"

#define KEY (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7)
#define LED (GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15)

void GPIOINIT()	//端口初始化
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin=LED;	 //定义所有管脚
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//50M翻转速度
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);//改变指定管脚的映射

	GPIO_InitStructure.GPIO_Pin=KEY;	 //定义所有管脚
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//50M翻转速度
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
}
void RCCINIT()	//时钟初始化
{
	SystemInit();//打开系统72M时钟

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //打开端口B的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
}


/****************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/
int main()
{
	u16 value;
	RCCINIT();		 //RCC初始化
	GPIOINIT();		 //GPIO初始化
	while(1)
	{
		value=GPIO_ReadInputData(GPIOB);		//((uint16_t)GPIOx->IDR)-->value
		value=value&0x00ff;
		switch(value)
		{
			case 0x00fe: GPIO_Write(GPIOB,0x01ff);break;	   //if(value==0x00fe) GPIOB->ODR = 0x01ff
			case 0x00fd: GPIO_Write(GPIOB,0x02ff);break;
			case 0x00fb: GPIO_Write(GPIOB,0x04ff);break;
			case 0x00f7: GPIO_Write(GPIOB,0x08ff);break;
			case 0x00ef: GPIO_Write(GPIOB,0x10ff);break;
			case 0x00df: GPIO_Write(GPIOB,0x20ff);break;
			case 0x00bf: GPIO_Write(GPIOB,0x40ff);break;
			case 0x007f: GPIO_Write(GPIOB,0x80ff);break;
			default : break;	
		}
	}		
}
