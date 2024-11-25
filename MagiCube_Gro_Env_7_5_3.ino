//#include <PCA9685.h>
//#include <SPIFFS.h>
//#include <ArduinoJson.h>
//#include "config.h"
//#include "controls.h"
//#include "display.h"
//#include "sensors.h"

// MagiCube_Gro_Env_v7-2.ino

#include "main_gui.h"
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <EEPROM.h>
#include <ESP32Time.h>

// Pin Definitions
#define XPT2046_IRQ 36
#define XPT2046_MOSI 13
#define XPT2046_MISO 12
#define XPT2046_CLK 14
#define XPT2046_CS 33
#define TFT_BL 27

// PWM Configuration for backlight
#define TFT_BL_PWM_CHANNEL 0
#define TFT_BL_PWM_FREQ 5000
#define TFT_BL_PWM_RESOLUTION 8
#define TFT_BL_PWM_MAX_DUTY 255

// Screen Configuration
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320
#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))

// Global Objects
SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);
Adafruit_BME280 bme;
ESP32Time rtc;

// Buffer for LVGL
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// Touch coordinates
int x, y, z;

// Logging callback for LVGL
void log_print(lv_log_level_t level, const char * buf) {
    LV_UNUSED(level);
    Serial.println(buf);
    Serial.flush();
}

// Touchscreen reading callback for LVGL
void touchscreen_read(lv_indev_t * indev, lv_indev_data_t * data) {
    if(touchscreen.tirqTouched() && touchscreen.touched()) {
        TS_Point p = touchscreen.getPoint();
        x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
        y = map(p.y, 3800, 240, 1, SCREEN_HEIGHT);
        z = p.z;

        data->state = LV_INDEV_STATE_PRESSED;
        data->point.x = x;
        data->point.y = y;
    }
    else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

void setup() {
    Serial.begin(115200);
    Wire.begin(21, 22); // Initialize I2C for BME280

    // Initialize backlight
    pinMode(TFT_BL, OUTPUT);
    ledcAttach(TFT_BL, TFT_BL_PWM_FREQ, TFT_BL_PWM_RESOLUTION);
    ledcWrite(TFT_BL, TFT_BL_PWM_MAX_DUTY);

    // Initialize BME280
    if (!bme.begin(0x76)) {
        Serial.println("Could not find BME280 sensor!");
    }

    // Initialize LVGL
    lv_init();
    lv_log_register_print_cb(log_print);

    // Initialize touchscreen
    touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    touchscreen.begin(touchscreenSPI);  // Changed this line
    touchscreen.setRotation(1);

    // Initialize display
    lv_display_t * disp;
    disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90);

    // Initialize touch input
    lv_indev_t * indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, touchscreen_read);

    // Create the main GUI
    create_main_gui();
}

void loop() {
    static uint32_t last_update = 0;
    
    // Update environmental data every 2 seconds
    if(millis() - last_update > 2000) {
        float temperature = bme.readTemperature();
        float humidity = bme.readHumidity();
        
        // Update GUI with new sensor readings
        update_environmental_data(temperature, humidity);
        
        last_update = millis();
    }

    lv_timer_handler();
    lv_tick_inc(5);
    delay(5);
}
