/* ����������Ҫ��BOOT1�ε��������ϵ缴�ɿ���Ч��  */
#include "public.h"
#include "stack.h"
#define DATA (GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15)
#define rs (GPIO_Pin_1)
#define rw (GPIO_Pin_2)
#define e (GPIO_Pin_0)
u8 num[]="0123456789"; 
u8 a[]="1 + 6 / 9=      ";
u8 b[16]="                ";
u8 a_stack[]="                "; 
int stack_flag = -1;
void calculate();
	
STACK *s1 = NULL;
STACK *s2 = NULL;


void push(u8 n) //��ջ
{
	if(stack_flag>=15)
	{
		return;
	}
	else
	{
		stack_flag++;
		a_stack[stack_flag] = n;
	}
}

void compute(u8 op)
{
	int num1,num2,rel;
	stack_pop(s1,&num1);
	stack_pop(s1,&num2);
	switch(op)
	{
		case'+':
			rel = num1+num2;break;
		case'-':
			rel = num2 - num1;break;
		case'*':
			rel = num1 * num2;break;
		case'/':
			rel = num2 / num1;break;
		default:
			stack_push(s1,&num2);stack_push(s1,&num1);;break;
		
	}
	
	stack_push(s1,&rel);
	return;
}

void opscan() //������---����
{
	int key[8];
	key[0] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8);
	key[1] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9);
	key[2] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10);
	key[3] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11);
	key[4] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12);
	key[5] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_13);
	key[6] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_14);
	delayms(20);
	if(key[0] == 0){
		push('+');
	}
	if(key[1] == 0){
		push('-');
	}
	if(key[3] == 0){
		push('*');
	}
	if(key[5] == 0){
		push('/');
	}
	if(key[6] == 0){
		push('(');
		calculate();
		
	}
	
	
	delayms(20);
	return;
}

void keyscan()  //������---����
{
	u16 value;
	u8 h1,h2,h3,key;
	GPIO_Write(GPIOA,0xfe);  //�жϵ�һ���Ǹ���������
	value=GPIO_ReadInputData(GPIOA);
	h1=(value);
	if(h1!=0xfe)		 
	{
		delayms(200);	  //����
		if(h1!=0xfe)
		{
			key=h1&0xf0;
			switch(key)		
			{
				case 0xe0: push('0');break;
				case 0xd0: push('1');break;
				case 0xb0: push('2');break;
				case 0x70: push('3');break;
			}
			return;
		}
	//	while(h1!=0xfe);
	}

	GPIO_Write(GPIOA,0xfd);  //�жϵ�2���Ǹ���������
	value=GPIO_ReadInputData(GPIOA);
	h2=(value);
	if(h2!=0xfd)		 
	{
		delayms(200);
		if(h2!=0xfd)
		{
			key=h2&0xf0;
			switch(key)		
			{
				case 0xe0: push('4');break;
				case 0xd0: push('5');break;
				case 0xb0: push('6');break;
				case 0x70: push('7');break;
			}
			return;
		}
	//	while(h2!=0xfd);
	}

	GPIO_Write(GPIOA,(0xfb));  //�жϵ�3���Ǹ���������
	value=GPIO_ReadInputData(GPIOA);
	h3=(value);
	if(h3!=0xfb)		 
	{
		delayms(200);
		if(h3!=0xfb)
		{
			key=h3&0xf0;
			switch(key)		
			{
				case 0xe0: push('8');break;
				case 0xd0: push('9');break;
				case 0xb0: push(')');break;
				case 0x70: push('=');break;
			}
			return;
		}
	}
	
}

void calculate()
{
	u8 oop;//oop��ʾ��һ����������
	int value = 0;  //���ڼ�¼��λ����
//	if(a_stack[stack_flag] != '=')
//		return;
//	else
	
	{
		int flag = 0;   //���ڼ�¼�Ƿ���������
		for(int i=0;i<=stack_flag-1;i++)
		{
			if(a_stack[i]>='0'&&a_stack[i]<='9')
			{
					value = value*10 + a_stack[i]-'0';
					flag = 1;
					continue;
			}
			
			else
			{
				if(flag)
				{
					stack_push(s1,&value);
					flag = 0;
					value = 0;
				}
				
				if(a_stack[i] == ')')//ȥ����
				{  
					stack_top(s2,&oop);//�����һ���������ű���
					while(oop != '(')
					{
						stack_pop(s2,&oop);
						compute(oop);
						stack_top(s2,&oop);//�������ڵļ�������s1�У�						
					}
					stack_pop(s2,&oop); //��������ȥ����
					continue;
				}
				
				else//�������ž���ջ
				{
					
					int pri;
					int opri;
					if(stack_isempty(s2) || a_stack[i] =='(')
					{
						stack_push(s2,&a_stack[i]);
						continue;
					}
					stack_top(s2,&oop);
					
					switch(a_stack[i])
					{
						case'+':case'-':
							pri = 1;break;
						case'*':case'/':
							pri = 2;break;
						case'(':default:
							pri = 0;break;
					}
					
					switch(oop)
					{
						case'+':case'-':
							opri = 1;break;
						case'*':case'/':
							opri = 2;break;
						case'(':default:
							opri = 0;break;
					}
					
					if(pri > opri)  //�·������ȼ����ߣ�ѹ��ջ
					{
						stack_push(s2,&a_stack[i]);
						continue;
					}
					
					while(pri <= opri)//�·������ȼ��ͻ�ȣ�������Ѿ��ڶ�ջ�ڵļ��㣬��ѹ��
					{
						stack_pop(s2,&oop);
						compute(oop);
						if(stack_isempty(s2))
							break;
						stack_top(s2,&oop);
						switch(a_stack[i])
					{
						case'+':case'-':
							pri = 1;break;
						case'*':case'/':
							pri = 2;break;
						case'(':default:
							pri = 0;break;
					}
					
					switch(oop)
					{
						case'+':case'-':
							opri = 1;break;
						case'*':case'/':
							opri = 2;break;
						case'(':default:
							opri = 0;break;
					}//���²������ȼ�
					}
					
					stack_push(s2,&oop);
				}
				
			}
		}
		
		if(flag)
		{
		stack_push(s1,&value);
		}
		while(!stack_isempty(s2))
		{//ֻҪ����ջ��Ϊ�վͿ�ʼ����
			stack_pop(s2,&oop);
			compute(oop);
		}	
		b[0] = s1->data[0]/100+'0';
		b[1] = (s1->data[0]/10)%10+'0';
		b[2] = s1->data[0]%10+'0';
	}
	
	
}
	
void GPIOINIT()	  //�˿ڳ�ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	GPIO_InitStructure.GPIO_Pin=DATA|rs|rw|e;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);//�ѵ���������ͨIO��
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�������
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//��������
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//��������
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
void RCCINIT() //ϵͳ��ʼ��
{
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
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
		lcdwrd(a_stack[i]);	
	}
	lcdwrc4bit(0x40+0x80);
	for(i=0;i<16;i++)
	{
		lcdwrd(b[i]);	
	}
}

int main()
{
	s1 = stack_create();
  s2 = stack_create();
  if (s1 == NULL || s2 == NULL) 
	{
        // �����ջ����ʧ�ܵ����
        return 1;
  
	}
	RCCINIT();	  //  ϵͳʱ�ӳ�ʼ��

	GPIOINIT();	  //	 �˿ڳ�ʼ��

	lcdinit();	//	  Һ����ʾ��ʼ��
	while(1)
	{
		opscan();
		keyscan();
		display();				
	}
}
