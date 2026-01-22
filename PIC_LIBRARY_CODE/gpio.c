/*
 * File:   ET.c
 * Author: SUJAN D
 *
 * Created on 20 January, 2026, 5:00 PM
 */


#include"et.h"
#include<xc.h>

#define _XTAL_FREQ 20000000
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF


void main(void)
{
    int i;

    /* ---------- SET ALL GPIO AS OUTPUT ---------- */

    // PORTA : pins 2?7
    for(i = 2; i <= 7; i++)
        GPIO_pinmode(i, OUTPUT);

    // PORTB : pins 33?40
    for(i = 33; i <= 40; i++)
        GPIO_pinmode(i, OUTPUT);

    // PORTC : pins 15?18 and 23?26
    for(i = 15; i <= 18; i++)
        GPIO_pinmode(i, OUTPUT);
    for(i = 23; i <= 26; i++)
        GPIO_pinmode(i, OUTPUT);

    // PORTD : pins 19?22 and 27?30
    for(i = 19; i <= 22; i++)
        GPIO_pinmode(i, OUTPUT);
    for(i = 27; i <= 30; i++)
        GPIO_pinmode(i, OUTPUT);

    // PORTE : pins 8?10
    for(i = 8; i <= 10; i++)
        GPIO_pinmode(i, OUTPUT);

    /* ---------- LED TEST LOOP ---------- */
    while(1)
    {
        // PORTA LEDs
        for(i = 2; i <= 7; i++)
        {
            GPIO_pinwrite(i, HIGH);
            __delay_ms(300);
            GPIO_pinwrite(i, LOW);
        }

        // PORTB LEDs
        for(i = 33; i <= 40; i++)
        {
            GPIO_pinwrite(i, HIGH);
            __delay_ms(300);
            GPIO_pinwrite(i, LOW);
        }

        // PORTC LEDs
        for(i = 15; i <= 18; i++)
        {
            GPIO_pinwrite(i, HIGH);
            __delay_ms(300);
            GPIO_pinwrite(i, LOW);
        }
        for(i = 23; i <= 26; i++)
        {
            GPIO_pinwrite(i, HIGH);
            __delay_ms(300);
            GPIO_pinwrite(i, LOW);
        }

        // PORTD LEDs
        for(i = 19; i <= 22; i++)
        {
            GPIO_pinwrite(i, HIGH);
            __delay_ms(300);
            GPIO_pinwrite(i, LOW);
        }
        for(i = 27; i <= 30; i++)
        {
            GPIO_pinwrite(i, HIGH);
            __delay_ms(300);
            GPIO_pinwrite(i, LOW);
        }

        // PORTE LEDs
        for(i = 8; i <= 10; i++)
        {
            GPIO_pinwrite(i, HIGH);
            __delay_ms(300);
            GPIO_pinwrite(i, LOW);
        }
    }
}
