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
		bdesc.mappedAtCreation = desc.initialData.data() == nullptr ? false : true;
		bdesc.size = desc.byteSize;

		s_Buffer = device.CreateBuffer(&bdesc); 

		if (desc.initialData.begin() != nullptr)
		{
			void* data = s_Buffer.GetMappedRange(0, desc.byteSize);
			memcpy(data, desc.initialData.data(), desc.byteSize);
			s_Buffer.Unmap();
		}
	}

	void DawnBuffer::Destroy()
	{
		s_Buffer.Destroy();
	}
}