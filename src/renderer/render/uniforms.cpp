#include <render/uniforms.hpp>
#include <resources/resourceManger.hpp>
#include <device.hpp>

namespace gfx
{
	UniformRingBuffer::UniformRingBuffer(uint32_t size)
		:	m_BufferSize(size), m_Alignment(Device::instance->s_AdapterDesc.minUniformBufferOffsetAlignment), m_CurrentOffset(0), m_HeadOffset(0)
	{ 
		m_Layout = ResourceManager::instance->Create(BindGroupLayoutDescriptor{
			.bufferBindings = {
				{.slot = 0, .hasDynamicOffset = true }
			}
			});

		m_Buffer = ResourceManager::instance->Create(DynamicBufferDescriptor{
			.usage = gfx::BufferUsage::UNIFORM,
			.bufferSize = size,
			.bufferRange = GPU_BUFFER_BINDING_RANGE,
			.bindGroupLayout = m_Layout
			});

		m_BufferData = operator new(size);
	}

	void UniformRingBuffer::Upload()
	{
		//if (m_HeadOffset > m_CurrentOffset)
		//{
		//	uint32_t remainingSize = m_BufferSize - m_HeadOffset;
		//	uint32_t rappedSize = m_CurrentOffset;

		//	ResourceManager::instance->SetBufferData(m_Buffer, m_HeadOffset, (void*)((char*)m_BufferData + m_HeadOffset), remainingSize);
		//	ResourceManager::instance->SetBufferData(m_Buffer, 0, (void*)((char*)m_BufferData), rappedSize);
		//}
		//else
		//{
		//	uint32_t size = m_CurrentOffset - m_HeadOffset;

		//	ResourceManager::instance->SetBufferData(m_Buffer, m_HeadOffset, (void*)((char*)m_BufferData + m_HeadOffset), size);
		//}
		
		ResourceManager::instance->SetBufferData(m_Buffer, 0, m_BufferData, m_BufferSize);
		m_HeadOffset = m_CurrentOffset;
	}

	void UniformRingBuffer::Destroy()
	{ 
		operator delete(m_BufferData); 
		ResourceManager::instance->Remove(m_Buffer);
	}

	utils::Handle<gfx::DynamicBuffer> UniformRingBuffer::GetBuffer()
	{
		return m_Buffer;
	}

	utils::Handle<gfx::BindGroupLayout> UniformRingBuffer::GetLayout()
	{
		return m_Layout;
	}
}