/* ������ɳ����ε�BOOT1�ڿ���Դ ����������������ʵ�� */

#include "public.h"

#define KEY (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7)
#define LED (GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15)

void GPIOINIT()	//�˿ڳ�ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin=LED;	 //�������йܽ�
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//50M��ת�ٶ�
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//�������
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);//�ı�ָ���ܽŵ�ӳ��

	GPIO_InitStructure.GPIO_Pin=KEY;	 //�������йܽ�
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//50M��ת�ٶ�
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//��������
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
}
void RCCINIT()	//ʱ�ӳ�ʼ��
{
	SystemInit();//��ϵͳ72Mʱ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //�򿪶˿�B��ʱ��
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
	RCCINIT();		 //RCC��ʼ��
	GPIOINIT();		 //GPIO��ʼ��
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
