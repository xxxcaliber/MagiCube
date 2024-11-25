// Configuration for ESP32-2432S024R Display
// https://www.aliexpress.com/item/1005005865107357.html

#define USER_SETUP_INFO "ESP32-2432S024R"

// Define the display driver
#define ILI9341_2_DRIVER  // jg ILI9341_2_DRIVER

// Display resolution
#define TFT_WIDTH  320 // swapped these two
#define TFT_HEIGHT 240

#define TFT_INVERSION_ON  // JG WAS ON

// Display orientation settings
#define DISPLAY_SWAP_XY false
#define DISPLAY_MIRROR_X true
#define DISPLAY_MIRROR_Y false

// Define SPI pins for display
#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15  // Chip select control pin
#define TFT_DC    2  // Data Command control pin
#define TFT_RST  -1  // Set to -1 if not used
#define TFT_BL   27  // LED back-light control pin

// Touch screen SPI pins (XPT2046)
#define TOUCH_CS 33  // Touch screen chip select
#define TOUCH_IRQ 36 // Touch screen interrupt pin

// Define SPI clock frequencies
#define SPI_FREQUENCY       24000000  // Display SPI frequency
#define SPI_READ_FREQUENCY  20000000  // Display read frequency
#define SPI_TOUCH_FREQUENCY  2000000  // Touch controller SPI frequency

// Load the required fonts
#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:-.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

#define SMOOTH_FONT

// Color order
#define TFT_RGB_ORDER TFT_BGR 

// Optional SPI transactions
#define SUPPORT_TRANSACTIONS
