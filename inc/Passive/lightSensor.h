#pragma once

#include "device.h"

class LightSensor : public Device{
    public:
        LightSensor();
        LightSensor(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway);
        float getLight() const;
    private:
        float light;
};