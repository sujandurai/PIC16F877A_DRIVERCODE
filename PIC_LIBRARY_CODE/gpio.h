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

#ifndef PORT
#define PORTA (*(volatile unsigned char *)0X05)
#define TRISA (*(volatile unsigned char *)0X85)
#define ADCON1 (*(volatile unsigned char*)0x9f)
#define STATUS (*(volatile unsigned char*)0x03)
#define PORTB (*(volatile unsigned char *)0X06)
#define TRISB (*(volatile unsigned char *)0X86)
#define OPTIONAL_REG (*(volatile unsigned char *)0X81)
#define  TMR0 (*(volatile unsigned char*)0x101)
#define PORTC (*(volatile unsigned char * ) 0X07)
#define TRISC (*(volatile unsigned char * )0X87)
#define PORTD (*(volatile unsigned char * )0X08)
#define TRISD (*(volatile unsigned char *)0X88)
#define PORTE (*(volatile unsigned char *)0X09)
#define TRISE (*(volatile unsigned char *)0x89)
#define INTCON (*(volatile unsigned char *)0x0B)
#define TMRO (*(volatile unsigned char *)0X01)
#endif

extern volatile unsigned char *port_s[];
extern volatile unsigned char *tris[];

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
