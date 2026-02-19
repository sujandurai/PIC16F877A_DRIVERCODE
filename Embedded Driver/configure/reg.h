
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
