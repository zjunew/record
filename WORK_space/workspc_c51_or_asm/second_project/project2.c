#include <reg51.h>  
#include<intrins.h> 
#define uchar unsigned char  
#define uint unsigned int  
static uchar led = 0x01  ;
void delay(uint i)  
{  
    while(i--)
		{	
			uint j =15;
			while(j--);
		}			
}  
  
void INT0_ISR(void) interrupt 0 
{  
		delay(1000);
    led=_crol_(led,1);  
    P0 = led; 
		delay(5000);
}  

static bit autoRun = 0;

void INT1_ISR(void) interrupt 2 
{  
    if(autoRun == 0) 
    {   
		autoRun = 1;
    }  
    else 
    {  
        autoRun = 0;  
        P0 = 0x00; 
    }  
}  
  
void main() {  
    IT0 = 1; 
    IT1 = 1;
    EX0 = 1; 
    EX1 = 1; 
    EA = 1;  
  
    P0 = 0x00; 
  
    while(1)
    {
        if(autoRun)
        {
            led=_crol_(led,1);
            P0 = led; 
            delay(10000); 
        }
				delay(500);
    }
}