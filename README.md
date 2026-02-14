# GPIO Driver Library – PIC16F877A (8-BIT)

⭐ A high-performance, register-level embedded driver library for the **Microchip PIC16F877A** microcontroller.

Developed using pure register-level programming (bypassing heavy built-in libraries where possible) to provide deep hardware control, predictable timing, and minimal overhead.

---

# 🔧 Features

### Full Port Control

Comprehensive support for **PORTA through PORTE** with physical pin mapping.

### Register-Based Architecture

Direct manipulation of **TRISx** and **PORTx** registers using pointer abstraction.

### ADC Management

Automatic disabling of analog functionality using **ADCON1** for stable digital I/O.

### Seven-Segment Display Support

Dedicated APIs for:

* Common Anode
* Common Cathode
* Hexadecimal Display (0–F)

### Matrix Keypad Integration

Supports 4×4 keypad scanning** for calculator and user-input systems.

### Embedded Calculator Engine

Implements arithmetic operations:

* Addition
* Subtraction
* Multiplication
* Division

With multi-digit handling and seven-segment output.

### Learning-Centric Design

Ideal for students transitioning from high-level frameworks to **bare-metal embedded firmware development**.

---

# 📁 Project Structure

```
PIC16F877A/

├── pic_library_code/                    # Header Files
│   ├── gpio.h
│
├── gpoi_middle_code/                    # Source Files
│   ├── gpio.c
│   ├── seven_segment.c
│   ├── keypad.c
│   └── calculator.c
│
├── EXAMPLE CODES/
│   ├── calculator_system.c
│   └── counters.c
│
└── README.md
```

---

# 📌 Core API Reference

## GPIO Control

```
Function                                              Description
------------------------------------------------------------------------------------------
void GPIO_pinmode(int pin, pinmode_t mode)            - Sets a specific physical pin as INPUT or OUTPUT.

void GPIO_pinwrite(int pin, pinstate state)           - Writes HIGH (1) or LOW (0) to a specific pin.

int pin_read(int pin)                                 - Returns the current digital state of a pin.

void toggle(int pin)                                  - Toggles the logic state of a pin.

void port_mode(port n, pinmode_t mode)                - Configures an entire port (PORTA–PORTE).

void config_range_tris(uint8_t start,
                       uint8_t end,
                       port n,
                       pinmode_t mode)                - Configures multiple TRIS bits at once.

void config_range_ports(uint8_t start,
                        uint8_t end,
                        port n,
                        pinstate state)               - Performs batch PORT operations.
```

---

# 📌 Peripheral Functions

## Seven Segment Display

```
Function                                              Description
------------------------------------------------------------------------------------------
void seven_segment_ANODE(char value, port n)          - Displays hexadecimal value (0–F) on Common Anode.

void seven_segment_CATHODE(char value, port n)        - Displays hexadecimal value (0–F) on Common Cathode.
```

## Keypad

```
Function                                              Description
------------------------------------------------------------------------------------------
char keypad_scan_phone(void)                          - Scans  4×4 keypad and returns pressed key.
```

## Calculator Engine

```
Function                                              Description
------------------------------------------------------------------------------------------
void calculator_init(void)                            - Initializes calculator modules.

void calculator_input(char key)                       - Processes keypad input for arithmetic logic.

int calculator_get_result(void)                       - Returns computed result.
```

---

# ⚠️ Critical Hardware Notes

## ADCON1 Register

PORTA and PORTE pins default to analog mode on reset.

To use them as digital:

```
ADCON1 = 0x06;
```

---

## RA4 Open-Drain Behavior

RA4 can only drive LOW internally.

External pull-up resistor required (≈10kΩ) to generate HIGH output.

---

## PORTB Internal Pull-Ups

Internal weak pull-ups can be enabled using:

```
OPTION_REG &= ~(1 << 7);
```

Useful for keypad interfacing without external resistors.

---

# 🧠 Technical Reference

| Parameter       | Value              |
| --------------- | ------------------ |
| Microcontroller | PIC16F877A         |
| Architecture    | 8-bit              |
| Clock Frequency | 20 MHz Recommended |
| Compiler        | XC8 (MPLAB X IDE)  |
| Simulator       | Proteus            |
| Debugger        | PICkit 3           |

Datasheet:
https://ww1.microchip.com/downloads/en/devicedoc/39582b.pdf

---

# 🚀 Example Usage

## GPIO Blink Example

```c
#include "gpio.h"

#define _XTAL_FREQ 20000000

void main()
{
    GPIO_pinmode(33, OUTPUT);

    while(1)
    {
        toggle(33);
        __delay_ms(500);
    }
}
```

---

## Calculator Example

```c
#include "calculator.h"
#include "keypad.h"

void main()
{
    calculator_init();

    while(1)
    {
        char key = keypad_scan_phone();

        if(key)
        {
            calculator_input(key);
        }
    }
}
```

---

# ⚖️ License

This project is open-source.

Free to use for:

* Educational purposes
* Research
* Embedded product prototyping
* Commercial evaluation

---

# 👨‍💻 Author

Embedded Systems Developer
PIC Firmware & Driver Architecture

---

⭐ If this project helps you, consider giving it a star.
