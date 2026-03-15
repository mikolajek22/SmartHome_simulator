#include "conditioning.h"

Conditioning::Conditioning() : Device(), value(false)
{

}
Conditioning::Conditioning(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway) :
                            Device(mac, ipAddress, mask, defaultGateway), value(false)
{

}
bool Conditioning::getValue() const
{
    return value;
}

void Conditioning::setValue(bool v)
{
    value =v;
}