#include <dawn/resources/dawnDynamicBuffer.hpp>
#include <dawn/dawnDevice.hpp>

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

        wgpu::BindGroupLayout bgLayout = nullptr;
    
        {
			wgpu::BufferDescriptor bdesc = {};
			bdesc.usage = gfx::DecodeBufferUsageType(desc.usage | gfx::BufferUsage::COPY_DST);
            bdesc.size = desc.bufferSize;
			s_Buffer = device.CreateBuffer(&bdesc);
        }
        
        {
            wgpu::BindGroupLayoutEntry entry = {};
            wgpu::BindGroupLayoutDescriptor layoutDesc = {};

            gfx::BufferBindingType type = desc.usage == gfx::BufferUsage::UNIFORM ? gfx::BufferBindingType::UNIFORM : gfx::BufferBindingType::STORAGE;

            entry.binding = 0;
            entry.visibility = wgpu::ShaderStage::Vertex | wgpu::ShaderStage::Fragment;
            entry.buffer.hasDynamicOffset = true;
            entry.buffer.type = gfx::DecodeBufferBindingType(type);

            layoutDesc.entries = &entry;
            layoutDesc.entryCount = 1;

            bgLayout = device.CreateBindGroupLayout(&layoutDesc);
        }

        { 
            wgpu::BindGroupEntry entry = {};
            wgpu::BindGroupDescriptor bgDesc = {};
            
            entry.binding = 0;
            entry.buffer = s_Buffer;
            entry.offset = 0;
            entry.size = desc.bufferRange;

            bgDesc.entries = &entry;
            bgDesc.entryCount = 1;
            bgDesc.layout = bgLayout;

            s_BindGroup = device.CreateBindGroup(&bgDesc);
        } 

        // releasing the layout after the creation of the bingGroup
        bgLayout = nullptr;
    }

    void DawnDynamicBuffer::Destroy()
    {
        if (s_Buffer != nullptr)
            s_Buffer.Destroy(); 

        s_BindGroup = nullptr;
    }
}