#pragma once

#include "device.h"

class RainSensor : public Device{
    public:
        RainSensor();
        RainSensor(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway);
        bool getValue() const;
    private:
        bool raining;
};