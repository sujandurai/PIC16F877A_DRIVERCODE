Here is a professional **README.md** for your GPIO library designed for the **PIC16F877A**.

---

# GPIO Library for PIC16F877A

## Overview

This GPIO library provides a hardware abstraction layer (HAL) for digital input/output operations on the **PIC16F877A** microcontroller.

It simplifies:

* Pin configuration (Input / Output)
* Digital write (High / Low)
* Digital read
* Pin toggle
* Range-based TRIS configuration
* Range-based PORT operations

The library maps physical microcontroller pins to corresponding PORT and TRIS registers internally.

---

## Supported Microcontroller

* **Microcontroller:** PIC16F877A
* **Architecture:** 8-bit
* **Ports Supported:** PORTA, PORTB, PORTC, PORTD, PORTE

---

## File Structure

```
gpios.h       -> Header file (macros, enums, definitions)
gpios.c       -> GPIO implementation
README.md     -> Documentation
```

---

## Pin Mapping Logic

The library converts physical pin numbers into:

| Pin Range | Port  |
| --------- | ----- |
| 2 – 7     | PORTA |
| 8 – 10    | PORTE |
| 15 – 18   | PORTC |
| 19 – 22   | PORTD |
| 23 – 26   | PORTC |
| 27 – 30   | PORTD |
| 33 – 40   | PORTB |

Analog pins are configured as digital using:

```c
ADCON1 = 0x06;
```

---

## Data Types Used

### Pin Mode

```c
typedef enum {
    OUTPUT = 0,
    INPUT = 1
} pinmode_t;
```

### Pin State

```c
typedef enum {
    LOW = 0,
    HIGH = 1,
    TOGGLE = 2
} pinstate;
```

---

# Function Documentation

---

## 1️⃣ GPIO_pinmode()

### Description

Configures a specific pin as INPUT or OUTPUT.

### Syntax

```c
void GPIO_pinmode(int pin, pinmode_t mode);
```

### Example

```c
GPIO_pinmode(33, OUTPUT);   // Configure RB0 as output
GPIO_pinmode(2, INPUT);     // Configure RA0 as input
```

---

## 2️⃣ GPIO_pinwrite()

### Description

Writes HIGH or LOW to a specified pin.

### Syntax

```c
void GPIO_pinwrite(int pin, pinstate state);
```

### Example

```c
GPIO_pinwrite(33, HIGH);    // Set RB0 high
GPIO_pinwrite(33, LOW);     // Set RB0 low
```

---

## 3️⃣ pin_read()

### Description

Reads the current logic level of a pin.

### Syntax

```c
int pin_read(int pin);
```

### Returns

* 1 → HIGH
* 0 → LOW

### Example

```c
int state = pin_read(2);
```

---

## 4️⃣ toggle()

### Description

Toggles the current state of a pin.

### Syntax

```c
void toggle(int pin);
```

### Example

```c
toggle(33);   // Toggle RB0
```

---

## 5️⃣ config_range_tris()

### Description

Configures multiple bits of a TRIS register at once.

### Syntax

```c
void config_range_tris(uint8_t start, uint8_t end, triss port, pinmode_t mode);
```

### Parameters

* `start` → Lower bit (0–7)
* `end` → Upper bit (exclusive)
* `port` → Port index
* `mode` → INPUT or OUTPUT

### Example

```c
config_range_tris(0, 4, PORTB_INDEX, OUTPUT); 
// Set RB0–RB3 as output
```

---

## 6️⃣ config_range_ports()

### Description

Performs batch operations on PORT bits.

### Syntax

```c
void config_range_ports(int start, int end, port port_name, pinstate state);
```

### Operations Supported

* LOW
* HIGH
* TOGGLE

### Example

```c
config_range_ports(0, 8, PORTB_INDEX, HIGH); 
// Set entire PORTB HIGH
```

---

# Internal Architecture

The library uses pointer arrays:

```c
volatile unsigned char *port_s[]
volatile unsigned char *tris[]
```

This allows dynamic register selection without large switch-case blocks.

---

# Advantages

✔ Clean abstraction over hardware registers
✔ No direct register manipulation in user code
✔ Reduced repetitive bit manipulation
✔ Supports single pin and range operations
✔ Easy integration into embedded projects

---

# Limitations

* Designed specifically for PIC16F877A
* Pin numbering must follow defined mapping
* Analog configuration limited to ADCON1 = 0x06

---

# Example Usage

```c
#include "gpios.h"

int main()
{
    GPIO_pinmode(33, OUTPUT);  // RB0 output
    
    while(1)
    {
        toggle(33);
        __delay_ms(500);
    }
}
```

---
