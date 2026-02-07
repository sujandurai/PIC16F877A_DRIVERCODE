/******************** MACROS ********************/
#define  SETIN(n,port)   (port |=  (1 << (n)))
#define  SETOUT(n,port)  (port &= ~(1 << (n)))
#define  SETHIGH(n,port) (port |=  (1 << (n)))
#define  SETLOW(n,port)  (port &= ~(1 << (n)))

/******************** TYPEDEFS ********************/
typedef enum
{
    OUTPUT = 0,
    INPUT  = 1,
} pinmode_t;

typedef enum
{
    HIGH = 1,
    LOW  = 0
} pinstate;

typedef enum
{
    PORTA = 1,
    PORTB = 2,
    PORTC = 3,
    PORTD = 4,
    PORTE = 5
} portmode;

/******************** REGISTER DEFINITIONS ********************/
#ifndef PORT
#define PORTA (*(volatile unsigned char *)0x05)
#define TRISA (*(volatile unsigned char *)0x85)
#define ADCON1 (*(volatile unsigned char *)0x9F)
#define STATUS (*(volatile unsigned char *)0x03)

#define PORTB (*(volatile unsigned char *)0x06)
#define TRISB (*(volatile unsigned char *)0x86)

#define PORTC (*(volatile unsigned char *)0x07)
#define TRISC (*(volatile unsigned char *)0x87)

#define PORTD (*(volatile unsigned char *)0x08)
#define TRISD (*(volatile unsigned char *)0x88)

#define PORTE (*(volatile unsigned char *)0x09)
#define TRISE (*(volatile unsigned char *)0x89)

#define OPTIONAL_REG (*(volatile unsigned char *)0x81)
#define TMR0 (*(volatile unsigned char *)0x101)
#define TMRO (*(volatile unsigned char *)0x01)
#define INTCON (*(volatile unsigned char *)0x0B)
#endif

/******************** GPIO FUNCTIONS ********************/





void GPIO_pinmode(int a, pinmode_t b);
void GPIO_pinwrite(int a, pinstate b);

void delay_s(unsigned int x);

void seven_segment(unsigned char a);
void seven_segment_1(unsigned char a);

void upcounter(int a);
void downcounter(int a);

void sport_counter(int x);
void dport_counter(unsigned int x);

void string_display(char arr[]);

void keypad_scan(void);

void sequential_op(unsigned char a);
void cal_sequential(void);



