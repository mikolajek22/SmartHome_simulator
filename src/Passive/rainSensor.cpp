#include "rainSensor.h"

RainSensor::RainSensor() : Device(), raining(false)
{

}
RainSensor::RainSensor(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway) :
                            Device(mac, ipAddress, mask, defaultGateway), raining(false)
{

}
bool RainSensor::getValue() const
{
    return raining;
}