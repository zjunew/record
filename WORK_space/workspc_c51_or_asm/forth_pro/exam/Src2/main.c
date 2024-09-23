/* ��ʵ��������ɳ���󣬿��Բ��ðε�BOOT1�̽�ñʵ��������������ʾ 
	J21Ҫ��P10������ӵ���VCC�ǲ��Ӱ����ʾ��*/

#include "public.h"
#define KEY (GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15)
#define SEG (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7)

u8 m,k;

u8 smg[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
        0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};// ��ѡ

void GPIOINIT()	   //�˿ڳ�ʼ��
{

/*********����һ��GPIO_InitTypeDef ���͵Ľṹ��**********/
	GPIO_InitTypeDef GPIO_InitStructure;

/*********ѡ��Ҫ���Ƶ�GPIOx������**********/
	GPIO_InitStructure.GPIO_Pin=SEG;

/*********������������Ϊ50MHZ**********/
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;

/*********��������ģʽΪͨ���������**********/
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;

/*��ʼ����Ӧ��GPIO*/
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable , ENABLE);		 //Changes the mapping of the specified pin.
   
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;

	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�������

	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;

	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//��������

	GPIO_Init(GPIOB,&GPIO_InitStructure);	
}
void RCCINIT()	 //ϵͳʱ������
{	
	SystemInit();					//ϵͳʱ�ӳ�ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		  //��GPIOB��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	      //��GPIOA��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//�ܽŸ��ù���ʱ�Ӵ�
}
void keyscan()
{
	u16 value;
	u8 h1,h2,h3,h4,key;
	GPIO_Write(GPIOB,(u16)(0xfe<<8));  //�жϵ�һ���Ǹ���������
	value=GPIO_ReadInputData(GPIOB);
	h1=(u8)(value>>8);
	if(h1!=0xfe)		 
	{
		delayms(200);	  //����
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

	GPIO_Write(GPIOB,(u16)(0xfd<<8));  //�жϵ�2���Ǹ���������
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

	GPIO_Write(GPIOB,(u16)(0xfb<<8));  //�жϵ�3���Ǹ���������
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

	GPIO_Write(GPIOB,(u16)(0xf7<<8));  //�жϵ�4���Ǹ���������
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
		keyscan();						//���ϵ�ɨ�谴��
	}		
}
