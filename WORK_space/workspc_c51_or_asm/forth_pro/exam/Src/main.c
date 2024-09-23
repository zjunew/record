/* ����������Ҫ��BOOT1�ε��������ϵ缴�ɿ���Ч��  */


#include "public.h"
#define DATA (GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15)
#define rs (GPIO_Pin_1)
#define rw (GPIO_Pin_2)
#define e (GPIO_Pin_0)
u8 num[]="0123456789"; 
u8 a[]=" welcome to PZ  ";
u8 b[]=" Beautiful Girl ";
void GPIOINIT()	  //�˿ڳ�ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=DATA|rs|rw|e;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);//�ѵ���������ͨIO��
}
void RCCINIT() //ϵͳ��ʼ��
{
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//�������������������ʾ�ͻ������û�д򿪶˿ڸ��ù��ܵ�ʱ������
}
u8 readbusy()	//æ�źż��
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
void lcdwrc(u8 c)	  //д��λ����
{	
	while(readbusy());
	GPIO_ResetBits(GPIOB,rs);		
	GPIO_ResetBits(GPIOB,rw);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);
	GPIOB->BSRR = c<<8 & 0xf000;  //�������͵�P0�� 
    GPIOB->BRR = ((~c)<<8) & 0xf000;

	delayms(1);
	GPIO_SetBits(GPIOB,e);
	delayms(1);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);
}

void lcdwrc4bit(long c)		  //д8λ����,ͨ��4������
{	
	while(readbusy());
	GPIO_ResetBits(GPIOB,rs);		
	GPIO_ResetBits(GPIOB,rw);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);
	GPIOB->BSRR = c<<8 & 0xf000;  //�������͵�P0�� 
    GPIOB->BRR = ((~c)<<8) & 0xf000;
	delayms(1);
	GPIO_SetBits(GPIOB,e);
	delayms(1);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);

	GPIOB->BSRR = c<<12 & 0xf000;  //�������͵�P0�� 
    GPIOB->BRR = ((~c)<<12) & 0xf000;
	delayms(1);
	GPIO_SetBits(GPIOB,e);
	delayms(1);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);
}

void lcdwrd(long dat)			//����λ����ͨ��4������
{
	while(readbusy());		
	GPIO_SetBits(GPIOB,rs);		
	GPIO_ResetBits(GPIOB,rw);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);
	GPIOB->BSRR = dat<<8 & 0xf000;  //�������͵�P0�� 
    GPIOB->BRR = ((~dat)<<8) & 0xf000;
	delayms(1);
	GPIO_SetBits(GPIOB,e);
	delayms(1);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);
	GPIOB->BSRR = dat<<12 & 0xf000;  //�������͵�P0�� 
    GPIOB->BRR = ((~dat)<<12) & 0xf000;
	delayms(1);
	GPIO_SetBits(GPIOB,e);
	delayms(1);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);
	GPIO_ResetBits(GPIOB,rs);
}
void lcdinit()			   //LCD��ʼ��
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
void display()		  //��ʾ
{
	u8 i;
	lcdwrc4bit(0x00+0x80);
	for(i=0;i<16;i++)
	{
		lcdwrd(a[i]);	
	}
	lcdwrc4bit(0x40+0x80);
	for(i=0;i<16;i++)
	{
		lcdwrd(b[i]);	
	}
}
int main()
{
	
	RCCINIT();	  //  ϵͳʱ�ӳ�ʼ��

	GPIOINIT();	  //	 �˿ڳ�ʼ��

	lcdinit();	//	  Һ����ʾ��ʼ��
	while(1)
	{
		display();				
	}
}
