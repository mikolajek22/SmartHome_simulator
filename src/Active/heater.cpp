#include "heater.h"

Heater::Heater() : Device(), value(false)
{

}
Heater::Heater(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway) :
                            Device(mac, ipAddress, mask, defaultGateway), value(false)
{

}
bool Heater::getValue() const
{
    return value;
}

void Heater::setValue(bool v)
{
    value =v;
}