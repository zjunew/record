#ifndef _iic_H
#define _iic_H
#include "public.h"
#define scl (GPIO_Pin_6)
#define sda (GPIO_Pin_7)
#define LED (GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15)

void IICGPIOINIT(void);
void IICRCCINIT(void);
void SDAOUTINT(void);
void SDAININT(void);
void wrbytes(u8 add,u8 dat);
u8 rdbytes(u8 add);


#endif
