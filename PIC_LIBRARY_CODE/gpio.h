#ifndef GPIOS_H
#define GPIOS_H

#include <stdint.h>

/* =========================================================
   BIT MANIPULATION MACROS
   ========================================================= */

#define SET_BIT(port,n)     (port |= (1 << (n)))
#define CLEAR_BIT(port,n)   (port &= ~(1 << (n)))
#define TOGGLE_BIT(port,n)  (port ^= (1 << (n)))

#define SETIN(n,port)       (port |= (1 << (n)))     // TRIS = 1 → INPUT
#define SETOUT(n,port)      (port &= ~(1 << (n)))    // TRIS = 0 → OUTPUT

#define SETHIGH(n,port)     (port |= (1 << (n)))
#define SETLOW(n,port)      (port &= ~(1 << (n)))


/* =========================================================
   ENUM DEFINITIONS
   ========================================================= */

typedef enum
{
    OUTPUT = 0,
    INPUT  = 1
} pinmode_t;

typedef enum
{
    LOW = 0,
    HIGH = 1,
    TOGGLE = 2
} pinstate;

typedef enum
{
    PORT_A = 0,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E
} port;

typedef enum
{
    TRIS_A = 0,
    TRIS_B,
    TRIS_C,
    TRIS_D,
    TRIS_E
} triss;


/* =========================================================
   REGISTER BIT STRUCTURES
   ========================================================= */

typedef struct
{
    unsigned RA0:1;
    unsigned RA1:1;
    unsigned RA2:1;
    unsigned RA3:1;
    unsigned RA4:1;
    unsigned RA5:1;
} rega_bits;

typedef struct
{
    unsigned RB0:1;
    unsigned RB1:1;
    unsigned RB2:1;
    unsigned RB3:1;
    unsigned RB4:1;
    unsigned RB5:1;
    unsigned RB6:1;
    unsigned RB7:1;
} regb_bits;

typedef struct
{
    unsigned RC0:1;
    unsigned RC1:1;
    unsigned RC2:1;
    unsigned RC3:1;
    unsigned RC4:1;
    unsigned RC5:1;
    unsigned RC6:1;
    unsigned RC7:1;
} regc_bits;

typedef struct
{
    unsigned RD0:1;
    unsigned RD1:1;
    unsigned RD2:1;
    unsigned RD3:1;
    unsigned RD4:1;
    unsigned RD5:1;
    unsigned RD6:1;
    unsigned RD7:1;
} regd_bits;

typedef struct
{
    unsigned RE0:1;
    unsigned RE1:1;
    unsigned RE2:1;
} rege_bits;


/* =========================================================
   REGISTER DEFINITIONS  (PIC16F877A MEMORY MAP)
   ========================================================= */

#ifndef PORT_REG_DEFINED

/* PORTA */
#define PORTA      (*(volatile uint8_t *)0x05)
#define TRISA      (*(volatile uint8_t *)0x85)
#define PORTAbits  (*(volatile rega_bits *)0x05)
#define TRISAbits  (*(volatile rega_bits *)0x85)

/* PORTB */
#define PORTB      (*(volatile uint8_t *)0x06)
#define TRISB      (*(volatile uint8_t *)0x86)
#define PORTBbits  (*(volatile regb_bits *)0x06)
#define TRISBbits  (*(volatile regb_bits *)0x86)

/* PORTC */
#define PORTC      (*(volatile uint8_t *)0x07)
#define TRISC      (*(volatile uint8_t *)0x87)
#define PORTCbits  (*(volatile regc_bits *)0x07)
#define TRISCbits  (*(volatile regc_bits *)0x87)

/* PORTD */
#define PORTD      (*(volatile uint8_t *)0x08)
#define TRISD      (*(volatile uint8_t *)0x88)
#define PORTDbits  (*(volatile regd_bits *)0x08)
#define TRISDbits  (*(volatile regd_bits *)0x88)

/* PORTE */
#define PORTE      (*(volatile uint8_t *)0x09)
#define TRISE      (*(volatile uint8_t *)0x89)
#define PORTEbits  (*(volatile rege_bits *)0x09)
#define TRISEbits  (*(volatile rege_bits *)0x89)

/* OTHER IMPORTANT REGISTERS */
#define STATUS     (*(volatile uint8_t *)0x03)
#define ADCON1     (*(volatile uint8_t *)0x9F)
#define INTCON     (*(volatile uint8_t *)0x0B)
#define OPTION_REG (*(volatile uint8_t *)0x81)
#define TMR0       (*(volatile uint8_t *)0x01)

#endif


/* =========================================================
   GLOBAL PORT POINTER ARRAYS
   ========================================================= */

extern volatile uint8_t *port_s[];
extern volatile uint8_t *tris[];


/* =========================================================
   GPIO FUNCTION PROTOTYPES
   ========================================================= */

void GPIO_pinmode(int pin, pinmode_t mode);
void GPIO_pinwrite(int pin, pinstate state);
int  pin_read(int pin);
void toggle(int pin);
/* RANGE CONFIGURATION FUNCTIONS */

void config_range_ports(int low, int high, port p, pinstate state);
void config_range_tris(uint8_t low, uint8_t high, triss t, pinmode_t mode);


/* 8BIT TIMER DELAY FUNCTIONS */

void delay_s(unsigned int seconds);

/* APPLICATION  FUNCTIONS */

void seven_segment(uint8_t value, port p);
void seven_segment_1(uint8_t value);

void upcounter(int delay, port p);
void downcounter(int delay, port p);

void keypad_scan(port row, port col);
void keypad_scans(port p);

void double_port_counter(int delay, port p);
void single_port_counter(unsigned int delay);

void string_display(char arr[]);

void sequential_op(uint8_t value);
void cal_sequential(void);





#endif
