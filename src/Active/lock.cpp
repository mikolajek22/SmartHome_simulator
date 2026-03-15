#include "lock.h"

Lock::Lock() : Device(), value(false)
{

}
Lock::Lock(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway) :
                            Device(mac, ipAddress, mask, defaultGateway), value(false)
{

}
bool Lock::getValue() const
{
    return value;
}

void Lock::setValue(bool v)
{
    value =v;
}