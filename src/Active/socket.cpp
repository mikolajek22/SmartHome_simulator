#include "socket.h"

Socket::Socket() : Device(), value(false)
{

}
Socket::Socket(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway) :
                            Device(mac, ipAddress, mask, defaultGateway), value(false)
{

}
bool Socket::getValue() const
{
    return value;
}

void Socket::setValue(bool v)
{
    value =v;
}