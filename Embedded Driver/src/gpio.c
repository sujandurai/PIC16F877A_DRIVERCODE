#include "lcd.h"


volatile unsigned char *port_s[] = { &PORTA,&PORTB,&PORTC,&PORTD,&PORTE };
volatile unsigned char *tris[]   = { &TRISA,&TRISB,&TRISC,&TRISD,&TRISE };

volatile unsigned int *directions[] = { SHIFT_DISPLAY_LEFT , SHIFT_DISPLAY_RIGHT };

volatile unsigned char positions[2][16] =
{
    {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,
        0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F
    },
    {
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,
        0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF
    }
};

volatile unsigned int display_settings[] =
{
    DISPLAY_OFF,
    DISPLAY_ON_CURSOR_OFF,
    DISPLAY_ON_BLINK,
    DISPLAY_ON_CURSOR,
    DISPLAY_ON_CUR_BLINK
};

#define RS PORTCbits.RC0
#define RW PORTCbits.RC1
#define EN PORTCbits.RC2

#define delay for(int j=0;j<1000;j++)

unsigned int q = 1;
uint8_t d = 0;


/* ================= BASIC ================= */

void lcd_select_port(port m)
{
    q = m;
}

void lcd_clear(port n)
{
    lcd_cmd(CLEAR_DISPLAY,n);
    lcd_cmd(CURSOR_RETURN,n);
}

void lcd_set_display(uint8_t disptype)
{
    d = disptype;
}

void lcd_cmd(unsigned char a, port n)
{
    unsigned char *t,*p;

    t = tris[n];
    p = port_s[n];

    *t = 0x00;
    *p = a;

    RS = 0;
    RW = 0;
    EN = 1;
    delay;
    EN = 0;
}

void lcd_data(unsigned char a, port n)
{
    unsigned char *t,*p;

    t = tris[n];
    p = port_s[n];

    *t = 0x00;
    *p = a;

    RS = 1;
    RW = 0;
    EN = 1;
    delay;
    EN = 0;
}

void lcd_print(unsigned char *s, port n)
{
    while(*s)
    {
        lcd_data(*s++, n);
    }
}


/* ================= DISPLAY FUNCTIONS ================= */

void string_disp_shift_2line_5X10(unsigned char sentence[], direction m)
{
    TRISCbits.RC0=0;
    TRISCbits.RC1=0;
    TRISCbits.RC2=0;

    uint8_t n=q;

    lcd_cmd(SET_DDRAM_ADDRESS2,n);
    lcd_cmd(DISPLAY_8BIT_2LINE_1FONT,n);
    lcd_cmd(display_settings[d],n);
    lcd_cmd(directions[m],n);
    lcd_cmd(0xC0,n);

    lcd_print(sentence,n);
}

void string_disp_shift_2line_5X7(unsigned char sentence[], port n, direction m)
{
    TRISCbits.RC0=0;
    TRISCbits.RC1=0;
    TRISCbits.RC2=0;

    lcd_cmd(SET_DDRAM_ADDRESS1,n);
    lcd_cmd(DISPLAY_8BIT_2LINE_1FONT,n);
    lcd_cmd(display_settings[d],n);
    lcd_cmd(directions[m],n);
    lcd_cmd(0xC4,n);

    lcd_print(sentence,n);
}


/* ================= SCROLL ================= */

void lcd_scrollText_2Line_5x10(unsigned char sentence[], port n, direction m, uint8_t row, uint8_t col)
{
    TRISCbits.RC0=0;
    TRISCbits.RC1=0;
    TRISCbits.RC2=0;

    lcd_clear(n);
    lcd_cmd(DISPLAY_8BIT_2LINE_1FONT,n);
    lcd_cmd(display_settings[d],n);
    lcd_cmd(positions[row][col],n);
    lcd_print(sentence,n);

    while(1)
    {
        if(m==RIGHT)
            lcd_cmd(0x1C,n);
        else
            lcd_cmd(0x18,n);

        delay;
    }
}

void lcd_scrollText_2Line_5x7(unsigned char sentence[], port n, direction m, uint8_t row, uint8_t col)
{
    lcd_scrollText_2Line_5x10(sentence,n,m,row,col);
}


/* ================= OTHER EFFECTS ================= */

void lcd_displayPaged_2Line(unsigned char sentence[], port n)
{
    TRISCbits.RC0=0;
    TRISCbits.RC1=0;
    TRISCbits.RC2=0;

    lcd_cmd(DISPLAY_8BIT_2LINE_1FONT,n);
    lcd_cmd(display_settings[d],n);

    int i=0;

    while(sentence[i] != '\0')
    {
        lcd_cmd(0x01,n);

        lcd_cmd(SET_DDRAM_ADDRESS1,n);
        for(int col=0; col<16; col++)
            if(sentence[i] != '\0')
                lcd_data(sentence[i++], n);

        lcd_cmd(SET_DDRAM_ADDRESS2,n);
        for(int col=0; col<16; col++)
            if(sentence[i] != '\0')
                lcd_data(sentence[i++], n);

        delay;
    }

    lcd_clear(n);
}

void lcd_typewriterEffect(unsigned char sentence[], uint8_t row, uint8_t col)
{
    TRISCbits.RC0=0;
    TRISCbits.RC1=0;
    TRISCbits.RC2=0;

    lcd_cmd(DISPLAY_8BIT_2LINE_1FONT,q);
    lcd_cmd(display_settings[d],q);

    for(int i=0; sentence[i]!=0; i++)
    {
        lcd_cmd(positions[row][col],q);
        delay;
        lcd_data(sentence[i],q);
        delay;
        lcd_cmd(CLEAR_DISPLAY,q);
    }
}


/* ================= 2 STRING ================= */

void lcd_scroll_2string(uint8_t string1[], uint8_t string2[], direction m)
{
    int n=q;

    lcd_clear(n);
    lcd_cmd(DISPLAY_8BIT_2LINE_1FONT,n);
    lcd_cmd(display_settings[d],n);

    lcd_cmd(0x80,n);
    lcd_print(string1,n);

    lcd_cmd(0xC0,n);
    lcd_print(string2,n);

    while(1)
    {
        if(m==RIGHT)
            lcd_cmd(0x1C,n);
        else
            lcd_cmd(0x18,n);

        delay;
    }
}

void lcd_noscroll_2line(unsigned char sentence[], unsigned char sentence1[])
{
    int n=q;

    lcd_cmd(DISPLAY_8BIT_2LINE_1FONT,n);
    lcd_cmd(0x06,n);
    lcd_cmd(display_settings[d],n);
    lcd_clear(n);

    lcd_cmd(0x80,n);
    lcd_print(sentence,n);

    lcd_cmd(0xC0,n);
    lcd_print(sentence1,n);
}


void lcd_sliderTwoLines(uint8_t string1[], uint8_t string2[], direction m)
{
    int n=q;

    lcd_clear(n);
    lcd_cmd(DISPLAY_8BIT_2LINE_1FONT,n);
    lcd_cmd(display_settings[d],n);

    lcd_cmd(0x80,n);
    lcd_print(string1,n);

    lcd_cmd(0xC0,n);
    lcd_print(string2,n);

    while(1)
    {
        for(int i=0;i<16;i++) lcd_cmd(0x1C,n);
        for(int i=0;i<16;i++) lcd_cmd(0x18,n);
    }
}
