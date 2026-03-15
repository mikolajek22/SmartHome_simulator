#pragma once

#include "device.h"

class Thermometer : public Device{
    public:
        Thermometer();
        Thermometer(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway);
        float getTemperature() const;
        void simulate();
    private:
        float temperature;
};