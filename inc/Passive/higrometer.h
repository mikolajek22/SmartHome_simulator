#pragma once

#include "device.h"

class Higrometer : public Device{
    public:
        Higrometer();
        Higrometer(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway);
        float getHumidity() const;
    private:
        float humidity;
};