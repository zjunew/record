/* K1控制EEPROM的写，K2控制EEPROM的读，读取上次写进的数据
   下载完成程序后要拔掉BOOT1，再重启就可以 */


#include "public.h"
#include "iic.h"
#include "lcd1602.h"

#define KEY (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7)
u8 num[]="0123456789+-*/()=";
u8 show[100];
unsigned char count = 0;
u8 oper_val = 0 , oper_status = 0;

u8 nums_val = 0, nums_status = 0; 
//独立按键----------------------------------------------------------------------------------------------------------------
void KEYGPIOINIT()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=KEY;	 //定义所有管脚
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//50M翻转速度
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
void KEYRCCINIT()
{
	SystemInit();//打开系统72M时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //打开端口B的时钟	
}

void oper_keydown()
{
   u16 value=0;
	value=GPIO_ReadInputData(GPIOA);
	value=value&0x00ff;
	switch(value)
	{
        case 0x00fe: oper_status = 1; oper_val = 10;break;	   //if(value==0x00fe) GPIOB->ODR = 0x01ff
        case 0x00fd: oper_status = 1; oper_val = 11;break;
        case 0x00fb: oper_status = 1; oper_val = 12;break;
        case 0x00f7: oper_status = 1; oper_val = 13;break;
        case 0x00ef: oper_status = 1; oper_val = 14;break;
        case 0x00df: oper_status = 1; oper_val = 15;break;
        case 0x00bf: oper_status = 1; oper_val = 16;break;
        case 0x007f: oper_status = 1; oper_val = 17;break;
        default : break;
	}
	delayms(200);
}

void oper_show()
{
    //u8 i;
    if(oper_status==1)
    {
        oper_status = 0 ;
        show[count] =num[ oper_val ];
        //count ++ ;
        

        lcdwrd(show[count]);
				count ++ ;
    }
}
void oper_scan()
{
	IICRCCINIT();
	LCDRCCINIT();
	KEYRCCINIT();
	IICGPIOINIT();
	LCDGPIOINIT();
	KEYGPIOINIT();

	
	oper_keydown();
	oper_show();
}
//独立按键----------------------------------------------------------------------------------------------------------------

int main()
{
/*初始化一些配置的参数*/	
	IICRCCINIT();
	LCDRCCINIT();
	KEYRCCINIT();
	IICGPIOINIT();
	LCDGPIOINIT();
	KEYGPIOINIT();
	lcdinit();

	while(1)
	{
    	oper_scan();
	}		
}

