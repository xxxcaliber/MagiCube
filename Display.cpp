#include "display.h"
#include <XPT2046_Touchscreen.h>
#include "config.h"

extern TFT_eSPI tft;
extern XPT2046_Touchscreen touchscreen;
extern lv_display_t * disp;
extern lv_indev_t * touch_indev;
extern lv_obj_t *main_screen;
extern lv_obj_t *temp_label;
extern lv_obj_t *humid_label;
extern lv_obj_t *pressure_label;
extern lv_obj_t *temp_arc;
extern lv_obj_t *humid_arc;
extern lv_obj_t *device_panel;

void my_disp_flush(lv_display_t *disp_drv, const lv_area_t *area, uint8_t *px_map) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)px_map, w * h, true);
    tft.endWrite();

    lv_display_flush_ready(disp_drv);
}

void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data) {
    uint16_t touchX, touchY;
    bool touched = touchscreen.touched();
    
    if (touched) {
        TS_Point p = touchscreen.getPoint();
        touchX = map(p.x, 200, 3700, 0, SCREEN_WIDTH);
        touchY = map(p.y, 240, 3800, 0, SCREEN_HEIGHT);
        data->state = LV_INDEV_STATE_PRESSED;
        data->point.x = touchX;
        data->point.y = touchY;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

void init_display() {
    tft.init();
    tft.setRotation(1); // Landscape mode
    
    lv_init();

    static lv_color_t buf1[SCREEN_WIDTH * 10];
    static lv_color_t buf2[SCREEN_WIDTH * 10];
    
    disp = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_display_set_flush_cb(disp, my_disp_flush);
    lv_display_set_buffers(disp, buf1, buf2, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);
}

void init_touch() {
    touchscreen.begin();
    touchscreen.setRotation(1);
    
    touch_indev = lv_indev_create();
    lv_indev_set_type(touch_indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(touch_indev, my_touchpad_read);
}

void update_sensor_displays(float temp, float humid, float pressure) {
    char buf[32];
    
    snprintf(buf, sizeof(buf), "Temp: %.1f C", temp);
    lv_label_set_text(temp_label, buf);
    
    snprintf(buf, sizeof(buf), "Humidity: %.1f%%", humid);
    lv_label_set_text(humid_label, buf);
    
    snprintf(buf, sizeof(buf), "Pressure: %.1f hPa", pressure);
    lv_label_set_text(pressure_label, buf);
    
    // Update arcs if they exist
    if (temp_arc != NULL) {
        lv_arc_set_value(temp_arc, (int16_t)temp);
    }
    if (humid_arc != NULL) {
        lv_arc_set_value(humid_arc, (int16_t)humid);
    }
}

void create_ui() {
    // Get the active screen
    main_screen = lv_scr_act();
    lv_obj_clean(main_screen);
    
    // Create a main container
    lv_obj_t *main_cont = lv_obj_create(main_screen);
    lv_obj_set_size(main_cont, SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_obj_align(main_cont, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(main_cont, 10, 0);
    
    // Create labels with proper styling
    temp_label = lv_label_create(main_cont);
    lv_obj_align(temp_label, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_set_style_text_font(temp_label, &lv_font_montserrat_16, 0);
    lv_label_set_text(temp_label, "Temp: --.-°C");
    
    humid_label = lv_label_create(main_cont);
    lv_obj_align(humid_label, LV_ALIGN_TOP_LEFT, 10, 40);
    lv_obj_set_style_text_font(humid_label, &lv_font_montserrat_16, 0);
    lv_label_set_text(humid_label, "Humidity: --.-%");
    
    pressure_label = lv_label_create(main_cont);
    lv_obj_align(pressure_label, LV_ALIGN_TOP_LEFT, 10, 70);
    lv_obj_set_style_text_font(pressure_label, &lv_font_montserrat_16, 0);
    lv_label_set_text(pressure_label, "Pressure: --.- hPa");
    
    // Create temperature arc
    temp_arc = lv_arc_create(main_cont);
    lv_obj_set_size(temp_arc, 100, 100);
    lv_obj_align(temp_arc, LV_ALIGN_TOP_RIGHT, -10, 10);
    lv_arc_set_range(temp_arc, 0, 50);  // 0-50°C range
    lv_arc_set_value(temp_arc, 0);
    lv_obj_set_style_arc_color(temp_arc, lv_color_make(255, 0, 0), LV_PART_INDICATOR);
    
    // Create humidity arc
    humid_arc = lv_arc_create(main_cont);
    lv_obj_set_size(humid_arc, 100, 100);
    lv_obj_align(humid_arc, LV_ALIGN_BOTTOM_RIGHT, -10, -10);
    lv_arc_set_range(humid_arc, 0, 100);  // 0-100% range
    lv_arc_set_value(humid_arc, 0);
    lv_obj_set_style_arc_color(humid_arc, lv_color_make(0, 0, 255), LV_PART_INDICATOR);
    
    // Create device control panel
    device_panel = lv_obj_create(main_cont);
    lv_obj_set_size(device_panel, 140, 120);
    lv_obj_align(device_panel, LV_ALIGN_BOTTOM_LEFT, 10, -10);
    lv_obj_set_style_pad_all(device_panel, 10, 0);
    
    // Add control buttons
    lv_obj_t *led_btn = lv_btn_create(device_panel);
    lv_obj_set_size(led_btn, 60, 30);
    lv_obj_align(led_btn, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_t *led_label = lv_label_create(led_btn);
    lv_label_set_text(led_label, "LED");
    lv_obj_center(led_label);
    
    lv_obj_t *mist_btn = lv_btn_create(device_panel);
    lv_obj_set_size(mist_btn, 60, 30);
    lv_obj_align(mist_btn, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_t *mist_label = lv_label_create(mist_btn);
    lv_label_set_text(mist_label, "Mist");
    lv_obj_center(mist_label);
    
    // Add fan slider
    lv_obj_t *fan_slider = lv_slider_create(device_panel);
    lv_obj_set_size(fan_slider, 120, 10);
    lv_obj_align(fan_slider, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_t *fan_label = lv_label_create(device_panel);
    lv_label_set_text(fan_label, "Fan Speed");
    lv_obj_align_to(fan_label, fan_slider, LV_ALIGN_OUT_TOP_MID, 0, -5);
}