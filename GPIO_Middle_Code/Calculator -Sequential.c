#define _XTAL_FREQ 20000000

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#include <xc.h>


/* =====================================================
   GLOBAL VARIABLES
   ===================================================== */

unsigned int n=0;
unsigned int sum=0;
unsigned int sign=0;


/* =====================================================
   7 SEGMENT HEX VALUES
   ===================================================== */

unsigned char hex_digits[10] =
{
    0xC0,0xF9,0xA4,0xB0,
    0x99,0x92,0x82,0xF8,
    0x80,0x90
};


/* =====================================================
   CALCULATOR FUNCTION
   ===================================================== */

void cal_sequential(unsigned char a)
{
    TRISC = 0x00;
    TRISB = 0x00;

    /* NUMBER INPUT */
    if(a >= '0' && a <= '9')
    {
        n = n*10 + a - '0';
        PORTC = hex_digits[a-'0'];
    }

    /* ADDITION */
    else if(a=='+')
    {
        sum = sum + n;
        n = 0;
        sign = 1;
    }

    /* SUBTRACTION */
    else if(a=='-')
    {
        sum = sum - n;
        n = 0;
        sign = 2;
    }

    /* MULTIPLICATION */
    else if(a=='*')
    {
        if(sum==0) sum=1;
        sum = sum * n;
        n = 0;
        sign = 3;
    }

    /* DIVISION */
    else if(a=='/')
    {
        if(n!=0) sum = sum / n;
        n = 0;
        sign = 4;
    }

    /* RESULT */
    else if(a=='=')
    {
        if(sign==1) sum = sum + n;
        else if(sign==2) sum = sum - n;
        else if(sign==3) sum = sum * n;
        else if(sign==4 && n!=0) sum = sum / n;
        else sum = sum + n;

        if(sum > 9)
        {
            PORTC = hex_digits[sum % 10];
            PORTB = hex_digits[(sum/10) % 10];
        }
        else
        {
            PORTC = hex_digits[sum];
            PORTB = 0xC0;
        }

        sum=0;
        n=0;
        sign=0;
    }

    /* CLEAR */
    else if(a=='C')
    {
        sum=0;
        n=0;
        sign=0;

        PORTC = 0xC0;
        PORTB = 0xC0;
    }
}


/* =====================================================
   KEYPAD SCAN FUNCTION
   ===================================================== */

void keypad_scan(void)
{
    unsigned int bit1=-1,bit2=-1;

    unsigned char keyboard[4][4] =
    {
        {'7','8','9','/'},
        {'4','5','6','*'},
        {'1','2','3','-'},
        {'C','0','=','+'}
    };

    while(1)
    {
        /* COLUMN SCAN */
        while(1)
        {
            TRISD = 0xF0;
            PORTD = 0x0F;

            if(PORTD & (1<<4)){bit1=0;break;}
            else if(PORTD & (1<<5)){bit1=1;break;}
            else if(PORTD & (1<<6)){bit1=2;break;}
            else if(PORTD & (1<<7)){bit1=3;break;}
        }

        /* ROW SCAN */
        while(1)
        {
            TRISD = 0x0F;
            PORTD = 0xF0;

            if(PORTD & (1<<0)){bit2=0;break;}
            else if(PORTD & (1<<1)){bit2=1;break;}
            else if(PORTD & (1<<2)){bit2=2;break;}
            else if(PORTD & (1<<3)){bit2=3;break;}
        }

        cal_sequential(keyboard[bit2][bit1]);

        __delay_ms(200);   // debounce
    }
}


/* =====================================================
   MAIN FUNCTION
   ===================================================== */

void main(void)
{
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0xFF;

    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;

    keypad_scan();   // start calculator
}
