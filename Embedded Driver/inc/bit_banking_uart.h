#include"timer0.h"

#ifndef UART_H

#endif	/* UART_H */

void uart_init();
void transmit(uint8_t data);
void string_transmit(uint8_t *s);



void uart_init()
{
    TRISBbits.RB1=0;
    PORTBbits.RB1=1;
    
}

void transmit(uint8_t data)
{
       delay_ms(0.103);
      PORTBbits.RB1=0;
      delay_ms(0.103);
      unsigned char n=0;
    
     for(uint8_t i=0;i<8;i++)
    { 
        if(data & (1<<i)){
            PORTBbits.RB1=1;   } 
        else
            {PORTBbits.RB1=0;}
        
      delay_ms(0.103);
       
    }
    PORTBbits.RB1=1;
    delay_ms(0.103);
   
}

void string_transmit(uint8_t *s)
{
    while(*s)
    {
        transmit(*s++);
    }
}
