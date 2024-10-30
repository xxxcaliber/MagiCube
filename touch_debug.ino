#include <SPI.h>
#include <XPT2046_Touchscreen.h>

// Touch pins
#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

// Create touchscreen object
SPIClass touchSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Touch Debug Test Starting...");
    
    // Initialize touch SPI
    touchSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    touchscreen.begin(touchSPI);
    touchscreen.setRotation(-1);
    
    Serial.println("Touch initialized");
}

void loop() {
    if (touchscreen.tirqTouched() && touchscreen.touched()) {
        TS_Point p = touchscreen.getPoint();
        
        // Print raw values
        Serial.print("Raw X: "); Serial.print(p.x);
        Serial.print(", Raw Y: "); Serial.print(p.y);
        Serial.print(", Pressure: "); Serial.println(p.z);
        
        // Calculate mapped values
        int mappedX = map(p.x, 200, 3700, 0, 240);
        int mappedY = map(p.y, 240, 3800, 0, 320);
        
        // Print mapped values
        Serial.print("Mapped X: "); Serial.print(mappedX);
        Serial.print(", Mapped Y: "); Serial.println(mappedY);
        Serial.println("-------------------");
    }
    delay(50);
}
