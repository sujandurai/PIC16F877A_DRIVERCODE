# PIC16F877A Embedded Driver Framework

### GPIO • Display • Keypad • Calculator Engine (8-Bit)

⭐ A modular, register-level embedded firmware framework for the **Microchip PIC16F877A** microcontroller.

This project provides a clean Hardware Abstraction Layer (HAL) for digital I/O, display control, keypad scanning, and an embedded calculator system while maintaining direct access to hardware registers for deterministic performance.

Designed for:

* Embedded Systems Students
* Firmware Engineers
* Academic Projects
* Bare-Metal Development
* Hardware Prototyping

---

# ✨ Key Features

### ✔ Register-Level GPIO Control

Direct manipulation of **TRISx** and **PORTx** registers using optimized pointer abstraction.

### ✔ Full Port Coverage

Supports all microcontroller ports:

PORTA • PORTB • PORTC • PORTD • PORTE

### ✔ Automatic Analog Disable

Configures analog pins as digital using **ADCON1** for reliable I/O behavior.

### ✔ Seven-Segment Display Driver

Supports:

* Common Anode
* Common Cathode
* Hexadecimal Characters (0–F)

### ✔ Matrix Keypad Interface

Compatible with **4×3** and **4×4** keypad layouts for calculator and user interfaces.

### ✔ Embedded Calculator Engine

Implements arithmetic operations:

Addition • Subtraction • Multiplication • Division

With multi-digit processing and seven-segment output.

### ✔ Lightweight & Deterministic

No unnecessary abstraction layers — optimized for predictable execution timing.

---

# 📂 Repository Structure

```
PIC16F877A/

├── pic_library_code/                        # Header Files
│   ├── gpio.h
├── gpio_middle_code/                        # Source Files
│   ├── gpio.c
│   ├── seven_segment.c
│   ├── keypad.c
│   └── calculator.c
│
├── EXAMPLE CODES/              # Application Examples
│   ├── calculator_system.c
│   └── counters.c
│
└── README.md
```

---

# 📌 Core API Reference

## GPIO Control Interface

```
Function                                              Description
------------------------------------------------------------------------------------------------
void GPIO_pinmode(int pin, pinmode_t mode)            Configure a physical pin as INPUT or OUTPUT.

void GPIO_pinwrite(int pin, pinstate state)           Write HIGH or LOW logic level to a pin.

int  pin_read(int pin)                                Read the current digital state of a pin.

void toggle(int pin)                                  Toggle the logic state of a pin.

void port_mode(port port_name, pinmode_t mode)        Configure direction for an entire port.

void config_range_tris(uint8_t start,
                       uint8_t end,
                       port port_name,
                       pinmode_t mode)                Configure multiple TRIS bits simultaneously.

void config_range_ports(uint8_t start,
                        uint8_t end,
                        port port_name,
                        pinstate state)               Perform batch operations on PORT bits.
```

---

# 📌 Peripheral Interfaces

## Seven-Segment Display

```
Function                                              Description
------------------------------------------------------------------------------------------------
void seven_segment_ANODE(char value, port port_name)  Display hexadecimal value (0–F) on Common Anode display.

void seven_segment_CATHODE(char value, port port_name)Display hexadecimal value (0–F) on Common Cathode display.
```

## Keypad Driver

```
Function                                              Description
------------------------------------------------------------------------------------------------
char keypad_scan_phone(void)                          Scan keypad matrix and return pressed key.
```

## Calculator Engine

```
Function                                              Description
------------------------------------------------------------------------------------------------
void calculator_init(void)                            Initialize calculator modules and display.

void calculator_input(char key)                       Process keypad input and arithmetic logic.

int  calculator_get_result(void)                      Retrieve computed calculation result.
```

---

# ⚠️ Hardware Considerations

## Analog Configuration (PORTA / PORTE)

Pins default to analog mode after reset.

Configure as digital:

```c
ADCON1 = 0x06;
```

---

## RA4 Output Characteristics

RA4 operates as an **open-drain output**.

Requirement:

External pull-up resistor (~10 kΩ) for HIGH level output.

---

## PORTB Internal Pull-Ups

Enable internal pull-ups when using keypad:

```c
OPTION_REG &= ~(1 << 7);
```

---

# 🧠 Technical Specifications

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

# 🚀 Example Applications

## GPIO Blink Example

```c
#include "gpio.h"

#define _XTAL_FREQ 20000000

void main(void)
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

## Calculator System Example

```c
#include"gpio.h"

void main(void)
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

# 🏗 Internal Architecture

The framework uses pointer-based register abstraction:

```
volatile unsigned char *port_s[];
volatile unsigned char *tris[];
```

Advantages:

✔ Eliminates large switch-case blocks
✔ Faster execution
✔ Cleaner scalable design
✔ Reduced code duplication

---

# 📜 License

This project is open-source and free for:

* Education
* Research
* Embedded prototyping
* Commercial evaluation

---

# 👨‍💻 Author

Embedded Systems Developer
PIC Firmware Architecture & Driver Design

---

⭐ If you find this project useful, consider giving it a star.
