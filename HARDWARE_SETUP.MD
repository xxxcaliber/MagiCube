# Hardware Setup Guide

## Components List
1. ESP32-2432S024R Development Board
   - Built-in 2.4" TFT Display
   - XPT2046 Touch Controller
   
2. Sensors
   - BME280 (Temperature, Humidity, Pressure)
   
3. Actuators
   - PCA9685 PWM Controller
   - 5v LED Module
   - 5v Piezzo Atomizer
   - 5v Fan

## Wiring Diagram

### I2C Devices (BME280 & PCA9685)
- SDA → Pin 21
- SCL → Pin 22
- VCC → 3.3V
- GND → GND

### Display & Touch (Built-in)
XPT2046 Touch Controller:
- IRQ → Pin 36
- MOSI → Pin 32
- MISO → Pin 39
- CLK → Pin 25
- CS → Pin 33

### Output Devices (via PCA9685)
1. LED Module
   - Channel 0
   - VCC → 5V
   - GND → GND

2. Atomizer
   - Channel 1
   - VCC → 5V
   - GND → GND

3. Fan
   - Channel 2
   - VCC → 5V
   - GND → GND

## Power Requirements
- Input Voltage: 5V DC
- Current Draw: ~1A maximum
