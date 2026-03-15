#include "soilHumiditySensor.h"

SoilHumiditySensor::SoilHumiditySensor() : Device(), humidity(0.0f)
{

}
SoilHumiditySensor::SoilHumiditySensor(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway) :
                            Device(mac, ipAddress, mask, defaultGateway), humidity(0.0f)
{

}
float SoilHumiditySensor::getHumidity() const
{
    return humidity;
}