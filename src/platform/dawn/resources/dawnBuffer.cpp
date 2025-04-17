#include <platform/dawn/dawnDevice.hpp>
#include <platform/dawn/resources/dawnBuffer.hpp>

namespace gfx
{
	DawnBuffer::DawnBuffer()
		: s_Buffer(nullptr)
	{
	}

	DawnBuffer::DawnBuffer(const BufferDescriptor& desc)
	{
		DawnDevice* deviceInstance = (DawnDevice*)Device::instance; 
		wgpu::Device device = deviceInstance->GetDawnDevice();

		wgpu::BufferDescriptor bdesc = {};
		bdesc.usage = gfx::DecodeBufferUsageType(desc.usage | gfx::BufferUsage::COPY_DST);
		bdesc.size = desc.size;

		s_Buffer = device.CreateBuffer(&bdesc); 

		if (desc.data != nullptr)
			device.GetQueue().WriteBuffer(s_Buffer, 0, desc.data, desc.size);
	}

	void DawnBuffer::Destroy()
	{
		s_Buffer.Destroy();
	}
}