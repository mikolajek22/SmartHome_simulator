#include "airQualitySensor.h"

AirQualitySensor::AirQualitySensor() : Device(), quality(0.0f)
{

}
AirQualitySensor::AirQualitySensor(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway) :
                            Device(mac, ipAddress, mask, defaultGateway), quality(0.0f)
{

}
float AirQualitySensor::getQuality() const
{
    return quality;
}