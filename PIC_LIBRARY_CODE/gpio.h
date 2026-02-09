#ifndef GPIO_H
#define GPIO_H

#include <xc.h>

/* ================= BIT MACROS ================= */
#define SETIN(n,port)      (port |=  (1 << (n)))
#define SETOUT(n,port)     (port &= ~(1 << (n)))
#define SETTOGGLE(n,port)  (port ^=  (1 << (n)))

#define SETHIGH(n,port)    (port |=  (1 << (n)))
#define SETLOW(n,port)     (port &= ~(1 << (n)))

/* ================= PIN MODES ================= */
typedef enum
{
    OUTPUT = 0,
    INPUT  = 1
} pinmode_t;

/* ================= PIN STATE ================= */
typedef enum
{
    LOW = 0,
    HIGH = 1,
    TOGGLE = 2
} pinstate;

/* ================= PORT ENUM ================= */
typedef enum
{
    PORT_A = 0,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E
} port_t;

/* ================= REGISTER MAP ================= */
#define PORTA_REG (*(volatile unsigned char *)0x05)
#define TRISA_REG (*(volatile unsigned char *)0x85)
#define PORTB_REG (*(volatile unsigned char *)0x06)
#define TRISB_REG (*(volatile unsigned char *)0x86)
#define PORTC_REG (*(volatile unsigned char *)0x07)
#define TRISC_REG (*(volatile unsigned char *)0x87)
#define PORTD_REG (*(volatile unsigned char *)0x08)
#define TRISD_REG (*(volatile unsigned char *)0x88)
#define PORTE_REG (*(volatile unsigned char *)0x09)
#define TRISE_REG (*(volatile unsigned char *)0x89)

#define ADCON1   (*(volatile unsigned char*)0x9F)
#define OPTION_REG (*(volatile unsigned char *)0x81)
#define INTCON   (*(volatile unsigned char *)0x0B)
#define TMR0     (*(volatile unsigned char *)0x01)
#define STATUS   (*(volatile unsigned char *)0x03)

/* ================= POINTER ARRAYS ================= */
extern volatile unsigned char *port_s[];
extern volatile unsigned char *tris_s[];

/* ================= GPIO FUNCTIONS ================= */
void GPIO_pinmode(int pin, pinmode_t mode);
void GPIO_pinwrite(int pin, pinstate state);
int  GPIO_pinread(int pin);
void GPIO_toggle(int pin);

/* ================= DELAY ================= */
void delay_s(unsigned int sec);

/* ================= DISPLAY ================= */
void seven_segment(unsigned char val, port_t p);
void seven_segment_1(unsigned char val);

/* ================= COUNTERS ================= */
void upcounter(int val, port_t p);
void downcounter(int val, port_t p);

#endif
