#include "../features/BmeSensor.h"
#include "Device.h"


constexpr const char BME_NAME[] = "bme"

class EsensDevice : public Device {
public:
    EsensDevice() :
            bme(this)
    {
        this->add(&(this->bme));
    }

private:
    BmeSensor<BME_NAME> bme;
};


Device* createDevice() {
    return new EsensDevice();
}
