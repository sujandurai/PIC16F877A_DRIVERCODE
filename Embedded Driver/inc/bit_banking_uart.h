#include"TIMER0.H"

#ifndef UART_H

#endif	/* UART_H */

void uart_init();
void transmit(uint8_t data);
void string_transmit(uint8_t *s);



void uart_init()
{
    TRISCbits.RC1=0;
    PORTCbits.RC1=1;
    TRISCbits.RC2=1;
    
}

void transmit(uint8_t data)
{
   
      delay_104us();
    
      PORTCbits.RC1 = 0;      // Start bit
   
      delay_104us();
     

    for(uint8_t i = 0; i < 8; i++)
    {
        if(data & (1 << i))
            
            PORTCbits.RC1 = 1;
        else
            PORTCbits.RC1 = 0;

       
        delay_104us();
        
    }
   
    PORTCbits.RC1 = 1;      // Stop bit
    
       delay_ms(0.104); 
     
    
    
}

void string_transmit(uint8_t *s)
{
    while(*s)
    {
        transmit(*s++);
    }
}

void receiver(void)
{
        uint8_t count=0;
        uint8_t data=0X00;
        TRISCbits.RC2=1;
        
        while(PORTCbits.RC2);
       delay_104us();
        
        while(count<8)
        {
            if(PORTCbits.RC2==1)
                data|=(1<<count);
            
              count++;
              
               delay_104us();
        }
        
           delay_ms(0.104);
           transmit(data);
           delay_ms(0.104); 
          
}



