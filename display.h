#ifndef DISPLAY_H
#define DISPLAY_H

#include <lvgl.h>
#include <TFT_eSPI.h>
#include "config.h"

// Function declarations
void init_display();
void init_touch();
void create_ui();
void update_sensor_displays(float temp, float humid, float pressure);

// Event callback declarations - declare as extern
extern void led_btn_event_cb(lv_event_t * e);
extern void mist_btn_event_cb(lv_event_t * e);
extern void fan_slider_event_cb(lv_event_t * e);

#endif // DISPLAY_H