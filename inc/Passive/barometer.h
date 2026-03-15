#pragma once

#include "device.h"

class Barometer : public Device{
    public:
        Barometer();
        Barometer(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway);
        float getPressure() const;
    private:
        float pressure;
};