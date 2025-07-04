#include <dawn/resources/dawnDynamicBuffer.hpp>
#include <dawn/resources/dawnResourceManager.hpp>
#include <dawn/dawnDevice.hpp>
#include <log.hpp>
#include <assert.hpp>

namespace gfx
{
    DawnDynamicBuffer::DawnDynamicBuffer()
        :   s_Buffer(nullptr), s_BindGroup(nullptr)
    {
    }

    DawnDynamicBuffer::DawnDynamicBuffer(const DynamicBufferDescriptor& desc)
    {
        DawnDevice* deviceInstance = (DawnDevice*)Device::instance;
        wgpu::Device device = deviceInstance->GetDawnDevice();
        DawnResourceManager* rm = (DawnResourceManager*)ResourceManager::instance;
    
        {
			wgpu::BufferDescriptor bdesc = {};
			bdesc.usage = gfx::DecodeBufferUsageType(desc.usage | gfx::BufferUsage::COPY_DST);
            bdesc.size = desc.bufferSize;
			s_Buffer = device.CreateBuffer(&bdesc);
        }
        
        { 
            DawnBindGroupLayout* bgl = rm->Get(desc.bindGroupLayout);
            if (bgl)
            {
                wgpu::BindGroupEntry entry = {};
                wgpu::BindGroupDescriptor bgDesc = {};

                entry.binding = 0;
                entry.buffer = s_Buffer;
                entry.offset = 0;
                entry.size = desc.bufferRange;

                bgDesc.entries = &entry;
                bgDesc.entryCount = 1;
                bgDesc.layout = bgl->s_BindGroupLayout;

                s_BindGroup = device.CreateBindGroup(&bgDesc);
            }
            else
                GFX_ERROR("Provided bindgroup layout in the dynamicBuffer creation was null!");
        }

        // saving the desc for resize
        s_Desc = desc;
    }

    void DawnDynamicBuffer::Resize()
    {
        DawnDevice* deviceInstance = (DawnDevice*)Device::instance;
        wgpu::Device device = deviceInstance->GetDawnDevice();
        DawnResourceManager* rm = (DawnResourceManager*)ResourceManager::instance;

        Destroy();

        s_Desc.bufferSize *= 2;
        
        {
            wgpu::BufferDescriptor bdesc = {};
            bdesc.usage = gfx::DecodeBufferUsageType(s_Desc.usage | gfx::BufferUsage::COPY_DST);
            bdesc.size = s_Desc.bufferSize;
            s_Buffer = device.CreateBuffer(&bdesc);
        }

        {
            DawnBindGroupLayout* bgl = rm->Get(s_Desc.bindGroupLayout);
            if (bgl)
            {
                wgpu::BindGroupEntry entry = {};
                wgpu::BindGroupDescriptor bgDesc = {};

                entry.binding = 0;
                entry.buffer = s_Buffer;
                entry.offset = 0;
                entry.size = s_Desc.bufferRange;

                bgDesc.entries = &entry;
                bgDesc.entryCount = 1;
                bgDesc.layout = bgl->s_BindGroupLayout;

                s_BindGroup = device.CreateBindGroup(&bgDesc);
            }
            else
                GFX_ERROR("Provided bindgroup layout in the dynamicBuffer creation was null!");
        }
    }

    void DawnDynamicBuffer::Destroy()
    {
        if (s_Buffer != nullptr)
            s_Buffer.Destroy(); 

        s_Buffer = nullptr;
        s_BindGroup = nullptr;
    }
}