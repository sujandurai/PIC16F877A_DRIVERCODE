
# PIC16F877A Embedded Driver Framework

### GPIO • UART • I²C • Display • Keypad • Calculator Engine

⭐ A modular, register-level embedded firmware framework for the **Microchip PIC16F877A** microcontroller.

This project provides reusable peripheral drivers and hardware abstraction layers (HAL) for developing embedded applications using direct register manipulation while maintaining deterministic real-time behavior.

Designed for:

* Embedded Systems Engineers
* Firmware Developers
* Bare-Metal Programmers
* Academic Research
* Hardware Prototyping

---

# 🚀 Features

### 🔹 GPIO Driver

* Register-level pin configuration
* Input / Output management
* Port-wide operations
* Pin toggling support

### 🔹 UART Driver

* UART initialization
* Character transmission
* String transmission
* Character reception
* Serial debugging support

### 🔹 I²C Bit-Banging Driver

* Software-based I²C implementation
* Start / Stop generation
* ACK / NACK handling
* Byte transmit and receive
* Sensor interfacing support

### 🔹 Seven Segment Driver

* Common Anode support
* Common Cathode support
* Hexadecimal display support (0–F)

### 🔹 Matrix Keypad Driver

* 4×3 keypad support
* 4×4 keypad support
* Debounced key detection

### 🔹 Calculator Engine

* Addition
* Subtraction
* Multiplication
* Division
* Multi-digit processing

### 🔹 Lightweight Architecture

* No RTOS required
* Minimal RAM usage
* Deterministic execution
* Scalable module structure

---

# 📂 Repository Structure

```text
PIC16F877A-Driver-Framework/

├── include/
│   ├── gpio.h
│   ├── uart.h
│   ├── i2c_bb.h
│   ├── keypad.h
│   ├── seven_segment.h
│   └── calculator.h
│
├── src/
│   ├── gpio.c
│   ├── uart.c
│   ├── i2c_bb.c
│   ├── keypad.c
│   ├── seven_segment.c
│   └── calculator.c
│
├── examples/
│   ├── blink.c
│   ├── uart_terminal.c
│   ├── i2c_sensor.c
│   ├── keypad_demo.c
│   └── calculator_system.c
│
├── docs/
│   └── architecture.md
│
└── README.md
```

---

# 🛠 Peripheral Modules

## GPIO Driver

```c
void GPIO_pinmode(int pin, pinmode_t mode);
void GPIO_pinwrite(int pin, pinstate state);
int  pin_read(int pin);
void toggle(int pin);
void port_mode(port port_name, pinmode_t mode);
```

---

## UART Driver

```c
void UART_Init(unsigned long baudrate);

void UART_WriteChar(char data);

void UART_WriteString(const char *str);

char UART_ReadChar(void);

uint8_t UART_DataAvailable(void);
```

### Supported Baud Rates

* 9600
* 19200
* 38400
* 57600
* 115200

---

## I²C Bit-Banging Driver

```c
void I2C_Init(void);

void I2C_Start(void);

void I2C_Stop(void);

void I2C_Write(uint8_t data);

uint8_t I2C_Read(uint8_t ack);
```

### Compatible Devices

* EEPROM
* RTC
* OLED Displays
* Environmental Sensors
* IMU Modules

---

## Seven Segment Driver

```c
void seven_segment_ANODE(char value, port port_name);

void seven_segment_CATHODE(char value, port port_name);
```

---

## Keypad Driver

```c
char keypad_scan_phone(void);
```

---

## Calculator Engine

```c
void calculator_init(void);

void calculator_input(char key);

int calculator_get_result(void);
```

---

# ⚙ Hardware Configuration

## Configure Analog Pins as Digital

```c
ADCON1 = 0x06;
```

---

## Enable PORTB Pull-Ups

```c
OPTION_REG &= ~(1 << 7);
```

---

## RA4 Open Drain Behavior

RA4 requires an external pull-up resistor for proper HIGH-level operation.

Recommended:

```text
10kΩ Pull-Up Resistor
```

---

# 📊 Technical Specifications

| Parameter       | Value        |
| --------------- | ------------ |
| MCU             | PIC16F877A   |
| Architecture    | 8-bit        |
| Flash Memory    | 8K Words     |
| RAM             | 368 Bytes    |
| EEPROM          | 256 Bytes    |
| Clock Frequency | Up to 20 MHz |
| Compiler        | XC8          |
| IDE             | MPLAB X      |
| Debugger        | PICkit 3     |
| Simulator       | Proteus      |

---

# 💼 Example Applications

### LED Blink

```c
GPIO_pinmode(33, OUTPUT);

while(1)
{
    toggle(33);
    __delay_ms(500);
}
```

### UART Serial Terminal

```c
UART_Init(9600);

while(1)
{
    UART_WriteString("PIC16F877A UART Driver\r\n");
    __delay_ms(1000);
}
```

### I²C Sensor Interface

```c
I2C_Start();

I2C_Write(0xD0);

I2C_Write(0x00);

I2C_Stop();
```

### Calculator System

```c
calculator_init();

while(1)
{
    char key = keypad_scan_phone();

    if(key)
    {
        calculator_input(key);
    }
}
```

---

# 🏗 Architecture Overview

The framework uses pointer-based register abstraction:

```c
volatile unsigned char *port_s[];
volatile unsigned char *tris[];
```

### Benefits

✔ Reduced code duplication

✔ Faster register access

✔ Modular architecture

✔ Easy scalability

✔ Clean driver separation

✔ Improved maintainability

---

# 📚 Learning Outcomes

Through this project:

* Register-Level Programming
* Embedded Driver Development
* UART Communication
* I²C Protocol Implementation
* Hardware Abstraction Layer Design
* Embedded Software Architecture
* Bare-Metal Firmware Development

---

# 👨‍💻 Author

### Sujan Duraisamy

Embedded Systems • Firmware Development • Edge AI

Passionate about building efficient embedded systems using low-level firmware, hardware-software co-design, and real-time architectures.

---
