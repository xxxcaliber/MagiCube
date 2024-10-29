#include "controls.h"
#include "config.h"
#include <Wire.h>

extern PCA9685 pwm;

void init_controls() {
    Wire.begin(SDA_PIN, SCL_PIN);
    pwm.setupSingleDevice(Wire, PCA9685_I2C_ADDRESS);
    pwm.setToFrequency(1000);
    
    for(int i = 0; i < 16; i++) {
        pwm.setChannelDutyCycle(i, 0);
    }
}

void setLED(bool state) {
    pwm.setChannelDutyCycle(LED_CHANNEL, state ? 4095 : 0);
}

void setFan(uint16_t speed) {
    pwm.setChannelDutyCycle(FAN_CHANNEL, speed);
}

void setMist(bool state) {
    pwm.setChannelDutyCycle(MIST_CHANNEL, state ? 4095 : 0);
}  // Added missing closing brace