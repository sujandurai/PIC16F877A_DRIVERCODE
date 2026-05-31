#include<xc.h>  
#include <stdint.h>
#ifndef PIC_TIMERS_H
#define PIC_TIMERS_H




//=============================
// ENUM FOR TIME UNITS
//=============================
typedef enum {
    MILLI_S = 0,
    SEC     = 1,
    MIN     = 2
} TIME_UNIT;

typedef enum
{
    TIMER0_PRESCALE_1_2 = 0,
    TIMER0_PRESCALE_1_4 = 1,
    TIMER0_PRESCALE_1_8 = 2,
    TIMER0_PRESCALE_1_16 = 3,
    TIMER0_PRESCALE_1_32 = 4,
    TIMER0_PRESCALE_1_64 = 5,
    TIMER0_PRESCALE_1_128 = 6,
    TIMER0_PRESCALE_1_256 = 7
} timer0_prescale_t;

//=============================
// TIMER0 ? 8 BIT
//=============================
#define PORTB  (*(volatile unsigned char *)0X06)
#define TRISB  (*(volatile unsigned char *)0X86 )  //PORT B//
#define TMR0        (*(volatile uint8_t*)0x01)
#define T0CON       (*(volatile uint8_t*)0x05)
#define OPTION_REG  (*(volatile uint8_t*)0x81)
#define INTCON      (*(volatile uint8_t*)0x0B)



// Timer0 bit positions
#define T0PS0       0
#define T0PS1       1
#define T0PS2       2
#define PSA         3
#define T0SE        4
#define T0CS        5
#define TMR0ON      7

#define TMR0IF      2
#define TMR0IE      5
#define PEIE        6
#define GIE         7

//=============================
// TIMER1 ? 16 BIT
//=============================

#define OPTION_REG          (*(volatile uint8_t *)0x81)
#define OPTION_REGBITS      (*(volatile OPTIONAL_R*)0x81)

#define INTCON              (*(volatile uint8_t *)0x0B)
#define INTCON_REGBITS      (*(volatile INTCON_R*)0x0B)

#define TMR0                (*(volatile uint8_t *)0x101)


// TIMER 1
#define PIR1                (*(volatile uint8_t *)0x0C)
#define PIR1_REGBITS        (*(volatile PIR1_R*)0x0C)

#define PIE1                (*(volatile uint8_t *)0x8C)
#define PIE1_REGBITS        (*(volatile PIE1_R*)0x8C)

#define TMR1L               (*(volatile uint8_t *)0x0E)
#define TMR1H               (*(volatile uint8_t *)0x0F)

#define T1CON               (*(volatile uint8_t *)0x10)
#define T1CON_REGBITS       (*(volatile T1CON_R*)0x10)


// TIMER 2
#define TMR2                (*(volatile uint8_t *)0x11)
#define PR2                 (*(volatile uint8_t *)0x92)

#define T2CON               (*(volatile uint8_t *)0x12)
#define T2CON_REGBITS       (*(volatile T2CON_R*)0x12)

#define TMR1L       (*(volatile uint8_t*)0x0E)
#define TMR1H       (*(volatile uint8_t*)0x0F)
#define TMR1        (*(volatile uint16_t*)0x0E)
#define T1CON       (*(volatile uint8_t*)0x10)
#define PIR1        (*(volatile uint8_t*)0x0C)
#define PIE1        (*(volatile uint8_t*)0x8C)

// Timer1 bit positions
#define TMR1ON_BIT      0
#define TMR1CS_BIT      1
#define T1SYNC_BIT      2
#define T1OSCEN_BIT     3
#define T1CKPS0_BIT     4
#define T1CKPS1_BIT     5
#define T1RD16_BIT      7

#define TMR1IF_BIT      0
#define TMR1IE_BIT      0

//=============================
// TIMER2 ? 8 BIT (PWM or periodic)
//=============================
#define TMR2        (*(volatile uint8_t*)0x11)
#define PR2         (*(volatile uint8_t*)0x92)
#define T2CON       (*(volatile uint8_t*)0x12)

// Timer2 bit positions
#define T2CKPS0     0
#define T2CKPS1     1
#define TMR2ON_BIT  2
#define TOUTPS0     3
#define TOUTPS1     4
#define TOUTPS2     5
#define TOUTPS3     6

#define TMR2IF_BIT  1
#define TMR2IE_BIT  1

#endif 
//=============================
// UTILITY FUNCTIONS
//=============================

uint8_t time=0;

void blocking_delay(uint16_t ms);    // Blocking delay in milliseconds
void Timer0_Init(uint16_t prescaler, uint8_t   mode);
void Timer1_Init(uint16_t prescaler, uint8_t  mode);
void Timer2_Init(uint8_t prescaler, uint8_t period);
void prescaler_timer(timer0_prescale_t ratio);
void delay_Ms(uint16_t ms);


void prescaler_timer(timer0_prescale_t ratio)
{
         if(ratio==0) { OPTION_REG = 0x00; time=153; }
    else if(ratio==1) { OPTION_REG = 0x01; time=200; }
    else if(ratio==2) { OPTION_REG = 0x02; time=228; }
    else if(ratio==3) { OPTION_REG = 0x03; time=242; }
    else if(ratio==4) { OPTION_REG = 0x04; time=249; }
    else if(ratio==5) { OPTION_REG = 0x05; time=252; }
    else if(ratio==6) { OPTION_REG = 0x06; time=254; } 
    else if(ratio==7) { OPTION_REG = 0x07; time=255; }
}


void delay_ms_(uint8_t ms)
{  
    //OPTION_REG = 0x00;      

    while(ms--)
    {
        TMR0 = time;         // preload for ≈1 ms
        INTCON &= ~(1 << 2); // Clear TMR0IF

        while(!(INTCON & (1 << 2)));

        INTCON &= ~(1 << 2); // Clear flag
    }
}

void delay_ms(uint8_t ms)
{  
     OPTION_REG = 0x00;    
    while(ms--)
    {
        TMR0 = 153 ;         // preload for ≈1 ms
        INTCON &= ~(1 << 2); // Clear TMR0IF

        while(!(INTCON & (1 << 2)));

        INTCON &= ~(1 << 2); // Clear flag
    }
}
