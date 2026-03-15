#include "waterPump.h"

WaterPump::WaterPump() : Device(), value(false)
{

}
WaterPump::WaterPump(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway) :
                            Device(mac, ipAddress, mask, defaultGateway), value(false)
{

}
bool WaterPump::getValue() const
{
    return value;
}

void WaterPump::setValue(bool v)
{
    value =v;
}