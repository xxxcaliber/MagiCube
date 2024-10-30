# Troubleshooting Guide

## Display Issues

### Screen Orientation
If the display orientation is incorrect:
1. Check TFT_eSPI rotation setting
2. Verify SCREEN_WIDTH and SCREEN_HEIGHT values
3. Confirm LVGL display rotation

### Touch Problems
If touch is not responding:
1. Verify SPI connections
2. Check touch IRQ pin
3. Monitor Serial output for touch coordinates
4. Verify calibration values

## Sensor Issues

### BME280 Not Reading
1. Check I2C connections
2. Verify I2C address
3. Test with I2C scanner

### PWM Control Issues
1. Verify PCA9685 address
2. Check power supply
3. Test individual channels

## Debug Tools
- Serial Monitor output
- I2C Scanner
- Touch coordinate debug output
