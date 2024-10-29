#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <PCA9685.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include "config.h"
#include "controls.h"
#include "display.h"
#include "sensors.h"

// Add this function prototype at the top
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map);
void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data);

// Global variables
lv_display_t * disp = NULL;
lv_indev_t * touch_indev = NULL;

// Rest of your code remains the same...
// Forward declarations of event callbacks
void led_btn_event_cb(lv_event_t * e);
void mist_btn_event_cb(lv_event_t * e);
void fan_slider_event_cb(lv_event_t * e);

// Component initialization
TFT_eSPI tft = TFT_eSPI();
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);
Adafruit_BME280 bme;
PCA9685 pwm;

// LVGL objects
lv_obj_t *main_screen;
lv_obj_t *temp_label;
lv_obj_t *humid_label;
lv_obj_t *pressure_label;
lv_obj_t *temp_arc;
lv_obj_t *humid_arc;
lv_obj_t *device_panel;
lv_obj_t *chart;
lv_chart_series_t *temp_series;
lv_chart_series_t *humid_series;

// System state
struct {
    bool mist_active;
    bool led_active;
    bool fan_active;
    float temperature;
    float humidity;
    float pressure;
    uint32_t last_sensor_read;
    uint32_t last_data_log;
} state = {0};

void setup() {
    Serial.begin(115200);
    
    // Initialize display and touch
    init_display();
    init_touch();
    
    // Initialize sensors and controls
    init_sensors();
    init_controls();
    
    // Create the UI
    create_ui();
    
    // Initialize state
    state.last_sensor_read = 0;
    state.last_data_log = 0;

    Serial.println("Setup complete!");
}

void loop() {
    // Add LVGL tick
    lv_tick_inc(5);
    
    // Read sensors every 2 seconds
    if (millis() - state.last_sensor_read >= 2000) {
        SensorData sensor_data = read_sensors();
        state.temperature = sensor_data.temperature;
        state.humidity = sensor_data.humidity;
        state.pressure = sensor_data.pressure;
        
        update_sensor_displays(state.temperature, state.humidity, state.pressure);
        state.last_sensor_read = millis();
        
        // Debug output
        Serial.printf("Temp: %.1f°C, Humidity: %.1f%%, Pressure: %.1f hPa\n",
                     state.temperature, state.humidity, state.pressure);
    }

    // Handle LVGL tasks
    lv_timer_handler();
    
    // Small delay to prevent watchdog timer issues
    delay(5);
}

// Event callback implementations
void led_btn_event_cb(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        state.led_active = !state.led_active;
        setLED(state.led_active);
        
        // Update button state visually
        lv_obj_t * btn = (lv_obj_t *)lv_event_get_target(e);
        if(state.led_active) {
            lv_obj_add_state(btn, LV_STATE_CHECKED);
        } else {
            lv_obj_clear_state(btn, LV_STATE_CHECKED);
        }
    }
}

void mist_btn_event_cb(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        state.mist_active = !state.mist_active;
        setMist(state.mist_active);
        
        // Update button state visually
        lv_obj_t * btn = (lv_obj_t *)lv_event_get_target(e);
        if(state.mist_active) {
            lv_obj_add_state(btn, LV_STATE_CHECKED);
        } else {
            lv_obj_clear_state(btn, LV_STATE_CHECKED);
        }
    }
}

void fan_slider_event_cb(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t * slider = (lv_obj_t *)lv_event_get_target(e);
        int32_t value = lv_slider_get_value(slider);
        state.fan_active = value > 0;
        // Map 0-100 to 0-4095 for PWM
        uint16_t pwm_value = map(value, 0, 100, 0, 4095);
        setFan(pwm_value);
    }
}
