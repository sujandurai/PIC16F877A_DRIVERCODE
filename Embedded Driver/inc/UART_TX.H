#include"GPIO.H"
#ifndef UART_H
#define UART_H

typedef struct
{
    unsigned char TMR1IF :1;
    unsigned char TMR2IF :1;
    unsigned char CCP1IF :1;
    unsigned char SSPIF  :1;
    unsigned char TXIF   :1;
    unsigned char RCIF   :1;
    unsigned char ADIF   :1; 
    unsigned char PSPIF  :1;
   
} PIRreg;

typedef struct
{
     unsigned char TX9D :1;
     unsigned char TRMT :1;
     unsigned char BRGH :1;
     unsigned char NOTUSED :1;
     unsigned char SYNC :1;
     unsigned char TXEN :1;
     unsigned char TX9  :1;
     unsigned char CSRC :1;
     
} TXSTAreg;

typedef struct
{
     unsigned char RX9D :1;
     unsigned char OERR :1;
     unsigned char FERR :1;
     unsigned char ADDEN:1;
     unsigned char CREN :1;
     unsigned char SREN :1;
     unsigned char RX9  :1;
     unsigned char SPEN :1;
 
} RCSTAreg;


/* Register Mapping */

#define TXSTAregs (*(volatile TXSTAreg*)0x98)
#define RCSTAregs (*(volatile RCSTAreg *)0x18)


#define SPBRG (*(volatile unsigned char*)0x99)
#define TXREG (*(volatile unsigned char*)0x19)


#define TXSTA (*(volatile unsigned char *)0x98)
#define RCSTA (*(volatile unsigned char *)0x18)


#define PIR (*(volatile unsigned char*)0x0C)
#define PIRregs (*(volatile PIRreg *)0x0C)


#endif

unsigned int baudrate(unsigned int a);
void init_tx();
void transmit(unsigned char t);
void txstr(unsigned char *);
unsigned char SPBRGrate[]={103,51,33,29,16,255,0}; // 9.615  19.231  29.412 33.333 58.824  3.906  1000.000  
unsigned select_baudrate;



void init_tx()
{
    SPBRG = SPBRGrate[0];
    TXSTAregs.TXEN = 1;
    //TXSTAregs.SYNC = 0;
    TXSTAregs.BRGH = 1; 

   
    // TXSTA|=(1<<5);
    // TXSTA|=(1<<2);
      RCSTAregs.SPEN = 1;
    //RCSTA|=(1<<7);
    //TRISC |=(1<<7);
    //TRISC |=(1<<6);
    TRISCbits.RC6=1;
    TRISCbits.RC7=1;   
}



unsigned int baudrate(unsigned int a)
{
    if(a==9600)
        select_baudrate=0;
    else if(a==19200)
        select_baudrate=1;
    else if(a==29400)
        select_baudrate=2;
    else if(a==33300)
        select_baudrate=3;
    else if(a==58800)
        select_baudrate=4;
    else if(a==3900)
        select_baudrate=5; 
    else if(a==100000)
        select_baudrate=6;
    else
        select_baudrate=7; 
    
}

void transmit(unsigned char t)
{
    TXREG=t;
        //while(!PIRreg.TXIF);
   // PIRreg.TXIF = 0;
}

void txstr(unsigned char *s)
{
    while(*s) {
        transmit(*s++);
    }
}
