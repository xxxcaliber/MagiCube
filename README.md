# MagiCube
esp32-2432s024r MagiCube ENVI
# MagiCube ENVI

## Hardware
- ESP32-2432S024R with 2.4" TFT Touch Display (ILI9341_2_DRIVER)
- PCA9685
- BME280
- 5v Piezzo Atomizer Disc Module
- 5v LED light
- 5v fan

## Pin Configuration
- Touchscreen:
  - XPT2046_IRQ: 36 (T_IRQ)
  - XPT2046_MOSI: 32 (T_DIN)
  - XPT2046_MISO: 39 (T_OUT)
  - XPT2046_CLK: 25 (T_CLK)
  - XPT2046_CS: 33 (T_CS)

- I2C:
  - SDA: Pin 21
  - SCL: Pin 22

## Display Configuration
- Screen Width: 240
- Screen Height: 320
- Orientation: Horizontal

## Current Status
- Display: Working ✅
- Touch: Not Working ❌ (Under Development)
- Sensors: Working ✅
- Controls: Working ✅

## Development History
- [x] Initial setup with working display
- [x] Implemented sensor readings
- [x] Created basic UI layout
- [ ] Fix touch functionality
