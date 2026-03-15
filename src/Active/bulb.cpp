#include "bulb.h"

Bulb::Bulb() : Device(), value(false)
{

}
Bulb::Bulb(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway) :
                            Device(mac, ipAddress, mask, defaultGateway), value(false)
{

}
bool Bulb::getValue() const
{
    return value;
}

void Bulb::setValue(bool v)
{
    value =v;
}