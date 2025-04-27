#include <dawn/dawnDevice.hpp>
#include <dawn/resources/dawnBuffer.hpp>

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
		bdesc.mappedAtCreation = desc.data == nullptr ? false : true;
		bdesc.size = desc.size;

		s_Buffer = device.CreateBuffer(&bdesc); 

		if (desc.data != nullptr)
		{
			void* data = s_Buffer.GetMappedRange(0, desc.size);
			memcpy(data, desc.data, desc.size);
			s_Buffer.Unmap();
		}
	}

	void DawnBuffer::Destroy()
	{
		s_Buffer.Destroy();
	}
}