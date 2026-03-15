#pragma once

#include "device.h"

class SoilHumiditySensor : public Device{
    public:
        SoilHumiditySensor();
        SoilHumiditySensor(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway);
        float getHumidity() const;
    private:
        float humidity;
};