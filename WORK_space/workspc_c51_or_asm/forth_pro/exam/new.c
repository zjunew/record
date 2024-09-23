#include <reg51.h>
/********************************硬件接口定义*********************************/
#define RS  GPIO_Pin_1 //P2^6; 
#define RW  GPIO_Pin_2 //P2^5;
#define EN  GPIO_Pin_0 //P2^7;

/********************************宏定义*********************************/
#define    LCD_RS(x)  x ? GPIO_SetBits(GPIOB, RS): GPIO_ResetBits(GPIOB, RS)
#define    LCD_RW(x)  x ? GPIO_SetBits(GPIOB, RW): GPIO_ResetBits(GPIOB, RW)
#define    LCD_EN(x)  x ? GPIO_SetBits(GPIOB, EN): GPIO_ResetBits(GPIOB, EN)

/********************** 变量定义 ---------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;     //GPIO
ErrorStatus HSEStartUpStatus;	
typedef unsigned char BYTE;
typedef unsigned char BOOL; 

BYTE dis1[] = {"H "};
BYTE dis2[] = {" "};
BYTE dis_buf=0;            //显示缓存
BYTE temp;
BYTE key;                //键顺序码
BYTE fuhao=32;
BYTE flag=0;
BYTE flag_buf=0;
BYTE flag_fuhao=0;
BYTE flag_fuhao2=0;
BYTE j,m,n;
int i=0;
int operand[15] = {0};                /*数字数组，初始化*/
int  top_num = -1;
BYTE oper[15] = {0};                  /*操作符数组，初始化*/
int top_oper = -1;   
BYTE* temp_p;							 // 数组指针
BYTE* str = dis1;
BYTE dest[15];
int num = 0; 

/***************声明函数 ---------------*/
void RCC_Configuration(void);//RCC初始化
void NVIC_Configuration(void);	//NVIC初始化
void NOP(void);		//延时周期
void Delay(vu32 nCount);   //延时程序
void delay0(BYTE x);      //延时子程序
void keyscan(void);		 // 矩阵键盘扫描子程序
void duli_keyscan(void); 	//独立按键扫描子程序
void keydown(void);		  //判断键盘键是否按下
void calculate(void);		  //判断键盘键是否按下
void result2char(void);	  //计算表达式的值
void LCD(void); //LCD显示
int insert_operand(int *operand , int * top_num ,BYTE num);//数据压入数据栈 
int insert_oper (BYTE * oper , int *top_oper , char ch);//操作符压入符号栈
int compare(BYTE *oper , int *top_oper , BYTE ch);//比较操作服优先级
int deal_date(int *operand ,BYTE *oper ,int *top_num, int *top_oper);//进行数据运算

//RCC初始化
void RCC_Configuration(void)
{   
 //复位RCC外部设备寄存器到默认值
  RCC_DeInit();
  //打开外部高速晶振
  RCC_HSEConfig(RCC_HSE_ON);
   //等待外部高速时钟准备好
  HSEStartUpStatus = RCC_WaitForHSEStartUp();
  if(HSEStartUpStatus == SUCCESS)   //外部高速时钟已经准别好
  {								    
    //开启FLASH的预取功能
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    //FLASH延迟2个周期
    FLASH_SetLatency(FLASH_Latency_2); 	
  //配置AHB(HCLK)时钟=SYSCLK
    RCC_HCLKConfig(RCC_SYSCLK_Div1);    
   //配置APB2(PCLK2)钟=AHB时钟
    RCC_PCLK2Config(RCC_HCLK_Div1); 
    //配置APB1(PCLK1)钟=AHB 1/2时钟
    RCC_PCLK1Config(RCC_HCLK_Div2);
     //配置PLL时钟 == 外部高速晶体时钟*9 PLLCLK = 8MHz * 9 = 72 MHz 
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    //使能PLL时钟
    RCC_PLLCmd(ENABLE);
   //等待PLL时钟就绪
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }
  //配置系统时钟 = PLL时钟
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
   //检查PLL时钟是否作为系统时钟
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
}

//NVIC初始化
void NVIC_Configuration(void)
{
 NVIC_InitTypeDef NVIC_InitStructure;
#ifdef  VECT_TAB_RAM  
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
#ifdef  DEBUG

//**延时函数*
void NOP()
{ vu16 i;
  for(i=0; i<100; i++); 
}

//延时函数
void delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}

void assert_failed(u8* file, u32 line)
{ 
  while (1)
  {
  }
}
#endif

//延时子程序 
void  delay0(BYTE x)
{ BYTE j;
    while((x--)!=0)  //CPU执行x*12次
    { for(j=0;j<125;j++)
         {;}
    }
}

void result2char(void)	  //将计算结果转化为可显示的字符串
{
	dis2[5]=operand[0]%10+48;
	 dis2[4]=operand[0]/10%10+48;
	 dis2[3]=operand[0]/100%10+48;
	 dis2[2]=operand[0]/1000%10+48;
	 dis2[1]=operand[0]/10000%10+48;
	 dis2[0]=operand[0]/100000%10+48;
	 if(dis2[0]==48)
	 {  dis2[0]=32;
	 	if(dis2[1]==48)  
		{	dis2[1]=32;
		 	if(dis2[2]==48)  
			{	dis2[2]=32;
				if(dis2[3]==48)  
				{	dis2[3]=32;
					if(dis2[4]==48)  
					{	dis2[4]=32; }
				}
			}
		}
	}
}

void calculate(void)		  //判断键盘键是否按下
{
	i = 0;
	 str++;
     while(*str != '\0')
     {
        temp_p = dest;
 		m=0;
        while(*str >= 48 && *str <= 57)           /*判断是否是数据*/
        {
            *temp_p = *str;
            str ++;
            temp_p ++;
			m++;                
        }                               /*遇到符号退出*/
        if(*str != '(' && *(temp_p - 1) != '\0')      /*判断符号是否为'('*/
        {
            *temp_p = '\0';
            num = atoi(dest);               /*将字符串转为数字*/
            insert_operand(operand, &top_num,num);      /*将数据压入数据栈*/
        }
         while(1)				 
         {
             i = compare(oper,&top_oper,*str);      /*判断操作符优先级*/
            if(i == 0)
            {
                insert_oper(oper,&top_oper,*str);   /*压入操作符*/
                break;
            }
            else if(i == 1)                         /*判断括号内的表达式是否结束*/
            {
                str++;
            }
            else if(i == -1)                        /*进行数据处理*/
            {
                deal_date(operand,oper,&top_num,&top_oper);
            }
         }
        str ++;
	}
}
                                                          
//键扫描子程序 (4*3 的矩阵) P0.4 P0.5 P0.6 P0.7为行 
void keyscan(void)
 { 	temp = 0;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |  GPIO_Pin_1 |  GPIO_Pin_2 |  GPIO_Pin_3 ; // 选择所有脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //配置成推挽式输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //输出模式下 I/O输出速度 50M HZ
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //初PB口始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |  GPIO_Pin_5 |  GPIO_Pin_6 |  GPIO_Pin_7 ; // 选择所有脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //配置成推挽式输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //输出模式下 I/O输出速度 50M HZ
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //初PB口始化
	GPIO_Write(GPIOB,0X00F0); //初始化端口
    delay0(1);				 //延时
    temp=(GPIO_ReadInputData(GPIOB))&0xF0;	 //高8位的屏蔽低四位
    temp=~((temp>>4)|0x00F0); //将高四位移到地位处处理 
    if(temp==1)	  // p0.4 被拉低
    {    key=1;	  //第一个按键值
		flag_buf=1;
    }else if(temp==2)   // p0.5 被拉低
    {    key=2;	 //第2个按键值
		flag_buf=1;
    }else if(temp==4)   // p0.6 被拉低
    {    key=3;	  //第3个按键值
		flag_buf=1;
    }else if(temp==8)   // p0.7 被拉低
    {     key=4;	   //第4个按键值
		 flag_buf=1;
    }else	key=16;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |  GPIO_Pin_1 |  GPIO_Pin_2 |  GPIO_Pin_3 ; // 选择所有脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //配置成推挽式输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //输出模式下 I/O输出速度 50M HZ
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //初PB口始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |  GPIO_Pin_5 |  GPIO_Pin_6 |  GPIO_Pin_7 ; // 选择所有脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //配置成推挽式输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //输出模式下 I/O输出速度 50M HZ
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //初PB口始化
	GPIO_Write(GPIOB,0X000F);
    delay0(1);			 //延时
    temp=(GPIO_ReadInputData(GPIOB))&0x0F;
    temp=~(temp|0xF0);
	if(temp==1)		   //p0.0 被拉低
    {    key=key+0;
		flag_buf=1;
    }else if(temp==2)		   //p0.1 被拉低
    {    key=key+4;
		flag_buf=1;
    }else if(temp==4)   //p0.2 被拉低
    {    key=key+8;
		flag_buf=1;
    }else if(temp==8)	//p0.3 被拉低
    {   key=key+12;
		flag_buf=1;
    }else   key=16;	 

	if(key==11) {fuhao=40; flag_fuhao=1	;flag_fuhao2=1;flag_buf=0;}
	if(key==12) {fuhao=41; flag_fuhao=1	;flag_fuhao2=1;flag_buf=0;}    	
    dis_buf = key;	    //键值入显示缓存
    dis_buf = dis_buf & 0x0f;
}

//独立键盘扫描子程序 (2*4 的矩阵) P0.4 P0.5 P0.6 P0.7为行 
void  duli_keyscan(void)
{
	temp = 0;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All; //所有GPIO为同一类型端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //输出的最大频率为50HZ
	GPIO_Init(GPIOA, &GPIO_InitStructure);   //初始化GPIOA端口

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |  GPIO_Pin_1 | GPIO_Pin_2 |  GPIO_Pin_3 | GPIO_Pin_4 |  GPIO_Pin_5 |  GPIO_Pin_6 |  GPIO_Pin_7 ; // 选择所有脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //配置成推挽式输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //输出模式下 I/O输出速度 50M HZ
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //初PB口始化

	GPIO_Write(GPIOA,0X00FF); //初始化端口
    delay0(1);				 //延时
    temp=(GPIO_ReadInputData(GPIOA)) &0x00FF;	 //高8位的屏蔽低四位
    temp=~temp; //将高四位移到地位处处理 
    if(temp==16)	  // p0.4 被拉低
    {   fuhao=43;	  //第一个按键值
		flag_fuhao=1;
		flag_fuhao2=1;
    }
	else if(temp==32)   // p0.5 被拉低
    {    fuhao=45;	 //第2个按键值
		flag_fuhao=2;
		flag_fuhao2=1;
    }
	else if(temp==64)   // p0.6 被拉低
    {    fuhao=42;	  //第3个按键值
		flag_fuhao=3;
		flag_fuhao2=1;
    }
	else if(temp==128)   // p0.7 被拉低
    {    fuhao=47;	   //第4个按键值
		flag_fuhao=4;
		flag_fuhao2=1;
    }
	else if(temp==4)   // p0.6 被拉低
    {    fuhao=40;	  //第3个按键值
		flag_fuhao=3;
		flag_fuhao2=1;
    }
	else if(temp==8)   // p0.7 被拉低
    {    fuhao=41;	   //第4个按键值
		flag_fuhao=4;
		flag_fuhao2=1;
    }
	else if(temp==1)
    {    //fuhao=61;
		flag=1;
	}
	else if(temp!=0)
	{	 flag=2;}	
}

//函数：判断键是否按下 
 void  keydown(void)
 {   int retval;
  	//P1=0xF0; //将高4位全部置1 低四位全部置0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |  GPIO_Pin_1 |  GPIO_Pin_2 |  GPIO_Pin_3 ; // 选择所有脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //配置成推挽式输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //输出模式下 I/O输出速度 50M HZ
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //初PB口始化

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |  GPIO_Pin_5 |  GPIO_Pin_6 |  GPIO_Pin_7 ; // 选择所有脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //配置成悬浮输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //输出模式下 I/O输出速度 50M HZ
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //初PB口始化

	GPIO_Write(GPIOB,0X00F0);
	//P1!=0xF0
	retval =  GPIO_ReadInputData(GPIOB); //读PB口状态
	if(retval !=0xF0)  //判断按键是否按下 如果按钮按下 会拉低P1其中的一个端口
	{
	  keyscan();  //调用按键扫描程序
    }
}
	

/*数据压入数据栈*/
int insert_operand(int *operand , int * top_num ,BYTE num)           /*数据压入数据栈*/
{
    (*top_num) ++;
    operand[*top_num] = num;                    /*保存数据*/   
    return 0;                           /*正常退出*/
}
 
 /*操作符压入符号栈*/
int insert_oper (BYTE * oper , int *top_oper , char ch)             /*操作符压入符号栈*/
{
    (*top_oper)++;
    oper[*top_oper] = ch;                       /*保存操作符*/
    return 0;                           /*正常退出*/
}

/*比较操作服优先级*/ 
int compare(BYTE *oper , int *top_oper , BYTE ch)                   /*比较操作服优先级*/
{      
    if((oper[*top_oper] == '-' || oper[*top_oper] == '+')           /*判断当前优先级是否比栈顶操作符优先级高*/
            && (ch == '*' || ch == '/'))
    {
        return 0;                      /*操作符压入栈*/ 
    } 
    else if(*top_oper == -1 || ch == '(' 
            || (oper[*top_oper] == '(' && ch != ')'))       /*判断操作符栈是否为空；栈顶操作 符是否为'('*/
    {
        return 0;                       /*操作符压入栈*/
    } 
    else if (oper[*top_oper] =='(' && ch == ')' )       /*判断括号内的表达式是否计算完毕*/
    {
        (*top_oper)--;
        return 1;                       /*对（）进行处理*/
    } 
    else
    {
        return -1;                                          /*进行操作符的运算*/
    }
}

/*进行数据运算*/ 
int deal_date(int *operand ,BYTE *oper ,int *top_num, int *top_oper)    /*进行数据运算*/
{
    int num_1 = operand[*top_num];              /*取出数据栈中两个数据*/
    int num_2 = operand[*top_num - 1];
    int value = 0;
    if(oper[*top_oper] == '+')                  /*加法操作*/
    {
        value = num_1 + num_2;
    } 
    else if(oper[*top_oper] == '-')             /*减法操作*/
    {
        value = num_2 - num_1;
    } 
    else if(oper[*top_oper] == '*')             /*乘法操作*/
    {
        value = num_2 * num_1;
    }
    else if(oper[*top_oper] == '/')             /*除法操作*/
    {
        value = num_2 / num_1;
    }
    (*top_num) --;                              /*将数据栈顶下移一位*/
    operand[*top_num] = value;                  /*将得到的值压入数据栈*/
    (*top_oper) --;                             /*将操作符栈顶下移一位*/ 
}

/***********测试LCD繁忙状态**********************/	
BOOL lcd_bz()
{                         // 测试LCD忙碌状态
	BOOL result;
	LCD_RS(0);  //0;
	LCD_RW(1);  //1;
	LCD_EN(1);  //1;
	NOP();
	NOP();
	result = (GPIO_ReadInputData(GPIOB) & 0x8000)>>8;
	LCD_EN(0); // 0;
	return result; 
}
/*********写命令****************/	
lcd_wcmd(long cmd)
{                          // 写入指令数据到LCD
// while(lcd_bz());
	LCD_RS(0); // 0;
	LCD_RW(0); // 0;
	LCD_EN(0); // 0;
	NOP();
	NOP(); 
	GPIOB->BSRR = cmd<<8 & 0xf000;  //将数据送到P0口 
    GPIOB->BRR = ((~cmd)<<8) & 0xf000;
	NOP();
	NOP();	
	LCD_EN(1); // 1;
	NOP();	
	NOP();	
	LCD_EN(0); // 0; 
}

lcd_wcmd_4bit(long cmd)
{                          // 写入指令数据到LCD
	while(lcd_bz());
	LCD_RS(0); // 0;
	LCD_RW(0); // 0;
	LCD_EN(0); // 0;
	NOP();
	NOP(); 	 NOP();
	NOP();
	GPIOB->BSRR = cmd<<8 & 0xf000;  //将数据送到P0口 
    GPIOB->BRR = ((~cmd)<<8) & 0xf000;
	NOP();	 NOP();
	NOP();
	NOP();	
	LCD_EN(1); // 1;
	NOP();	
	NOP();	NOP();
	NOP();
	LCD_EN(0); // 0; 
	LCD_RS(0); //= 1;
	LCD_RW(0); //= 0;
	LCD_EN(0); //= 0;
	NOP();
	NOP(); 	 NOP();
	NOP();
	GPIOB->BSRR = cmd<<12 & 0xf000;  //将数据送到P0口 
    GPIOB->BRR = ((~cmd)<<12) & 0xf000;
	NOP();
	NOP();	 NOP();
	NOP();
	LCD_EN(1); // 1;
	NOP();	
	NOP();	NOP();
	NOP();
	LCD_EN(0); // 0; 
}
	
lcd_pos(long pos)
{                          //设定显示位置
	lcd_wcmd_4bit(pos | 0x0080);
}									 

lcd_init()				//LCD初始化设定
{                       
	lcd_wcmd(0x38);          //16*2显示，5*7点阵，8位数据
	delay(20000);
	lcd_wcmd(0x38);          //16*2显示，5*7点阵，8位数据 /
	delay(20000);
	lcd_wcmd(0x28);          //16*2显示，5*7点阵，8位数据
	delay(20000);
	lcd_wcmd_4bit(0x28);          //16*2显示，5*7点阵，8位数据
	delay(20000);
	lcd_wcmd_4bit(0x0c);          //显示开，关光标
	delay(20000);
	lcd_wcmd_4bit(0x02);          //移动光标
	delay(20000);
	lcd_wcmd_4bit(0x01);          //清除LCD的显示内容
	delay(20000);
}

/*****************写数据***********************/	
lcd_wdat( long dat) 
{                          //写入字符显示数据到LCD
	while(lcd_bz());
	LCD_RS(1); //= 1;
	LCD_RW(0); //= 0;
	LCD_EN(0); //= 0;
	
	GPIOB->BSRR = dat<<8 & 0xf000;    P0 = dat
    GPIOB->BRR = ((~dat)<<8) & 0xf000;
	NOP();
	NOP();
	NOP();
	NOP();
	LCD_EN(1);// = 1;
	NOP();
	NOP();
	NOP();
	NOP();
	LCD_EN(0);// = 0; 

	LCD_RS(1); //= 1;
	LCD_RW(0); //= 0;
	LCD_EN(0); //= 0;
	NOP();
	NOP();
	NOP();
	NOP();
	GPIOB->BSRR = dat<<12 & 0xf000;    P0 = dat
    GPIOB->BRR = ((~dat)<<12) & 0xf000;
	NOP();
	NOP();
	NOP();
	NOP();
	LCD_EN(1);// = 1;
	NOP();
	NOP();
	NOP();
	NOP();
	LCD_EN(0);// = 0; 
}

void LCD(void)
{
	lcd_wcmd_4bit(0x06);            //向右移动光标
      lcd_pos(0);                //设置显示位置为第一行的第1个字符
      i = 0;
     while(dis1[ i ] != '\0')
     {                           //显示字符
       lcd_wdat(dis1[ i ]);
       i++;
       delay(20000);                //控制两字之间显示速度
     }
      lcd_pos(0x40);             //设置显示位置为第二行第1个字符
      i = 0;
     while(dis2[ i ] != '\0')
     {
       lcd_wdat(dis2[ i ]);      //显示字符
       i++;
       delay(20000);                //控制两字之间显示速度
     }
      delay(800000);                //控制停留时间 
}	
	
main()
{
	j=1;
	#ifdef DEBUG
	//debug(); //在线调试使用
	#endif	
	RCC_Configuration();      //系统时钟配置函数 
	NVIC_Configuration();     //NVIC配置函数 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB1Periph_TIM2 | RCC_APB2Periph_AFIO, ENABLE);//启动GPIO模块时钟 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);  //把调试设置普通IO口 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All; //所有GPIO为同一类型端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //输出的最大频率为50HZ
	GPIO_Init(GPIOA, &GPIO_InitStructure);   //初始化GPIOA端口
	GPIO_Init(GPIOB, &GPIO_InitStructure);   //初始化GPIOB端口
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; //所有GPIO为同一类型端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	 //开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //输出的最大频率为50HZ
	GPIO_Init(GPIOB, &GPIO_InitStructure);   //初始化GPIOB端口
	GPIO_Write(GPIOA,0xffff);  //将GPIOA 16个端口全部置为高电平
	GPIO_Write(GPIOB,0xffff);  //将GPIOB 16个端口全部置为高电
	lcd_init();               // 初始化LCD
    delay(10);	

   while(1)              
   {   
   	//输入表达式：矩阵键盘输入数字，独立键盘输入符号 
	  while(flag_buf==0 && flag_fuhao2==0 && flag ==0)
	  {
		  keydown();	 //矩阵按键检测
		  delay(20);
		  duli_keyscan();  //独立按键检测
		  delay(20);
		  lcd_wcmd_4bit(0x01);//清除LCD的内容
		  delay(2000);
		  LCD();	 //实时显示按键的表达式
	  }
	 //如果有输入数字，将其显示在LCD屏上
	  if(flag_buf!=0)
	  {
		 dis1[j]=dis_buf+48;
	  }
	  //如果有输入符号，将其显示在LCD屏上
	  else if(flag_fuhao2!=0)
	  {
		 dis1[j]=fuhao;
	  }
	  //清除flag值
	  j++;
	  flag_buf=0;
	  flag_fuhao=0;
	  flag_fuhao2=0; 	  	  	  
	  if(flag==1)		 
	  {	  	  	 		 
		 calculate(); //计算表达式的值 
		 result2char();//将计算结果转化为字符串
		 dis2[0]=61;  //输入“=”
		 flag_fuhao=0;	  //清空flag
		 flag=0;
	  }
	  //如果有清屏指令，则清除屏幕，重新开始输入
	  if(flag==2)  	
	  {
	  	flag=0;
		j=1;
		for(m=0;m<16;m++)
		{
		   dis1[m]=32;
	    }
		for(m=0;m<16;m++)
		{
		   dis2[m]=32;
	    }
	    delay(2000);
	    LCD();
   	  }	
   }
}