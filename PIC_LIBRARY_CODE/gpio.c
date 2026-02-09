#include "gpio.h"

/* POINTER TABLES */
volatile unsigned char *port_s[] = {
    &PORTA_REG, &PORTB_REG, &PORTC_REG, &PORTD_REG, &PORTE_REG
};

volatile unsigned char *tris_s[] = {
    &TRISA_REG, &TRISB_REG, &TRISC_REG, &TRISD_REG, &TRISE_REG
};

/* ================= GPIO MODE ================= */
void GPIO_pinmode(int a, pinmode_t b)
{
    if(a>=2 && a<=7){ ADCON1=0x06; (b?SETIN(a-2,TRISA_REG):SETOUT(a-2,TRISA_REG)); }
    else if(a>=33&&a<=40){ (b?SETIN(a-33,TRISB_REG):SETOUT(a-33,TRISB_REG)); }
    else if((a>14&&a<19)||(a>22&&a<27)){ a=(a<19)?a-15:a-19; (b?SETIN(a,TRISC_REG):SETOUT(a,TRISC_REG)); }
    else if((a>18&&a<23)||(a>26&&a<31)){ a=(a<23)?a-19:a-23; (b?SETIN(a,TRISD_REG):SETOUT(a,TRISD_REG)); }
    else if(a>7&&a<11){ ADCON1=0x06; (b?SETIN(a-8,TRISE_REG):SETOUT(a-8,TRISE_REG)); }
}

/* ================= GPIO WRITE ================= */
void GPIO_pinwrite(int a, pinstate b)
{
    if(a>=33&&a<=40){ if(b==HIGH)SETHIGH(a-33,PORTB_REG); else if(b==LOW)SETLOW(a-33,PORTB_REG); else SETTOGGLE(a-33,PORTB_REG);}
    else if(a>=2&&a<=7){ if(b==HIGH)SETHIGH(a-2,PORTA_REG); else if(b==LOW)SETLOW(a-2,PORTA_REG); else SETTOGGLE(a-2,PORTA_REG);}
}

/* ================= GPIO READ ================= */
int GPIO_pinread(int a)
{
    if(a>=33&&a<=40) return (PORTB_REG&(1<<(a-33)))?1:0;
    if(a>=2&&a<=7)   return (PORTA_REG&(1<<(a-2)))?1:0;
    return 0;
}

void GPIO_toggle(int a){ GPIO_pinwrite(a,TOGGLE); }

/* ================= DELAY ================= */
void delay_s(unsigned int x)
{
    OPTION_REG=0x87; STATUS=0x40; TMR0=0; INTCON&=~(1<<2);
    unsigned int c=0;
    while(c<(3*x)){ if(INTCON&(1<<2)){ INTCON&=~(1<<2); TMR0=0; c++; }}
}

/* ================= 7 SEGMENT ================= */
void seven_segment(unsigned char a, port_t n)
{
    unsigned char hex[16]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};
    *tris_s[n]=0x00;
    *port_s[n]=hex[a-'0'];
}

void seven_segment_1(unsigned char a)
{
    unsigned char hex[16]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};
    TRISD_REG=0x00; PORTD_REG=hex[a-'0'];
}

/* ================= COUNTERS ================= */
void upcounter(int a, port_t m){ for(int i=a;i>=0;i--){ seven_segment(i+'0',m); delay_s(1);} }
void downcounter(int a, port_t m){ for(int i=0;i<a;i++){ seven_segment(i+'0',m); delay_s(1);} }

void sport_counter(unsigned int x)
{
    for(int i=0;i<x;i++){ seven_segment_1((i%10)+'0'); delay_s(1); }
}

void dport_counter(int x, port_t n)
{
    *tris_s[n]=0x00;
    for(int i=0;i<x;i++){ *port_s[n]=i; delay_s(1); }
}

/* ================= KEYPAD ================= */
void keypad_scan(port_t n, port_t m)
{
    volatile unsigned char *t=tris_s[n], *p=port_s[n];
    unsigned char key[4][4]={{'7','8','9','A'},{'4','5','6','B'},{'1','2','3','C'},{'F','0','E','D'}};
    *t=0xF0; *p=0x0F;
    for(int i=0;i<4;i++){
        *p=(1<<i);
        if(*p&(1<<4)) seven_segment(key[i][0],m);
        else if(*p&(1<<5)) seven_segment(key[i][1],m);
        else if(*p&(1<<6)) seven_segment(key[i][2],m);
        else if(*p&(1<<7)) seven_segment(key[i][3],m);
    }
}

/* ================= CALCULATOR MODE ================= */
void cal_sequential(void)
{
    unsigned char key[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'C','0','=','+'}};
    unsigned int r,c;
    while(1){
        TRISD_REG=0xF0; PORTD_REG=0x0F;
        while(!(PORTD_REG&0xF0));
        r=(PORTD_REG>>4)&0x0F;
        TRISD_REG=0x0F; PORTD_REG=0xF0;
        while(!(PORTD_REG&0x0F));
        c=PORTD_REG&0x0F;
        seven_segment_1(key[c][r]);
    }
}
