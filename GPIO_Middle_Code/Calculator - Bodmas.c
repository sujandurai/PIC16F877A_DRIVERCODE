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
#include <stdio.h>
#include <string.h>
#include <ctype.h>


/* =========================================================
   GLOBAL VARIABLES
   ========================================================= */

unsigned int i = 0;
unsigned int j = 0;

int num = 0;
int lastValue = 0;
int result = 0;

char op = '+';
unsigned char expBuffer[95];


/* =========================================================
   7 SEGMENT HEX TABLE
   ========================================================= */

const unsigned char hex_digits[16] =
{
    0xC0,0xF9,0xA4,0xB0,
    0x99,0x92,0x82,0xF8,
    0x80,0x90,0x88,0x83,
    0xC6,0xA1,0x86,0x8E
};


/* =========================================================
   RESET CALCULATOR
   ========================================================= */

void resetCalculator()
{
    i = 0;
    j = 0;
    num = 0;
    lastValue = 0;
    result = 0;
    op = '+';

    for(int k = 0; k < 95; k++)
        expBuffer[k] = 0;

    PORTB = 0xC0;
    PORTC = 0xC0;
}


/* =========================================================
   DISPLAY RESULT ON 2 DIGIT 7 SEGMENT
   ========================================================= */

void displayResult(int value)
{
    TRISB = 0x00;
    TRISC = 0x00;

    PORTC = hex_digits[value % 10];
    PORTB = hex_digits[(value / 10) % 10];
}


/* =========================================================
   EXPRESSION EVALUATION (BODMAS BASIC)
   ========================================================= */

void evaluateExpression(unsigned char exp[])
{
    while(1)
    {
        /* -------- NUMBER BUILD -------- */
        if(exp[i] >= '0' && exp[i] <= '9')
        {
            num = num * 10 + (exp[i] - '0');
        }

        /* -------- OPERATOR DETECT -------- */
        if(exp[i]=='+' || exp[i]=='-' || exp[i]=='*' || exp[i]=='/' || exp[i]=='\0')
        {
            switch(op)
            {
                case '+':
                    result += lastValue;
                    lastValue = num;
                    break;

                case '-':
                    result += lastValue;
                    lastValue = -num;
                    break;

                case '*':
                    lastValue = lastValue * num;
                    break;

                case '/':
                    if(num != 0)
                        lastValue = lastValue / num;
                    break;
            }

            op = exp[i];
            num = 0;
        }

        if(exp[i] == '\0')
            break;

        i++;
    }

    result += lastValue;

    displayResult(result);
}


/* =========================================================
   PROCESS KEY INPUT
   ========================================================= */

void processKey(unsigned char key)
{
    TRISC = 0x00;

    /* ---------- EQUAL ---------- */
    if(key == '=')
    {
        PORTC = 0x86;        // '=' symbol
        expBuffer[j] = '\0';
        evaluateExpression(expBuffer);
    }

    /* ---------- CLEAR ---------- */
    else if(key == 'C')
    {
        resetCalculator();
        return;
    }

    /* ---------- NORMAL INPUT ---------- */
    else
    {
        if(key >= '0' && key <= '9')
            PORTC = hex_digits[key - '0'];

        else if(key == '*')
            PORTC = 0xAB;

        else if(key == '+')
            PORTC = 0x8C;

        else if(key == '-')
            PORTC = 0x92;

        else if(key == '/')
            PORTC = 0xA1;

        expBuffer[j++] = key;
    }
}


/* =========================================================
   KEYPAD SCAN (4x4)
   ========================================================= */

void keypadTask()
{
    int col = -1;
    int row = -1;

    const unsigned char keypad[4][4] =
    {
        {'7','8','9','/'},
        {'4','5','6','*'},
        {'1','2','3','-'},
        {'C','0','=','+'}
    };

    while(1)
    {
        /* -------- COLUMN DETECT -------- */
        while(1)
        {
            TRISD = 0xF0;
            PORTD = 0x0F;

            if(PORTD & (1<<4)) { col = 0; break; }
            if(PORTD & (1<<5)) { col = 1; break; }
            if(PORTD & (1<<6)) { col = 2; break; }
            if(PORTD & (1<<7)) { col = 3; break; }
        }

        /* -------- ROW DETECT -------- */
        while(1)
        {
            TRISD = 0x0F;
            PORTD = 0xF0;

            if(PORTD & (1<<0)) { row = 0; break; }
            if(PORTD & (1<<1)) { row = 1; break; }
            if(PORTD & (1<<2)) { row = 2; break; }
            if(PORTD & (1<<3)) { row = 3; break; }
        }

        processKey(keypad[row][col]);
        __delay_ms(250);   // debounce
    }
}


/* =========================================================
   MAIN
   ========================================================= */

void main(void)
{
    resetCalculator();

    while(1)
    {
        keypadTask();
    }
}
