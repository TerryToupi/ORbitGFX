#include <render/uniforms.hpp>
#include <resources/resourceManger.hpp>
#include <dawn/dawnCommon.hpp>

namespace gfx
{
	UniformRingBuffer::UniformRingBuffer(uint32_t size)
		:	m_BufferSize(size), m_Alignment(minUniformBufferOffsetAlignment), m_CurrentOffset(0)
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
		if (m_HasWrapped)
		{
			// doubling the cappacity of the dynamic buffer
			ResourceManager::instance->ResizeDynamicBuffer(m_Buffer);
			// flushing the existing data
			ResourceManager::instance->SetBufferData(m_Buffer, 0, m_BufferData, m_BufferSize);
		
			m_BufferSize *= 2;

			// resize cpu buffer
			operator delete(m_BufferData);
			m_BufferData = nullptr;
			m_BufferData = operator new(m_BufferSize);

			//reset wrapped
			m_HasWrapped = false;
		}
		else
			ResourceManager::instance->SetBufferData(m_Buffer, 0, m_BufferData, m_CurrentOffset);

		m_CurrentOffset = 0;
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