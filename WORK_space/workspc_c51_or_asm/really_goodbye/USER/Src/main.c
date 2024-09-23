/* 下载完程序后要把BOOT1拔掉在重新上电即可看到效果  */
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


void push(u8 n) //入栈
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

void opscan() //检测键盘---符号
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

void keyscan()  //检测键盘---数字
{
	u16 value;
	u8 h1,h2,h3,key;
	GPIO_Write(GPIOA,0xfe);  //判断第一行那个按键按下
	value=GPIO_ReadInputData(GPIOA);
	h1=(value);
	if(h1!=0xfe)		 
	{
		delayms(200);	  //消抖
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

	GPIO_Write(GPIOA,0xfd);  //判断第2行那个按键按下
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

	GPIO_Write(GPIOA,(0xfb));  //判断第3行那个按键按下
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
	u8 oop;//oop表示上一个操作符号
	int value = 0;  //用于记录多位数字
//	if(a_stack[stack_flag] != '=')
//		return;
//	else
	
	{
		int flag = 0;   //用于记录是否输入数字
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
				
				if(a_stack[i] == ')')//去括号
				{  
					stack_top(s2,&oop);//将最顶的一个操作符号备份
					while(oop != '(')
					{
						stack_pop(s2,&oop);
						compute(oop);
						stack_top(s2,&oop);//将括号内的计算后存入s1中，						
					}
					stack_pop(s2,&oop); //将反括号去掉。
					continue;
				}
				
				else//其他符号就入栈
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
					
					if(pri > opri)  //新符号优先级更高，压入栈
					{
						stack_push(s2,&a_stack[i]);
						continue;
					}
					
					while(pri <= opri)//新符号优先级低或等，先完成已经在堆栈内的计算，再压入
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
					}//重新测算优先级
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
		{//只要符号栈不为空就开始运算
			stack_pop(s2,&oop);
			compute(oop);
		}	
		b[0] = s1->data[0]/100+'0';
		b[1] = (s1->data[0]/10)%10+'0';
		b[2] = s1->data[0]%10+'0';
	}
	
	
}
	
void GPIOINIT()	  //端口初始化
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	GPIO_InitStructure.GPIO_Pin=DATA|rs|rw|e;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);//把调试设置普通IO口
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//上拉输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//上拉输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
void RCCINIT() //系统初始化
{
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//如果不加这条语句程序显示就会出错，即没有打开端口复用功能的时钟配置
}
u8 readbusy()	//忙信号检测
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
void lcdwrc(u8 c)	  //写八位数据
{	
	while(readbusy());
	GPIO_ResetBits(GPIOB,rs);		
	GPIO_ResetBits(GPIOB,rw);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);
	GPIOB->BSRR = c<<8 & 0xf000;  //将数据送到P0口 
    GPIOB->BRR = ((~c)<<8) & 0xf000;

	delayms(1);
	GPIO_SetBits(GPIOB,e);
	delayms(1);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);
}

void lcdwrc4bit(long c)		  //写8位数据,通过4个引脚
{	
	while(readbusy());
	GPIO_ResetBits(GPIOB,rs);		
	GPIO_ResetBits(GPIOB,rw);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);
	GPIOB->BSRR = c<<8 & 0xf000;  //将数据送到P0口 
    GPIOB->BRR = ((~c)<<8) & 0xf000;
	delayms(1);
	GPIO_SetBits(GPIOB,e);
	delayms(1);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);

	GPIOB->BSRR = c<<12 & 0xf000;  //将数据送到P0口 
    GPIOB->BRR = ((~c)<<12) & 0xf000;
	delayms(1);
	GPIO_SetBits(GPIOB,e);
	delayms(1);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);
}

void lcdwrd(long dat)			//读八位数据通过4个引脚
{
	while(readbusy());		
	GPIO_SetBits(GPIOB,rs);		
	GPIO_ResetBits(GPIOB,rw);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);
	GPIOB->BSRR = dat<<8 & 0xf000;  //将数据送到P0口 
    GPIOB->BRR = ((~dat)<<8) & 0xf000;
	delayms(1);
	GPIO_SetBits(GPIOB,e);
	delayms(1);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);
	GPIOB->BSRR = dat<<12 & 0xf000;  //将数据送到P0口 
    GPIOB->BRR = ((~dat)<<12) & 0xf000;
	delayms(1);
	GPIO_SetBits(GPIOB,e);
	delayms(1);
	GPIO_ResetBits(GPIOB,e);
	delayms(1);
	GPIO_ResetBits(GPIOB,rs);
}
void lcdinit()			   //LCD初始化
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
void display()		  //显示
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
        // 处理堆栈创建失败的情况
        return 1;
  
	}
	RCCINIT();	  //  系统时钟初始化

	GPIOINIT();	  //	 端口初始化

	lcdinit();	//	  液晶显示初始化
	while(1)
	{
		opscan();
		keyscan();
		display();				
	}
}
