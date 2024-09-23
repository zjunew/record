#include <reg51.h>   
#include<intrins.h>  

typedef unsigned int u16;   
typedef unsigned char u8;
bit flag ; 

void service_one() interrupt 0
{
    flag = 1;
}
void service_two() interrupt 1
{
    flag = 2;
}
#define led P0   

void delay(u16 i)
{
    while(i--);
}

void main()
{
    EA = 1 ; 
    EX0 = 1 ; 
    IT0 = 1 ; 

    while(1)
    {
        static bit led_on = 0;  
        if(flag == 2)
        {
            led_on = !led_on;  
            flag = 0;  
            if(led_on)
            {
                u8 i;
                led=0x01;
                delay(50000);  
                while(1)
                {
                    led = 0x01 ;    
                    for(i=0;i<7;i++)    
                    {
                        led=_crol_(led,1);
                        delay(50000);  
                    }
                }
            }
            else
            {
                led = 0x01;  
            }
        }
        if(flag == 1)
        {
            static unsigned char con = 1; 
            P0 = 0x00; 
            con = _crol_(con,1) ;
            P0 = con; 
        }
    }

}
