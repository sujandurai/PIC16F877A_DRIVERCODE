


#include"timer0.h"

#define _XTAL_FREQ 20000000
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF
void main()
{
    
     
     TRISB=0x00;
     prescaler_timer(2);
     while(1)
     {
     
     delay_ms(0.103);   
     PORTB=0xFF;
     delay_ms(0.103);
     PORTB=0x00;
     
     
     }
}
