# ESP32 Air Mouse

DIY wireless Bluetooth air mouse using ESP32-WROOM-32, MPU6050 and three push buttons.

## Hardware

- ESP32 DevKit / ESP32-WROOM-32
- MPU6050
- 3 push buttons

## Connections

### MPU6050

| MPU6050 | ESP32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

### Buttons

| Function | ESP32 |
|---|---|
| Left Click | GPIO 25 |
| Right Click | GPIO 26 |
| Middle Click | GPIO 27 |

The buttons use the ESP32 internal pull-up resistors.

## Features

- Bluetooth wireless mouse
- MPU6050 motion control
- Left click
- Right click
- Middle click
- Adjustable cursor sensitivity
- MPU6050 gyro calibration

## Software

- Arduino IDE
- ESP32 Arduino Core
- Adafruit MPU6050
- Adafruit Unified Sensor
- ESP32 BLE Mouse

## Project

MPU6050
↓
ESP32
↓
Bluetooth HID
↓
PC

## Wokwi

A Wokwi simulation version can be included separately. Wokwi can simulate the ESP32 and MPU6050, but it does not control the physical PC cursor through Bluetooth HID.

## Author

solo-prince
