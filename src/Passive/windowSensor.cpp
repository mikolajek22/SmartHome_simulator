#include "windowSensor.h"

WindowSensor::WindowSensor() : Device(), open(false)
{

}
WindowSensor::WindowSensor(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway) :
                            Device(mac, ipAddress, mask, defaultGateway), open(false)
{

}
bool WindowSensor::getValue() const
{
    return open;
}



