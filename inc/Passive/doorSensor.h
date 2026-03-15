#pragma once

#include "device.h"

class DoorSensor : public Device{
    public:
        DoorSensor();
        DoorSensor(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway);
        bool getValue() const;
    private:
        bool open;
};