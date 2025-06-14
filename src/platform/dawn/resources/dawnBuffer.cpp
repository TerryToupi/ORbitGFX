#include <dawn/dawnDevice.hpp>
#include <dawn/resources/dawnBuffer.hpp>

#define ALIGN_TO_NEXT_MULTIPLE(n, k) ((n + k) & ~k)

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
		bdesc.usage = gfx::DecodeBufferUsageType(desc.usage) | wgpu::BufferUsage::CopyDst;
		bdesc.mappedAtCreation = desc.initialData.data() == nullptr ? false : true;
		bdesc.size = ALIGN_TO_NEXT_MULTIPLE(desc.byteSize, 4);

		s_Buffer = device.CreateBuffer(&bdesc); 

		if (desc.initialData.data() != nullptr)
		{
			void* data = s_Buffer.GetMappedRange(0, ALIGN_TO_NEXT_MULTIPLE(desc.byteSize, 4));
			memcpy(data, desc.initialData.data(), desc.initialData.size());
			s_Buffer.Unmap(); 
		}
	}

	void DawnBuffer::Destroy()
	{
		if (s_Buffer != nullptr)
			s_Buffer.Destroy();
	}
}