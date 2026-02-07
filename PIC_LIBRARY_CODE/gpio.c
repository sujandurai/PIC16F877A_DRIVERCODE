#include"t1.h"

void GPIO_pinmode(int a, pinmode_t b)
{
    if (a >= 33 && a <= 40)
    {
        if (b == 0) SETOUT(a - 33, TRISB);
        else SETIN(a - 33, TRISB);
    }
    else if (a >= 2 && a <= 7)
    {
        ADCON1 = 0x06;
        if (b == 0) SETOUT(a - 2, TRISA);
        else SETIN(a - 2, TRISA);
    }
    else if (((a > 14) && (a < 19)) || ((a > 22) && (a < 27)))
    {
        if (a < 19) a = a - 15;
        else a = a - 19;
        if (b == 0) SETOUT(a, TRISC);
        else SETIN(a, TRISC);
    }
    else if (((a > 18) && (a < 23)) || ((a > 26) && (a < 31)))
    {
        if (a < 23) a = a - 19;
        else a = a - 23;
        if (b == 0) SETOUT(a, TRISD);
        else SETIN(a, TRISD);
    }
    else if ((a > 7) && (a < 11))
    {
        ADCON1 = 0x06;
        if (b == 0) SETOUT(a - 8, TRISE);
        else SETIN(a - 8, TRISE);
    }
}

void GPIO_pinwrite(int a, pinstate b)
{
    if (a >= 33 && a <= 40)
    {
        if (b == 0) SETLOW(a - 33, PORTB);
        else SETHIGH(a - 33, PORTB);
    }
    else if (a >= 2 && a <= 7)
    {
        if (b == 0) SETLOW(a - 2, PORTA);
        else SETHIGH(a - 2, PORTA);
    }
    else if (((a > 14) && (a < 19)) || ((a > 22) && (a < 27)))
    {
        if (a < 19) a = a - 15;
        else a = a - 19;
        if (b == 0) SETLOW(a, PORTC);
        else SETHIGH(a, PORTC);
    }
    else if (((a > 18) && (a < 23)) || ((a > 26) && (a < 31)))
    {
        if (a < 23) a = a - 19;
        else a = a - 23;
        if (b == 0) SETLOW(a, PORTD);
        else SETHIGH(a, PORTD);
    }
    else if ((a > 7) && (a < 11))
    {
        if (b == 0) SETLOW(a - 8, PORTE);
        else SETHIGH(a - 8, PORTE);
    }
}

/******************** DELAY ********************/
void delay_s(unsigned int x)
{
    OPTIONAL_REG = 0x00;
    unsigned int count = 0;
    OPTIONAL_REG = 0x87;
    STATUS = 0x40;
    TMR0 = 0x00;
    INTCON &= ~(1 << 2);

    while (count < (3 * x))
    {
        if (INTCON & (1 << 2))
        {
            INTCON &= ~(1 << 2);
            TMR0 = 0;
            count++;
        }
    }
}

/******************** SEVEN SEGMENT ********************/
void seven_segment(unsigned char a)
{
    unsigned char hex_digits[16] =
    {
        0xC0,0xF9,0xA4,0xB0,
        0x99,0x92,0x82,0xF8,
        0x80,0x90,0x88,0x83,
        0xC6,0xA1,0x86,0x8E
    };

    TRISC = 0x00;
    int i = a - '0';

    if (i >= 0 && i <= 9) PORTC = hex_digits[i];
    else if (i > 17 && i <= 23)
    {
        i = i - 7;
        PORTC = hex_digits[i];
    }
}

void seven_segment_1(unsigned char a)
{
    unsigned char hex_digits[16] =
    {
        0xC0,0xF9,0xA4,0xB0,
        0x99,0x92,0x82,0xF8,
        0x80,0x90,0x88,0x83,
        0xC6,0xA1,0x86,0x8E
    };

    TRISD = 0x00;
    int i = a - '0';

    if (i >= 0 && i <= 9) PORTD = hex_digits[i];
    else if (i > 17 && i <= 23)
    {
        i = i - 7;
        PORTD = hex_digits[i];
    }
}

/******************** COUNTERS ********************/
void upcounter(int a)
{
    for (int i = a; i >= 0; i--)
    {
        char n = (unsigned char)i + '0';
        seven_segment(n);
        delay_s(1);
    }
}

void downcounter(int a)
{
    for (int i = 0; i < a; i++)
    {
        char n = (unsigned char)i + '0';
        seven_segment_1(n);
        delay_s(1);
    }
}

/******************** STRING DISPLAY ********************/
void string_display(char arr[])
{
    unsigned char alpha_CA[26] =
    {0x88,0x83,0xC6,0xA1,0x86,0x8E,0x82,0x89,0xF9,0xE1,0x8A,0xC7,
     0xAA,0xAB,0xC0,0x8C,0x98,0xAF,0x92,0x87,0xC1,0xE3,0x95,0x89,
     0x91,0xA4};

    TRISD = 0x00;
    for (int i = 0; arr[i] != '\0'; i++)
    {
        int j = arr[i] - 'A';
        PORTD = alpha_CA[j];
        delay_s(3);
    }
}
/******************** KEYPAD SCAN ********************/
void keypad_scan(void)
{
    unsigned int bit1 = -1, bit2 = -1;

    unsigned char keyboard[4][4] =
    {
        {'7','8','9','A'},
        {'4','5','6','B'},
        {'1','2','3','C'},
        {'F','0','E','D'}
    };

    TRISD = 0xF0;
    PORTD = 0x0F;

    for (int i = 0; i < 4; i++)
    {
        PORTD = (char)(1 << i);

        if ((PORTD & (1 << 4)))
        {
            seven_segment(keyboard[i][0]);
        }
        else if ((PORTD & (1 << 5)))
        {
            seven_segment(keyboard[i][1]);
        }
        else if ((PORTD & (1 << 6)))
        {
            seven_segment(keyboard[i][2]);
        }
        else if ((PORTD & (1 << 7)))
        {
            seven_segment(keyboard[i][3]);
        }
    }
}

/******************** SEQUENTIAL OPERATION ********************/
void sequential_op(unsigned char a)
{
    unsigned int n = 0;
    unsigned int sum = 0;
    unsigned int set = 0, s = 0;
    unsigned int m = 0, mul = 1, div = 1;
    unsigned int sign = 0;

    unsigned char hex_digits[16] =
    {
        0xC0,0xF9,0xA4,0xB0,
        0x99,0x92,0x82,0xF8,
        0x80,0x90,0x88,0x83,
        0xC6,0xA1,0x86,0x8E
    };

    TRISC = 0x00;
    TRISB = 0x00;
    PORTB = 0xC0;

    if (a >= '0' && a <= '9')
    {
        n = n * 10 + a - '0';
        PORTC = hex_digits[a - '0'];
    }

    else if (a == '+')
    {
        if (sign == 1) { sum = sum + n; }
        else if (sign == 2) { sum = sum - n; }
        else if (sign == 3) { sum = mul * n * sum; }
        else if (sign == 4) { sum = (div * sum) / n; }
        else { sum = sum + n; }

        n = 0;
        set = 1;
        m = 1; s = 1;
        sign = 1;
    }

    else if (a == '-')
    {
        if (sign == 1) { sum = sum + n; }
        else if (sign == 2) { sum = sum - n; }
        else if (sign == 3) { sum = mul * n * sum; }
        else if (sign == 4) { sum = (sum * div) / n; }
        else
        {
            if (m <= 0) sum = n - sum;
            else sum = sum - n;
        }

        n = 0;
        m = 1; s = 1;
        set = 2;
        sign = 2;
    }

    else if (a == '*')
    {
        if (sign == 1) { sum = sum + n; }
        else if (sign == 2) { sum = sum - n; }
        else if (sign == 3) { sum = mul * n * sum; }
        else if (sign == 4) { sum = (sum * div) / n; }
        else { sum = mul * n; }

        set = 3;
        n = 0;
        m = 1; s = 1;
        sign = 3;
    }

    else if (a == '/')
    {
        if (sign == 1) { sum = sum + n; }
        else if (sign == 2) { sum = sum - n; }
        else if (sign == 3) { sum = mul * n * sum; }
        else if (sign == 4) { sum = (div * sum) / n; }
        else
        {
            if (s <= 0) sum = n / div;
            else sum = (sum * div) / 1;
        }

        set = 4;
        n = 0;
        s = 1; m = 1;
        sign = 4;
    }

    else if (a == '=')
    {
        if (set == 1 || set == 0) sum = sum + n;
        else if (set == 2) sum = sum - n;
        else if (set == 3)
        {
            if (sum > 0) sum = mul * n * sum;
            else sum = mul * n;
        }
        else if (set == 4) sum = (div * sum) / n;

        if (sum > 9)
        {
            PORTC = hex_digits[sum % 10];
            PORTB = hex_digits[sum / 10];

            sum = 0; m = 0; set = 0; s = 0;
            div = 1; sign = 0; mul = 1;
        }
        else
        {
            PORTC = hex_digits[sum];
            PORTB = 0xC0;

            sum = 0; m = 0; set = 0; s = 0;
            div = 1; sign = 0; mul = 1;
        }
    }

    else if (a == 'C')
    {
        sum = 0;
        PORTC = 0xC0;
        PORTB = 0xC0;
        n = 0;
        mul = 1;
        div = 1;
        s = 0;
        sign = 0;
    }
}

/******************** CALCULATOR SEQUENTIAL ********************/
void cal_sequential(void)
{
    unsigned int bit1 = -1, bit2 = -1;

    unsigned char keyboard[4][4] =
    {
        {'7','8','9','/'},
        {'4','5','6','*'},
        {'1','2','3','-'},
        {'C','0','=','+'}
    };

    while (1)
    {
        while (1)
        {
            TRISD = 0xF0;
            PORTD = 0x0F;

            if ((PORTD & (1 << 4)) != 0) { bit1 = 0; break; }
            else if ((PORTD & (1 << 5)) != 0) { bit1 = 1; break; }
            else if ((PORTD & (1 << 6)) != 0) { bit1 = 2; break; }
            else if ((PORTD & (1 << 7)) != 0) { bit1 = 3; break; }
            else {;}
        }

        while (1)
        {
            TRISD = 0x0F;
            PORTD = 0xF0;

            if ((PORTD & (1 << 0)) != 0) { bit2 = 0; break; }
            else if ((PORTD & (1 << 1)) != 0) { bit2 = 1; break; }
            else if ((PORTD & (1 << 2)) != 0) { bit2 = 2; break; }
            else if ((PORTD & (1 << 3)) != 0) { bit2 = 3; break; }
            else {;}
        }
        sequential_op(keyboard[bit2][bit1]);
    }
}


