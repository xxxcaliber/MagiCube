#ifndef SENSORS_H
#define SENSORS_H

#include <Adafruit_BME280.h>
#include "config.h"

struct SensorData {
    float temperature;
    float humidity;
    float pressure;
};

void init_sensors();
SensorData read_sensors();

#endif // SENSORS_H