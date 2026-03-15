#include "barometer.h"

Barometer::Barometer() : Device(), pressure(0.0f)
{

}
Barometer::Barometer(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway) :
                            Device(mac, ipAddress, mask, defaultGateway), pressure(0.0f)
{

}
float Barometer::getPressure() const
{
    return pressure;
}