#pragma once

#include "device.h"

class AirQualitySensor : public Device{
    public:
        AirQualitySensor();
        AirQualitySensor(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway);
        float getQuality() const;
    private:
        float quality;
};