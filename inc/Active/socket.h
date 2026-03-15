#pragma once

#include "device.h"

class Socket : public Device{
    public:
        Socket();
        Socket(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway);
        bool getValue() const;
        void setValue(bool v);
    private:
        bool value;
};