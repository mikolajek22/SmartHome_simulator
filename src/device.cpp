#include "device.h"

uint32_t Device::deviceCount = 0;
uint32_t Device::devices[8] = {0};
Device::Device()
{
    /* Find Next free index for the device in the table */
    uniqID = allocateId();
}


Device::Device(uint8_t (&mac)[MAC_SIZE], uint32_t ipAddress, uint32_t mask, uint32_t defaultGateway) :
                network_settings{{}, ipAddress, mask, defaultGateway}

{
    for (uint8_t i = 0; i < MAC_SIZE; i++) 
    {
        this->network_settings.mac[i] = mac[i];
    }
    /* Find Next free index for the device in the table */
    uniqID = allocateId();
}


Device::~Device()
{
    if (uniqID != 0xFFFFFFFF)
    {
        uint8_t i = uniqID / 32;
        uint8_t j = uniqID % 32;
        devices[i] &= ~(1u << j);
        deviceCount--;
    }
    
}

bool Device::set_Ip(uint32_t ipAddress)
{
    this->network_settings.ipAddress = ipAddress;
    return true;
}


bool Device::set_Mask(uint32_t mask)
{
    this->network_settings.mask = mask;
    return true;
}


bool Device::set_Gateway(uint32_t defaultGateway)
{
    this->network_settings.defaultGateway = defaultGateway;
    return true;
}


bool Device::set_Mac(uint8_t (&mac)[MAC_SIZE])
{
    for (uint8_t i = 0; i < MAC_SIZE; i++) 
    {
        this->network_settings.mac[i] = mac[i];
    }
    return true;
}

uint32_t Device::get_Ip() const
{
    return this->network_settings.ipAddress;
}


uint32_t Device::get_Mask() const
{
    return this->network_settings.mask;
}


uint32_t Device::get_Gateway() const
{
    return this->network_settings.defaultGateway;
}


void Device::get_Mac(uint8_t (&mac)[MAC_SIZE]) const
{
for (uint8_t i = 0; i < MAC_SIZE; i++) 
    {
        mac[i] = this->network_settings.mac[i];
    }
}

uint32_t Device::allocateId() {
    for (uint8_t i = 0; i < 8; i++)
    {
        for (uint8_t j = 0; j < 32; j++)
        {
            if (!((devices[i] >> j) & 0b1))
            {
                devices[i] |= (0b1 << j);
                deviceCount++;
                return i * 32 + j;
            }
        }
    }
    return 0xFFFFFFFF;
}


