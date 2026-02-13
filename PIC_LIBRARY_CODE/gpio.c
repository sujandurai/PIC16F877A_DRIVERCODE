#include "gpios.h"

volatile unsigned char *port_s[] = { &PORTA,&PORTB,&PORTC,&PORTD,&PORTE };
volatile unsigned char *tris[] = { &TRISA,&TRISB,&TRISC,&TRISD,&TRISE };

void GPIO_pinmode(int a,pinmode_t b)
{
    if(a>=33&&a<=40){ if(b==0) SETOUT(a-33,TRISB); else SETIN(a-33,TRISB); }
    else if(a>=2 && a<=7){ ADCON1 = 0x06; if(b==0) SETOUT(a-2,TRISA); else SETIN(a-2,TRISA); }
    else if(((a>14)&&(a<19))||((a>22)&&(a<27))){
        if(a<19) a=a-15; else a=a-19;
        if(b==0) SETOUT(a,TRISC); else SETIN(a,TRISC);
    }
    else if(((a > 18) && (a < 23)) || ((a > 26) && (a < 31))){
        if(a<23) a=a-19; else a=a-23;
        if(b==0) SETOUT(a,TRISD); else SETIN(a,TRISD);
    }
    else if((a>7)&&(a<11)){
        ADCON1 = 0x06;
        if(b==0) SETOUT(a-8,TRISE); else SETIN(a-8,TRISE);
    }
}

void GPIO_pinwrite(int a,pinstate b)
{
    if(a>=33&&a<=40){ if(b==0) SETLOW(a-33,PORTB); else SETHIGH(a-33,PORTB); }
    else if(((a>=2)&&(a<=7))){ if(b==0) SETLOW(a-2,PORTA); else SETHIGH(a-2,PORTA); }
    else if(((a > 14) && (a < 19)) || ((a > 22) && (a < 27))){
        if(a<19) a=a-15; else a=a-19;
        if(b==0) SETLOW(a,PORTC); else SETHIGH(a,PORTC);
    }
    else if(((a>18)&&(a<23))||((a>26)&&(a<31))){
        if(a<23) a=a-19; else a=a-23;
        if(b==0) SETLOW(a,PORTD); else SETHIGH(a,PORTD);
    }
    else if((a>7)&&(a<11)){ if(b==0) SETLOW(a-8,PORTE); else SETHIGH(a-8,PORTE); }
}

int pin_read(int a)
{
   if(a>=33&&a<=40) return(PORTB&(1<<(a-33)))?1:0;
   else if(a>=2&&a<=7) return(PORTA&(1<<(a-2)))?1:0;
   else if(((a>14)&&(a<19))||((a>22)&&(a<27))){
     if(a<19)a=a-15; else a=a-19;
     return(PORTC&(1<<a))?1:0;}
   else if(((a>18)&&(a<23))||((a>26)&&(a<31))){
      if(a<23)a=a-19;else a=a-23;
      return(PORTD&(1<<a))?1:0;}
   else if((a>7)&&(a<11)) return(PORTE&(1<<(a-8)))?1:0;
   return 0;
}

void toggle(int a)
{
    if(a>=33&&a<=40) SETTOGGLE(a-33,PORTB);
    else if(((a>=2)&&(a<=7))) SETTOGGLE(a-2,PORTA);
    else if(((a > 14) && (a < 19)) || ((a > 22) && (a < 27))){
        if(a<19)a=a-15; else a=a-19;
        SETTOGGLE(a,PORTC);}
    else if(((a>18)&&(a<23))||((a>26)&&(a<31))){
        if(a<23)a=a-19; else a=a-23;
        SETTOGGLE(a,PORTD);}
    else if((a>7)&&(a<11)) SETTOGGLE(a-8,PORTE);
}

void config_range_tris(uint8_t m,uint8_t n,triss o,pinmode_t s) // m->Lower bit  n-> High bit  port->tris or port set input 1, output 0; range (0-7)
{
       volatile unsigned char *t;
       t = tris[o];
      
    for(unsigned int i=m;i<n;i++)
    {
        if(s== OUTPUT)
        {
           *t&=~(1<<i);
        }
        else if(s==INPUT)
        {
             *t|=(1<<i);
        }
    }
      
}

void config_range_ports(int m,int n,port o,pinstate s) // m->Lower bit  n-> High bit  port->tris or port set input 1, output 0; range (0-7)
{
    
    volatile unsigned char *p;
    
       p=port_s[o];
    if(n > 8) n = 8;   // prevent overflow

    for(unsigned char i = m; i < n; i++)
    {
        if(s == LOW)
        {
            *p &= ~(1 << i);
        }
        else if(s == HIGH)
        { 
            *p |= (1 << i);
        }
        else if(s == TOGGLE)   
        {
            *p ^= (1 << i);
        }
        
    }
       return ;
}
