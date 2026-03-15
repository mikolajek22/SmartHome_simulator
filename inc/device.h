#pragma once

#include <cstdio>
#include <cstdint>

#define MAC_SIZE        6
#define ADDRESS_SIZE    4
#define MAX_DEFINED_DEVICES 256

struct Network {
    uint8_t mac[MAC_SIZE];
    uint32_t ipAddress;
    uint32_t mask;
    uint32_t defaultGateway;
};

class Device {
    public:
        Device();
        Device(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway);
        ~Device();
        /* Network Settings Setters*/
        bool set_Ip(uint32_t ipAddress);
        bool set_Mask(uint32_t mask);
        bool set_Gateway(uint32_t defaultGateway);
        bool set_Mac(uint8_t (&mac)[MAC_SIZE]);

        /* Network Settings getters */
        uint32_t get_Ip() const;
        uint32_t get_Mask() const;
        uint32_t get_Gateway() const;
        void get_Mac(uint8_t (&mac)[MAC_SIZE]) const;
    protected:
        
        Network network_settings;
        
    private:
        uint32_t allocateId();
        uint32_t uniqID;
        static uint32_t deviceCount;
        static uint32_t devices[8]; // From max devices (8 * 32 bits)
        

};