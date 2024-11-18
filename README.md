# Master Embedded Systems: Projects with Atmega328, Arduino, and Eagle-PCB

Welcome to the **Embedded Systems Projects** repository! This repository contains a collection of projects using the **Atmega328** microcontroller, **Arduino**, and **Eagle PCB design**. These projects are designed for beginners who want to learn embedded systems concepts, build real-world applications, and fabricate their own PCBs.

## Table of Contents

- [Overview](#overview)
- [Understanding Microcontrollers: Atmega328 Basics](#understanding-microcontrollers-atmega8-basics)
- [Programming with Arduino IDE](#programming-with-arduino-ide)
- [Installing Arduino IDE and Setting Up ATmega328/UNO Board](#installing-arduino-ide-and-setting-up-atmega328uno-board)
- [Working with Timers in Embedded Systems](#working-with-timers-in-embedded-systems)
- [Interfacing with Sensors and ADC (Analog to Digital Conversion)](#interfacing-with-sensors-and-adc-analog-to-digital-conversion)
- [Pulse Width Modulation (PWM) for Motor and LED Control](#pulse-width-modulation-pwm-for-motor-and-led-control)
- [Interfacing LCD Displays for User Output](#interfacing-lcd-displays-for-user-output)
- [USBASP Programmer for Atmega328 Firmware Upload](#usbasp-programmer-for-atmega8-firmware-upload)
- [Eagle PCB Design: From Schematic to Fabrication](#eagle-pcb-design-from-schematic-to-fabrication)
- [DIY PCB Fabrication Process](#diy-pcb-fabrication-process)
- [Project Folders](#project-folders)

## Overview

This repository provides practical examples of embedded systems projects using the **Atmega328** microcontroller and **Arduino** platform. You will also explore **Eagle PCB design** for creating custom PCBs. The goal is to build a solid foundation for working with embedded systems and PCB fabrication.

## Understanding Microcontrollers: Atmega8 Basics

A **microcontroller** is a compact integrated circuit that acts as the brain of an embedded system. It combines a processor (for executing instructions), memory (for storing programs and temporary data), and input/output pins (for connecting to external devices) all in one chip. Unlike general-purpose computers, microcontrollers are designed to perform specific tasks, such as controlling an appliance, blinking an LED, or reading data from a sensor. Their versatility and low cost make them a cornerstone of modern electronics, found in everything from toys to industrial machinery.

The **Atmega328**, part of the AVR family, is a popular 8-bit microcontroller for beginners. Built on the efficient AVR architecture, it uses a Reduced Instruction Set Computer (RISC) design for faster performance. It features 32 KB of Flash memory for program storage, 1 KB of SRAM for temporary data, and 512 bytes of EEPROM for saving data even when power is off. With 23 input/output pins, built-in timers, a 10-bit Analog-to-Digital Converter (ADC), and communication protocols like UART, SPI, and I2C, the Atmega328 is ideal for learning how microcontrollers work. Its simplicity, combined with powerful features, makes it a go-to choice for building practical projects like motor control, sensor interfacing, and custom PCB designs.

## Programming with Arduino IDE

Arduino provides several built-in functions to interact with hardware components like LEDs, sensors, and motors. Here’s an overview of the most commonly used functions, explained in a simple way.

### `pinMode()`
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

**Example**:  
```cpp
int buttonState = digitalRead(2); // Read the state of the button on pin 2
```
### `analogWrite()`
Generates a PWM signal to control the brightness of LEDs or the speed of motors.

value: Ranges from 0 (off) to 255 (full brightness or speed).

**Syntax**:
```cpp
analogWrite(pin, value);
```

**Example**:
```cpp
analogWrite(9, 128); // Set 50% brightness on pin 9
```
### `delay()`
Pauses the program for a specified time in milliseconds.

**Syntax**:
```cpp
delay(milliseconds);
```

**Example**:
```cpp
delay(1000); // Wait for 1 second
```
### `Serial.begin`()
Initializes communication between the Arduino and a computer. The baud rate determines the speed of communication (e.g., 9600 bits per second).

**Syntax**:
```cpp
Serial.begin(baudRate);
```

**Example**:
```cpp
Serial.begin(9600); // Start communication at 9600 bps
```
### `Serial.print() and Serial.println()`
Send data or messages to the computer via the Serial Monitor.
Serial.print(): Prints data on the same line.
Serial.println(): Prints data and moves to the next line.

**Example**:
```cpp
Serial.print("Temperature: ");
Serial.println(25);
```
### `Serial.read()`
Reads incoming data from the serial buffer (one byte at a time).

**Syntax**:
```cpp
char data = Serial.read();
```
**Example**:
```cpp
if (Serial.available() > 0) {
    char receivedData = Serial.read(); // Read the first available byte
}
```

## Installing Arduino IDE and Setting Up ATmega328/UNO Board

This guide provides a brief explanation on how to install the Arduino IDE and set up the **ATmega328** or **Arduino Uno** board.

### 1. Install the Arduino IDE

#### a. Download and Install
1. Visit the official [Arduino website](https://www.arduino.cc/en/software).
2. Download the appropriate version for your operating system (Windows, macOS, Linux).
3. Follow the installation instructions:
   - For Windows: Run the installer `.exe` file and follow the prompts.
   - For macOS: Open the `.dmg` file and drag the Arduino IDE to the Applications folder.
   - For Linux: Use the package manager or install from the tarball.

#### b. Launch the IDE
After installation, launch the **Arduino IDE**. You should see the Arduino IDE window ready for use.

### 2. Set Up the ATmega328/UNO Board in Arduino IDE

#### a. Open the Arduino IDE
1. Open the **Arduino IDE** after installation.

#### b. Select the Board (ATmega328/UNO)
1. Go to **Tools** → **Board** → **Arduino Uno** (which uses the ATmega328P microcontroller).
2. Select **Arduino Uno** from the list of available boards.

#### c. Select the Port
1. Connect your **Arduino Uno** to your computer using a USB cable.
2. Go to **Tools** → **Port** and select the correct port where your Arduino Uno is connected. On Windows, this is usually something like `COM3` or `COM4`. On macOS/Linux, it will show up as `/dev/cu.usbmodemXXXX`.

### 3. Install the ATmega328 Drivers (if needed)

If your Arduino Uno is not recognized or you're using a clone board, you may need to install drivers.

- **For Windows**: The drivers are automatically installed when you install the Arduino IDE. However, for clone boards, you may need to manually install the **CH340/CH341** driver from the manufacturer's website.
- **For macOS/Linux**: These platforms usually don’t require additional drivers. If needed, you can find open-source drivers or use tools like **brew** on macOS.

### 4. Test the Setup

To confirm everything is set up correctly:

1. Open the **Arduino IDE**.
2. Go to **File** → **Examples** → **01.Basics** → **Blink**.
3. Click the **Upload** button (right arrow icon).
4. The LED on pin 13 of the Arduino Uno should start blinking if everything is configured properly.

You have now successfully set up the Arduino IDE for programming the **ATmega328/Uno** board.


