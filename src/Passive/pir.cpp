#include "pir.h"


Pir::Pir() : Device(), detected(false)
{

}
Pir::Pir(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway) :
                            Device(mac, ipAddress, mask, defaultGateway), detected(false)
{

}
bool Pir::getValue() const
{
    return detected;
}