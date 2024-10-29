#ifndef CONTROLS_H
#define CONTROLS_H

#include <PCA9685.h>
#include "config.h"

void init_controls();
void setLED(bool state);
void setFan(uint16_t speed);
void setMist(bool state);

#endif // CONTROLS_H