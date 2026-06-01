
#include "uart.h" 
//#define _XTAL_FREQ 20000000

#pragma config FOSC = HS        // High Speed Oscillator
#pragma config WDTE = OFF       // Watchdog Timer disabled
#pragma config PWRTE = OFF      // Power-up Timer disabled
#pragma config BOREN = ON       // Brown-out Reset enabled
#pragma config LVP = OFF        // Low-Voltage Programming disabled
#pragma config CPD = OFF        // Data EEPROM protection off
#pragma config WRT = OFF        // Flash Write protection off
#pragma config CP = OFF         // Code protection off



void main(void) 
{
     
     uart_init();
     
     while(1)
     {
     transmit(0x08); 
     __delay_ms(1);
     
     }
}
