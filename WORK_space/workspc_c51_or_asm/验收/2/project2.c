#include <reg51.h>  
#include<intrins.h> 
#define uchar unsigned char  
#define uint unsigned int  
static uchar led = 0x01  ;
unsigned char autoRun = 0;
void delay(uint i)  
{  
		
    while(i--)
		{	
			uint j =10;
			while(j--);
		}			
}  

void INT0_ISR(void) interrupt 0 
{  
		
    led=_crol_(led,1);  
		P0 = led; 
    
		delay(4500);
}  



void INT1_ISR(void) interrupt 2 
{  
    if(autoRun == 0) 
    {   delay(1000);
			autoRun = 1;
			
    }  
    else 
    {  delay(1000);
        autoRun = 0;  
        P0 = 0x00; 
			
    }  
}  
  
void main() {  
    IT0 = 1; 
    IT1 = 0;
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
            delay(1200); 
        }
    }
}