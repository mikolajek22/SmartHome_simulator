#include "thermometer.h"

Thermometer::Thermometer() : Device(), temperature(0.0f)
{

}
Thermometer::Thermometer(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway) :
                            Device(mac, ipAddress, mask, defaultGateway), temperature(0.0f)
{

}
float Thermometer::getTemperature() const
{
    return temperature;
}

#include "thermometer.h"
#include <cstdlib>

void Thermometer::simulate()
{
    temperature = 15.0f + (rand() % 1500) / 100.0f; 
}