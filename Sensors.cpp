     #include "sensors.h"
     #include "config.h"

     extern Adafruit_BME280 bme;  // Changed from definition to extern declaration

     void init_sensors() {
         if (!bme.begin(0x76)) {
             Serial.println("Could not find BME280 sensor!");
             while (1) delay(10);
         }
     }

     SensorData read_sensors() {
         SensorData data;
         data.temperature = bme.readTemperature();
         data.humidity = bme.readHumidity();
         data.pressure = bme.readPressure() / 100.0F;
         return data;
     }