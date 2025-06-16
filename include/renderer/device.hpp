#ifndef __DEVICE_HPP__
#define __DEVICE_HPP__

#include <string>
#include <cstdlib>
#include <cstddef>
#include <cstdint>

namespace gfx
{
    struct DeviceDescriptor
    {
        uint32_t vendorID;
        std::string vendor;
        std::string architecture;
        uint32_t deviceID;
        std::string name;
        std::string driver;
    };
    
    class Device
    {
    public:
        static inline Device* instance = nullptr;
        
        virtual ~Device() = default;
        
        virtual void Init() = 0;
        virtual void ShutDown() = 0;

    public:
        DeviceDescriptor s_DeviceDesc;
    };
}

#endif
