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
	
	//GPIO_InitTypeDef GPIO_InitStructure_new;
	
}
void KEYRCCINIT()
{
	SystemInit();//打开系统72M时钟
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //打开端口B的时钟	
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		  //打开GPIOB的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	      //打开GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//管脚复用功能时钟打开
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

void oper_use()
{
	
	oper_keydown();
	oper_show();
}
//独立按键----------------------------------------------------------------------------------------------------------------

//matrix----------------------------------------------------------------


void nums_keyscan()
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
				case 0xe0:nums_status = 1; nums_val = 0;break;
				case 0xd0:nums_status = 1; nums_val = 1;break;
				case 0xb0:nums_status = 1; nums_val = 2;break;
				case 0x70:nums_status = 1; nums_val = 3;break;
			}
		}
	//	while(h1!=0xfe);
		delayms(10);
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
				case 0xe0:nums_status = 1; nums_val = 4;break;
				case 0xd0:nums_status = 1; nums_val = 5;break;
				case 0xb0:nums_status = 1; nums_val = 6;break;
				case 0x70:nums_status = 1; nums_val = 7;break;
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
				case 0xe0:nums_status = 1; nums_val = 8 ;break;
				case 0xd0:nums_status = 1; nums_val = 9 ;break;
				case 0xb0:nums_status = 1; nums_val = 10 ;break;
				case 0x70:nums_status = 1; nums_val = 11 ;break;
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
				case 0xe0:nums_status = 1; nums_val = 12;break;
				case 0xd0:nums_status = 1; nums_val = 13;break;
				case 0xb0:nums_status = 1; nums_val = 14;break;
				case 0x70:nums_status = 1; nums_val = 15;break;
			}
		}
	//	while(h4!=0xf7);
	}
}

void nums_show()
{
    if(nums_status == 1)
    {
        nums_status = 0 ;
        show[count] =num[ nums_val ];
        
        lcdwrd(show[count]);
		count ++ ;
    }
}

void matrix_use()
{
	
	
	nums_keyscan();
	nums_show();
}
//matrix------------------------------------------------------------

int main()
{
/*初始化一些配置的参数*/	
	IICRCCINIT();
	LCDRCCINIT();
	KEYRCCINIT();
	IICGPIOINIT();
	LCDGPIOINIT();
	KEYGPIOINIT();
	//GPIOINIT()	;
	lcdinit();

	while(1)
	{
		oper_use();
	}		
}


