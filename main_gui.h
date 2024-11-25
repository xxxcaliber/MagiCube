// main_gui.h
#ifndef MAIN_GUI_H
#define MAIN_GUI_H

#include <lvgl.h>

// GUI Colors
#define THEME_PRIMARY      lv_color_hex(0x2196F3)  // Blue jg orig 2196F3 / pallete 483D8B
#define THEME_SECONDARY    lv_color_hex(0x707070)  // Gray,
#define THEME_SUCCESS     lv_color_hex(0xffd700)   // Green jg orig 96f321
#define THEME_WARNING     lv_color_hex(0xffa726)   // Orange jg original was b350af
#define THEME_BACKGROUND  lv_color_hex(0x556B2F)   // Dark background  jg orig 1E1E1E jg 11-17 was 000000  / light olive 6B8E23
#define TAB_WIDTH         40                       // Width of side tabs
#define THEME_GOLD     lv_color_hex(0x800080)   // GOLD  ffd700

// GUI Elements
extern lv_obj_t *main_screen;
extern lv_obj_t *tabview;
extern lv_obj_t *main_page;
extern lv_obj_t *status_bar;
extern lv_obj_t *time_label;
extern lv_obj_t *temp_arc;
extern lv_obj_t *humid_arc;
extern lv_obj_t *temp_label;
extern lv_obj_t *humid_label;

// Function declarations
void create_main_gui();
void update_environmental_data(float temp, float humidity);

#endif