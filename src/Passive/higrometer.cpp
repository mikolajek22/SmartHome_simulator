#include "higrometer.h"

Higrometer::Higrometer() : Device(), humidity(0.0f)
{

}
Higrometer::Higrometer(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway) :
                            Device(mac, ipAddress, mask, defaultGateway), humidity(0.0f)
{

}
float Higrometer::getHumidity() const
{
    return humidity;
}