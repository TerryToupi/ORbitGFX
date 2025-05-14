#include <render/uniforms.hpp>
#include <resources/resourceManger.hpp>
#include <device.hpp>

namespace gfx
{
	UniformRingBuffer::UniformRingBuffer(uint32_t size)
		:	m_BufferSize(size), m_Alignment(Device::instance->s_AdapterDesc.minUniformBufferOffsetAlignment), m_CurrentOffset(0), m_HeadOffset(0)
	{ 
		m_Buffer = ResourceManager::instance->Create(DynamicBufferDescriptor{
			.usage = gfx::BufferUsage::UNIFORM,
			.bufferSize = size,
			.bufferRange = GPU_BUFFER_BINDING_RANGE
			});

		m_BufferData = operator new(size);
	}

	void UniformRingBuffer::Upload()
	{
		ResourceManager::instance->SetBufferData(m_Buffer, m_HeadOffset, (void*)((char*)m_BufferData + m_HeadOffset), m_HeadOffset + m_CurrentOffset); 
		m_HeadOffset = m_CurrentOffset;
	}

	void UniformRingBuffer::Destroy()
	{ 
		operator delete(m_BufferData); 
		ResourceManager::instance->Remove(m_Buffer);
	}
}