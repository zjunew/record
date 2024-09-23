#ifndef _LCD1602_H
#define _LCD1602_H
#include "public.h"
#define DATA (GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15)
#define rs (GPIO_Pin_1)
#define rw (GPIO_Pin_2)
#define e (GPIO_Pin_0)

 u8 readbusy(void);	//Ã¦ÐÅºÅ¼ì²â
 //void lcdwrc(u8 c);
 void lcdwrc4bit(long c);
 void lcdwrd(long dat);
 void lcdinit(void);
 void LCDGPIOINIT(void);
 void LCDRCCINIT(void);


#endif
