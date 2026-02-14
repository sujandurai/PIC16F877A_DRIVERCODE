#include "gpios.h"

/* =========================================================
   GLOBAL POINTER ARRAYS
   ========================================================= */

volatile unsigned char *port_s[] = { &PORTA, &PORTB, &PORTC, &PORTD, &PORTE };
volatile unsigned char *tris[]   = { &TRISA, &TRISB, &TRISC, &TRISD, &TRISE };


/* =========================================================
   GPIO PIN MODE
   ========================================================= */

void GPIO_pinmode(int pin, pinmode_t mode)
{
    /* ---------- PORTB ---------- */
    if (pin >= 33 && pin <= 40)
    {
        if (mode == OUTPUT)
            SETOUT(pin - 33, TRISB);
        else
            SETIN(pin - 33, TRISB);
    }

    /* ---------- PORTA ---------- */
    else if (pin >= 2 && pin <= 7)
    {
        ADCON1 = 0x06;

        if (mode == OUTPUT)
            SETOUT(pin - 2, TRISA);
        else
            SETIN(pin - 2, TRISA);
    }

    /* ---------- PORTC ---------- */
    else if (((pin > 14) && (pin < 19)) || ((pin > 22) && (pin < 27)))
    {
        if (pin < 19)
            pin -= 15;
        else
            pin -= 19;

        if (mode == OUTPUT)
            SETOUT(pin, TRISC);
        else
            SETIN(pin, TRISC);
    }

    /* ---------- PORTD ---------- */
    else if (((pin > 18) && (pin < 23)) || ((pin > 26) && (pin < 31)))
    {
        if (pin < 23)
            pin -= 19;
        else
            pin -= 23;

        if (mode == OUTPUT)
            SETOUT(pin, TRISD);
        else
            SETIN(pin, TRISD);
    }

    /* ---------- PORTE ---------- */
    else if ((pin > 7) && (pin < 11))
    {
        ADCON1 = 0x06;

        if (mode == OUTPUT)
            SETOUT(pin - 8, TRISE);
        else
            SETIN(pin - 8, TRISE);
    }

    /* ---------- INVALID PIN ---------- */
    else
    {
        // Do nothing or error handling
    }
}


/* =========================================================
   GPIO WRITE
   ========================================================= */

void GPIO_pinwrite(int pin, pinstate state)
{
    if (pin >= 33 && pin <= 40)
    {
        if (state == LOW)
            SETLOW(pin - 33, PORTB);
        else
            SETHIGH(pin - 33, PORTB);
    }

    else if (pin >= 2 && pin <= 7)
    {
        if (state == LOW)
            SETLOW(pin - 2, PORTA);
        else
            SETHIGH(pin - 2, PORTA);
    }

    else if (((pin > 14) && (pin < 19)) || ((pin > 22) && (pin < 27)))
    {
        if (pin < 19)
            pin -= 15;
        else
            pin -= 19;

        if (state == LOW)
            SETLOW(pin, PORTC);
        else
            SETHIGH(pin, PORTC);
    }

    else if (((pin > 18) && (pin < 23)) || ((pin > 26) && (pin < 31)))
    {
        if (pin < 23)
            pin -= 19;
        else
            pin -= 23;

        if (state == LOW)
            SETLOW(pin, PORTD);
        else
            SETHIGH(pin, PORTD);
    }

    else if ((pin > 7) && (pin < 11))
    {
        if (state == LOW)
            SETLOW(pin - 8, PORTE);
        else
            SETHIGH(pin - 8, PORTE);
    }

    else
    {
        // Invalid pin
    }
}


/* =========================================================
   GPIO READ
   ========================================================= */

int pin_read(int pin)
{
    if (pin >= 33 && pin <= 40)
        return (PORTB & (1 << (pin - 33))) ? 1 : 0;

    else if (pin >= 2 && pin <= 7)
        return (PORTA & (1 << (pin - 2))) ? 1 : 0;

    else if (((pin > 14) && (pin < 19)) || ((pin > 22) && (pin < 27)))
    {
        if (pin < 19) pin -= 15;
        else pin -= 19;

        return (PORTC & (1 << pin)) ? 1 : 0;
    }

    else if (((pin > 18) && (pin < 23)) || ((pin > 26) && (pin < 31)))
    {
        if (pin < 23) pin -= 19;
        else pin -= 23;

        return (PORTD & (1 << pin)) ? 1 : 0;
    }

    else if ((pin > 7) && (pin < 11))
        return (PORTE & (1 << (pin - 8))) ? 1 : 0;

    else
        return 0;
}


/* =========================================================
   TOGGLE
   ========================================================= */

void toggle(int pin)
{
    if (pin >= 33 && pin <= 40)
        SETTOGGLE(pin - 33, PORTB);

    else if (pin >= 2 && pin <= 7)
        SETTOGGLE(pin - 2, PORTA);

    else if (((pin > 14) && (pin < 19)) || ((pin > 22) && (pin < 27)))
    {
        if (pin < 19) pin -= 15;
        else pin -= 19;

        SETTOGGLE(pin, PORTC);
    }

    else if (((pin > 18) && (pin < 23)) || ((pin > 26) && (pin < 31)))
    {
        if (pin < 23) pin -= 19;
        else pin -= 23;

        SETTOGGLE(pin, PORTD);
    }

    else if ((pin > 7) && (pin < 11))
        SETTOGGLE(pin - 8, PORTE);

    else
    {
        // Invalid pin
    }
}


/* =========================================================
   RANGE TRIS CONFIG
   ========================================================= */

void config_range_tris(uint8_t low, uint8_t high, triss t, pinmode_t mode)
{
    volatile unsigned char *reg = tris[t];

    for (uint8_t i = low; i < high; i++)
    {
        if (mode == OUTPUT)
            *reg &= ~(1 << i);
        else
            *reg |= (1 << i);
    }
}


/* =========================================================
   RANGE PORT CONFIG
   ========================================================= */

void config_range_ports(int low, int high, port p, pinstate state)
{
    volatile unsigned char *reg = port_s[p];

    if (high > 8) high = 8;

    for (int i = low; i < high; i++)
    {
        if (state == LOW)
            *reg &= ~(1 << i);

        else if (state == HIGH)
            *reg |= (1 << i);

        else if (state == TOGGLE)
            *reg ^= (1 << i);
    }
}
