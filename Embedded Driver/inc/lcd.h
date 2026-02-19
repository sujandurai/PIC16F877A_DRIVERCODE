#ifndef LCD_H
#define LCD_H

#include <xc.h>
#include <stdint.h>

/* ================= ENUM ================= */

typedef enum
{
    PORT_A = 0,
    PORT_B = 1,
    PORT_C = 2,
    PORT_D = 3,
    PORT_E = 4,

} port;

typedef enum
{
    LEFT = 0,
    RIGHT = 1,
    RIGHT_LEFT = 2,
    LEFT_RIGHT = 3,

} direction;


/* ================= PORT C BIT STRUCT ================= */

typedef struct {
    unsigned char RC0:1;
    unsigned char RC1:1;
    unsigned char RC2:1;
    unsigned char RC3:1;
    unsigned char RC4:1;
    unsigned char RC5:1;
    unsigned char RC6:1;
    unsigned char RC7:1;

} regc_bits;

/* ================= LCD COMMANDS ================= */

#define CLEAR_DISPLAY        0x01
#define CURSOR_RETURN        0x02

#define CURSOR_LEFT          0x04
#define CURSOR_LEFT_SHIFT    0x05
#define CURSOR_RIGHT         0x06
#define CURSOR_RIGHT_SHIFT   0x07

#define DISPLAY_OFF             0x08
#define DISPLAY_ON_CURSOR_OFF   0x0C
#define DISPLAY_ON_BLINK        0x0D
#define DISPLAY_ON_CURSOR       0x0E
#define DISPLAY_ON_CUR_BLINK    0x0F

#define SHIFT_DISPLAY_RIGHT     0x1C
#define SHIFT_DISPLAY_LEFT      0x18

#define DISPLAY_4BIT_2LINE_1FONT        0x28
#define DISPLAY_8BIT_2LINE_1FONT        0x38
#define DISPLAY_4BIT_2LINE_2FONT        0x2C
#define DISPLAY_8BIT_2LINE_2FONT        0x3C

#define DISPLAY_8BIT_1LINE_1FONT  0x30
#define DISPLAY_4BIT_1LINE_1FONT  0x20
#define DISPLAY_8BIT_1LINE_2FONT  0x31
#define DISPLAY_4BIT_1LINE_2FONT  0x21

#define SET_DDRAM_ADDRESS1   0x80
#define SET_DDRAM_ADDRESS2   0xC0


/* ================= GLOBAL VARIABLES ================= */

extern volatile unsigned char *port_s[];
extern volatile unsigned char *tris[];
extern volatile unsigned int *directions[];
extern volatile unsigned char positions[2][16];
extern volatile unsigned int display_settings[];

extern unsigned int q;
extern uint8_t d;


/* ================= FUNCTION PROTOTYPES ================= */

void lcd_select_port(port m);
void lcd_cmd(unsigned char a, port n);
void lcd_data(unsigned char b, port n);
void lcd_clear(port n);
void lcd_print(unsigned char *s, port n);
void lcd_set_display(uint8_t disptype);

void string_disp_shift_2line_5X10(unsigned char sentence[], direction m);
void string_disp_shift_2line_5X7(unsigned char sentence[], port n, direction m);

void lcd_scrollText_2Line_5x10(unsigned char sentence[], port n, direction m, uint8_t row, uint8_t col);
void lcd_scrollText_2Line_5x7(unsigned char sentence[], port n, direction m, uint8_t row, uint8_t col);

void lcd_displayPaged_2Line(unsigned char sentence[], port n);
void lcd_typewriterEffect(unsigned char sentence[], uint8_t row, uint8_t col);

void lcd_scroll_2string(uint8_t string1[], uint8_t string2[], direction m);
void lcd_noscroll_2line(unsigned char sentence[], unsigned char sentence1[]);

void lcd_sliderTwoLines(uint8_t string1[], uint8_t string2[], direction m);

#endif
