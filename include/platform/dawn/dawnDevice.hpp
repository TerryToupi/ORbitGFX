#ifndef __DAWN_DEVICE_HPP__
#define __DAWN_DEVICE_HPP__

#include <iostream>
#include <array>
#include <vector>

#include <dawn/dawnCommon.hpp>

#include <device.hpp>

namespace gfx
{
    class DawnDevice : public Device
    {
    public:
        virtual void Init() override;
        virtual void ShutDown() override; 

        virtual void SetDeviceDescriptor(const DeviceDescriptor& desc) override;
        virtual const DeviceDescriptor& GetDeviceDescriptor() override;
        
        const wgpu::Instance& GetDawnInstance();
        const wgpu::Adapter& GetDawnAdapter();
        const wgpu::Device& GetDawnDevice();
        
    private:
        wgpu::Instance m_Instance;
        wgpu::Adapter m_Adapter;
        wgpu::Device m_Device;
    };
}

#endif
