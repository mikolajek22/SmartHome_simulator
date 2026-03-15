#include "doorSensor.h"

DoorSensor::DoorSensor() : Device(), open(false)
{

}
DoorSensor::DoorSensor(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway) :
                            Device(mac, ipAddress, mask, defaultGateway), open(false)
{

}
bool DoorSensor::getValue() const
{
    return open;
}