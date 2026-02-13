#ifndef GPIOS_H
#define GPIOS_H

#include <xc.h>

#define  SETIN(n,port)  (port|=1<<(n))
#define  SETOUT(n,port) (port&=~(1<<(n)))
#define  SETTOGGLE(n,port) (port^=(1<<(n)))
#define  SETHIGH(n,port) (port|=1<<(n))
#define  SETLOW(n,port)  (port&=~(1<<(n)))

typedef enum { OUTPUT = 0, INPUT  = 1 } pinmode_t;
typedef enum { HIGH = 1, LOW = 0, TOGGLE= 2 } pinstate;
typedef enum { PORT_A = 0, PORT_B, PORT_C, PORT_D, PORT_E } port;
typedef enum
{
    
    TRIS_A = 0,
    TRIS_B = 1,
    TRIS_C = 2, 
    TRIS_D = 3, 
    TRIS_E = 4,   
}triss;
typedef struct {
    unsigned char RA0:1;
    unsigned char RA1:1;
    unsigned char RA2:1;
    unsigned char RA3:1;
    unsigned char RA4:1;
    unsigned char RA5:1;
    
} rega_bits;
typedef struct {
    unsigned char RB0:1;
    unsigned char RB1:1;
    unsigned char RB2:1;
    unsigned char RB3:1;
    unsigned char RB4:1;
    unsigned char RB5:1;
    unsigned char RB6:1;
    unsigned char RB7:1;
 
} regb_bits;
typedef struct {
    unsigned char RC0:1;
    unsigned char RC1:1;
    unsigned char RC2:1;
    unsigned char RC3:1;
    unsigned char RC4:1;
    unsigned char RC5:1;
    unsigned char RC6:1;
    unsigned char RC7:1;
 
} regc_bits;

typedef struct {
    unsigned char RD0:1;
    unsigned char RD1:1;
    unsigned char RD2:1;
    unsigned char RD3:1;
    unsigned char RD4:1;
    unsigned char RD5:1;
    unsigned char RD6:1;
    unsigned char RD7:1;
 
} regd_bits;

typedef struct {
    unsigned char RE0:1;
    unsigned char RE1:1;
    unsigned char RE2:1;
   
} rege_bits;

#define  SETHIGH(n,port) (port|=1<<(n))
#define  SETLOW(n,port)  (port&=~(1<<(n)))

#ifndef PORT
#define PORTA (*(volatile unsigned char *)0X05)
#define PORTAbits (*(volatile rega_bits*)0X05)
#define TRISA (*(volatile unsigned char *)0X85 )  //PORT A//
#define TRISAbits (*(volatile rega_bits *)0X85)
#define ADCON1 (*(volatile unsigned char*)0x9f)
#define STATUS (*(volatile unsigned char*)0x03)

#define PORTB (*(volatile unsigned char *)0X06)
#define PORTBbits (*(volatile unsigned regb_bits *)0X06)
#define TRISB (*(volatile unsigned char *)0X86 )  //PORT B//
#define TRISBbits (*(volatile unsigned regb_bits *)0X86 ) 
#define OPTIONAL_REG (*(volatile unsigned char *)0X81)

#define  TMR0 (*(volatile unsigned char*)0x101)

#define PORTC (*(volatile unsigned char * ) 0X07)
#define PORTCbits (*(volatile unsigned regc_bits * ) 0X07)
#define TRISC (*(volatile unsigned char * )0X87)  //PORT C//
#define TRISCbits (*(volatile unsigned regc_bits * )0X87) 

#define PORTD (*(volatile unsigned char * )0X08)
#define PORTDbits (*(volatile unsigned regd_bits * )0X08)
#define TRISD (*(volatile unsigned char *)0X88 )  //PORT D//
#define TRISDbits (*(volatile unsigned regd_bits *)0X88 )  

#define PORTE (*(volatile unsigned char *)0X09)
#define PORTEbits (*(volatile unsigned rege_bits *)0X09)
#define TRISE (*(volatile unsigned char *)0x89)   //PORT E//
#define TRISEbits (*(volatile unsigned rege_bits *)0x89) 
#define INTCON (*(volatile unsigned char *)0x0B)
#define TMRO (*(volatile unsigned char *)0X01)

#endif

volatile unsigned char *port_s[] = { &PORTA,&PORTB,&PORTC,&PORTD,&PORTE };
volatile unsigned char *tris[] = { &TRISA,&TRISB,&TRISC,&TRISD,&TRISE };


void GPIO_pinmode(int a,pinmode_t b);
void GPIO_pinwrite(int a,pinstate b);
int pin_read(int a);
void toggle(int a);
void delay_s(unsigned int x);
void seven_segment(unsigned char a,port n);
void seven_segment_1(unsigned char a);
void upcounter(int a,port m);
void downcounter(int a,port m);
void keypad_scan(port n,port m);
void dport_counter(int x,port n);
void sport_counter(unsigned int x);
void string_display(char arr[]);
void sequential_op(unsigned char a);
void cal_sequential(void);
void keypad_scans(port n);

#endif
