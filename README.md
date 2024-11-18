# Master Embedded Systems: Projects with Atmega8, Arduino, and Eagle-PCB

Welcome to the **Embedded Systems Projects** repository! This repository contains a collection of projects using the **Atmega8** microcontroller, **Arduino**, and **Eagle PCB design**. These projects are designed for beginners who want to learn embedded systems concepts, build real-world applications, and fabricate their own PCBs.

## Table of Contents

- [Overview](#overview)
- [Understanding Microcontrollers: Atmega8 Basics](#understanding-microcontrollers-atmega8-basics)
- [Programming with Arduino IDE](#programming-with-arduino-ide)
- [Working with Timers in Embedded Systems](#working-with-timers-in-embedded-systems)
- [Interfacing with Sensors and ADC (Analog to Digital Conversion)](#interfacing-with-sensors-and-adc-analog-to-digital-conversion)
- [Pulse Width Modulation (PWM) for Motor and LED Control](#pulse-width-modulation-pwm-for-motor-and-led-control)
- [Interfacing LCD Displays for User Output](#interfacing-lcd-displays-for-user-output)
- [USBASP Programmer for Atmega8 Firmware Upload](#usbasp-programmer-for-atmega8-firmware-upload)
- [Eagle PCB Design: From Schematic to Fabrication](#eagle-pcb-design-from-schematic-to-fabrication)
- [DIY PCB Fabrication Process](#diy-pcb-fabrication-process)
- [Project Folders](#project-folders)

## Overview

This repository provides practical examples of embedded systems projects using the **Atmega8** microcontroller and **Arduino** platform. You will also explore **Eagle PCB design** for creating custom PCBs. The goal is to build a solid foundation for working with embedded systems and PCB fabrication.

## Understanding Microcontrollers: Atmega8 Basics

A **microcontroller** is a compact integrated circuit that acts as the brain of an embedded system. It combines a processor (for executing instructions), memory (for storing programs and temporary data), and input/output pins (for connecting to external devices) all in one chip. Unlike general-purpose computers, microcontrollers are designed to perform specific tasks, such as controlling an appliance, blinking an LED, or reading data from a sensor. Their versatility and low cost make them a cornerstone of modern electronics, found in everything from toys to industrial machinery.

The **Atmega8**, part of the AVR family, is a popular 8-bit microcontroller for beginners. Built on the efficient AVR architecture, it uses a Reduced Instruction Set Computer (RISC) design for faster performance. It features 8 KB of Flash memory for program storage, 1 KB of SRAM for temporary data, and 512 bytes of EEPROM for saving data even when power is off. With 23 input/output pins, built-in timers, a 10-bit Analog-to-Digital Converter (ADC), and communication protocols like UART, SPI, and I2C, the Atmega8 is ideal for learning how microcontrollers work. Its simplicity, combined with powerful features, makes it a go-to choice for building practical projects like motor control, sensor interfacing, and custom PCB designs.

## Programming with Arduino IDE

Arduino provides several built-in functions to interact with hardware components like LEDs, sensors, and motors. Here’s an overview of the most commonly used functions, explained in a simple way.

---

### 1. GPIO (General Purpose Input/Output)

#### `pinMode()`
Configures a GPIO pin as an **input** or **output**.  
- **pin**: The pin number you want to set (e.g., 2, 13).  
- **mode**: Use `INPUT`, `OUTPUT`, or `INPUT_PULLUP`.  

**Example**:  
```cpp
pinMode(13, OUTPUT); // Set pin 13 as output
pinMode(2, INPUT);   // Set pin 2 as input
```
### `digitalWrite()`
Sets a pin to either HIGH (on) or LOW (off).
**Example**:  
```cpp
digitalWrite(13, HIGH); // Turn on LED connected to pin 13
digitalWrite(13, LOW);  // Turn it off
```
### `digitalRead()`
Reads the state of a digital input pin (HIGH or LOW).

Syntax:

cpp
Copy code
int state = digitalRead(pin);
Example:

cpp
Copy code
int buttonState = digitalRead(2); // Read the state of the button on pin 2
2. PWM (Pulse Width Modulation)
analogWrite()
Generates a PWM signal to control the brightness of LEDs or the speed of motors.

value: Ranges from 0 (off) to 255 (full brightness or speed).
Syntax:

cpp
Copy code
analogWrite(pin, value);
Example:

cpp
Copy code
analogWrite(9, 128); // Set 50% brightness on pin 9
3. Delays
delay()
Pauses the program for a specified time in milliseconds.

Syntax:

cpp
Copy code
delay(milliseconds);
Example:

cpp
Copy code
delay(1000); // Wait for 1 second
4. Serial Communication
Serial.begin()
Initializes communication between the Arduino and a computer. The baud rate determines the speed of communication (e.g., 9600 bits per second).

Syntax:

cpp
Copy code
Serial.begin(baudRate);
Example:

cpp
Copy code
Serial.begin(9600); // Start communication at 9600 bps
Serial.print() and Serial.println()
Send data or messages to the computer via the Serial Monitor.

Serial.print(): Prints data on the same line.
Serial.println(): Prints data and moves to the next line.
Example:

cpp
Copy code
Serial.print("Temperature: ");
Serial.println(25);
Serial.read()
Reads incoming data from the serial buffer (one byte at a time).

Syntax:

cpp
Copy code
char data = Serial.read();
Example:

cpp
Copy code
if (Serial.available() > 0) {
    char receivedData = Serial.read(); // Read the first available byte
}

