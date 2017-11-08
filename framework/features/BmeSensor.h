/* Bme Sensor makes use of the Adafruit BME280 Library which was forked into
 * Sming at github mschader/Sming
 * SDA -> D4, SCL -> D3 */

#ifndef BME280_SENSOR_H
#define BME280_SENSOR_H

#include "Feature.h"
#include <Libraries/Adafruit_BME280/Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

template<const char* const name>
class BmeSensor : public Feature<name> {

protected:
    using Feature<name>::LOG;
    Adafruit_BME280 bme;

public:

    BmeSensor(Device* device) :
            Feature<name>(device) {

            bool status;
            status = bme.begin();
            if (!status) {
                Serial.println("Could not find a valid BME280 sensor, check wiring!");
                while (1);
            }

            Serial.println("-- Default Test --");

            Serial.println();

            delay(100); // let sensor boot up

            this->updateTimer.initializeMs(10000, TimerDelegate(&BmeSensor::publishCurrentState, this));
            this->updateTimer.start(/*repeating:*/true);
        }

protected:
    virtual void publishCurrentState() {
        long currentPressure = bme.readPressure();
        LOG.log("currentPressure:", currentPressure);
        float currentTemperature = bme.readTemperature();
        LOG.log("currentTemperature:", currentTemperature);
        float currentHumidity = bme.readHumidity();
        LOG.log("currentHumidity", currentHumidity);

        this->publish("pressure", String(currentPressure), true);
        this->publish("temperature", String(currentTemperature), true);
        this->publish("humidity", String(currentHumidity), true);
    }

private:
    Timer updateTimer;

};


#endif
