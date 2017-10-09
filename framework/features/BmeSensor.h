#ifndef BME280_SENSOR_H
#define BME280_SENSOR_H

#include "Feature.h"
#include <Libraries/Adafruit_BME280/Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

template<const char* const name, const int scl_gpio = 14, const int sda_gpio = 12>
class BmeSensor : public Feature<name> {

protected:
    using Feature<name>::LOG;
    Adafruit_BME280 bme;

public:

    BmeSensor(Device* device) :
            Feature<name>(device) {

            bool status;
            Wire.begin(scl_gpio, sda_gpio);
            status = bme.init();
            if (!status) {
                Serial.println("Could not find a valid BME280 sensor, check wiring!");
                while (1);
            }

            Serial.println("-- Default Test --");
            delayTime = 1000;

            Serial.println();

            delay(100); // let sensor boot up

            this->updateTimer.initializeMs(10000, TimerDelegate(&BmeSensor::publishCurrentState, this));
            this->updateTimer.start(/*repeating:*/true);
        }
    }

protected:
    virtual void publishCurrentState() {
        long currentPressure = bme.readPressure();
        LOG.log("currentPressure:", currentPressure);
        float currentTemperature = bme.readTemperature();
        LOG.log("currentTemperature:", currentTemperature);
        float currentHumidity = bme.readHumidity();
        Log.log("currentHumidity", currentHumidity);

        this->publish("pressure", String(currentPressure), true);
        this->publish("temperature", String(currentTemperature), true);
        this->publish("humidity", String(currentHumidity), true);
    }

private:
    Timer updateTimer;

};


#endif
