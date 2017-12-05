#include "../features/BmeSensor.h"
#include "Device.h"


constexpr const char BME_NAME[] = "bme280";
const uint8_t addr = 0x76;

class EsensDevice : public Device {
public:
    EsensDevice() :
            bme(this, addr)
    {
        this->add(&(this->bme));
    }

private:
    BmeSensor<BME_NAME> bme;
};


Device* createDevice() {
    return new EsensDevice();
}
