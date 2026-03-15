#include "lightSensor.h"

LightSensor::LightSensor() : Device(), light(0.0f)
{

}
LightSensor::LightSensor(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway) :
                            Device(mac, ipAddress, mask, defaultGateway), light(0.0f)
{

}
float LightSensor::getLight() const
{
    return light;
}