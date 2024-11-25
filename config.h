#ifndef CONFIG_H
#define CONFIG_H

// Display Configuration
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define BUFFER_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10)

// Touchscreen pins
#define XPT2046_IRQ 36
#define XPT2046_MOSI 13
#define XPT2046_MISO 12
#define XPT2046_CLK 14
#define XPT2046_CS 33
#define TFT_BL 27

// I2C Configuration
#define SDA_PIN 21
#define SCL_PIN 22

// PCA9685 Configuration
//#define PCA9685_I2C_ADDRESS 0x40
//#define LED_CHANNEL 0
//#define FAN_CHANNEL 1
//#define MIST_CHANNEL 2

#endif // CONFIG_H
