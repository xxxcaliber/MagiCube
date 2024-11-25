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

## Define SPI pins for display
#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15  // Chip select control pin
#define TFT_DC    2  // Data Command control pin
#define TFT_RST  -1  // Set to -1 if not used
#define TFT_BL   27  // LED back-light control pin

- I2C:
  - SDA: Pin 21
  - SCL: Pin 22

## Display Configuration
- Screen Width: 320
- Screen Height: 240
- Orientation: Horizontal

## Current Status
- Display: Working ✅
- Touch: Working ✅
- Sensors: under development ✅
- Controls: under developmnet ✅

## Development History
- [x] Initial setup with working display
- [x] Implemented sensor readings
- [x] Created basic UI layout
- [x] Fixed touch functionality
