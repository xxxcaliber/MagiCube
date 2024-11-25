// main_gui.cpp
#include <cstdio>
#include "main_gui.h"

// Define GUI elements
lv_obj_t *main_screen = nullptr;
lv_obj_t *tabview = nullptr;
lv_obj_t *main_page = nullptr;
lv_obj_t *status_bar = nullptr;
lv_obj_t *time_label = nullptr;
lv_obj_t *temp_arc = nullptr;
lv_obj_t *humid_arc = nullptr;
lv_obj_t *temp_label = nullptr;
lv_obj_t *humid_label = nullptr;

// main_gui.cpp
// ... (previous includes and declarations remain the same)

static void create_status_bar() {
    // Create time label directly on main screen instead of status bar
    time_label = lv_label_create(main_screen);
    lv_label_set_text(time_label, "12:00");
    lv_obj_align(time_label, LV_ALIGN_BOTTOM_RIGHT, -10, -5);
    lv_obj_set_style_text_color(time_label, lv_color_hex(0xFFFFFF), 0);  //jg was FFFFFF
    
    // Create style for larger time text
    static lv_style_t style_time;
    lv_style_init(&style_time);
    lv_style_set_text_font(&style_time, &lv_font_montserrat_22);
    lv_obj_add_style(time_label, &style_time, 0);
}

static void create_gauges() {
    // Create temperature arc
    temp_arc = lv_arc_create(main_page);
    lv_obj_set_size(temp_arc, 150, 150);
    lv_obj_align(temp_arc, LV_ALIGN_CENTER, -79, 0);
    lv_arc_set_rotation(temp_arc, 135);
    lv_arc_set_bg_angles(temp_arc, 0, 270);
    lv_arc_set_value(temp_arc, 0);
    lv_obj_set_style_arc_color(temp_arc, THEME_SUCCESS, LV_PART_MAIN);
    
    // Temperature label with larger font
    temp_label = lv_label_create(temp_arc);
    lv_label_set_text(temp_label, "0°F");
    lv_obj_align(temp_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(temp_label, THEME_GOLD, 0);
    
    // Create style for larger temperature text
    static lv_style_t style_temp;
    lv_style_init(&style_temp);
    lv_style_set_text_font(&style_temp, &lv_font_montserrat_28);
    lv_obj_add_style(temp_label, &style_temp, 0);

    // Create humidity arc
    humid_arc = lv_arc_create(main_page);
    lv_obj_set_size(humid_arc, 150, 150);
    lv_obj_align(humid_arc, LV_ALIGN_CENTER, 79, 0);
    lv_arc_set_rotation(humid_arc, 135);
    lv_arc_set_bg_angles(humid_arc, 0, 270);
    lv_arc_set_value(humid_arc, 0);
    lv_obj_set_style_arc_color(humid_arc, THEME_SUCCESS, LV_PART_MAIN);
    
    // Humidity label with larger font
    humid_label = lv_label_create(humid_arc);
    lv_label_set_text(humid_label, "0%");
    lv_obj_align(humid_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(humid_label, THEME_GOLD, 0);
    
    // Create style for larger humidity text
    static lv_style_t style_humid;
    lv_style_init(&style_humid);
    lv_style_set_text_font(&style_humid, &lv_font_montserrat_28);
    lv_obj_add_style(humid_label, &style_humid, 0);
}

void create_main_gui() {
    // Create main screen
    main_screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(main_screen, THEME_BACKGROUND, 0);
    
    // Create status bar
    create_status_bar();
    
    // Create tabview
    tabview = lv_tabview_create(main_screen);
    lv_obj_set_style_bg_color(tabview, THEME_BACKGROUND, 0);
    lv_obj_align(tabview, LV_ALIGN_TOP_LEFT, 0, 0); // jg was 0, 30
    lv_obj_set_size(tabview, 320, 240); //jg was 240

    //lv_obj_set_style_bg_color(tabview, lv_palette_lighten(LV_PALETTE_RED, 2), 0); //

    lv_obj_t * tab_btns = lv_tabview_get_tab_btns(tabview);  // jg added this section to adjust size of tabs
    lv_obj_set_style_pad_all(tab_btns, 5, 0); // Reduce padding
    lv_obj_set_style_bg_color(tab_btns, THEME_GOLD, 0); // jg added line
    lv_obj_set_style_height(tab_btns, 30, 0); // Make tabs shorter
    lv_obj_align(tab_btns, LV_ALIGN_TOP_LEFT, 5, 2); // Position at top
    
    // Add tabs
    main_page = lv_tabview_add_tab(tabview, "Main");
    lv_tabview_add_tab(tabview, "Set");
    lv_tabview_add_tab(tabview, "Log");
    lv_tabview_add_tab(tabview, "Sys");
    lv_obj_set_style_text_color(tab_btns, THEME_SUCCESS, 0);
    //lv_obj_set_style_text_color(tabview, THEME_GOLD, 0);  //jg was FFFFFF
    //lv_obj_set_style_bg_color(tabview, lv_palette_lighten(LV_PALETTE_AMBER, 3), 0);  // jg added line
    //lv_obj_set_style_bg_opa(tab_btns, LV_OPA_COVER, 0); // jg added line

    // Create gauges on main page
    create_gauges();
    
    lv_scr_load(main_screen);
}

void update_environmental_data(float temp, float humidity) {
    if(temp_arc && humid_arc) {
        // Update temperature
        lv_arc_set_value(temp_arc, (int)temp);
        char temp_str[16];
        snprintf(temp_str, sizeof(temp_str), "%.1f°F", temp);
        lv_label_set_text(temp_label, temp_str);
        
        // Update humidity
        lv_arc_set_value(humid_arc, (int)humidity);
        char humid_str[16];
        snprintf(humid_str, sizeof(humid_str), "%.0f%%", humidity);
        lv_label_set_text(humid_label, humid_str);
        
        // Update arc colors based on values
        if(temp < 30) {
            lv_obj_set_style_arc_color(temp_arc, THEME_SUCCESS, LV_PART_MAIN);
        } else if(temp < 60) {
            lv_obj_set_style_arc_color(temp_arc, THEME_WARNING, LV_PART_MAIN);
        } else {
            lv_obj_set_style_arc_color(temp_arc, lv_color_hex(0xFF0000), LV_PART_MAIN);
        }
    }
}