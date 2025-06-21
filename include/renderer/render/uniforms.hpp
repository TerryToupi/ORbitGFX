#ifndef __UNIFORMS_HPP__
#define __UNIFORMS_HPP__

#include <handle.hpp>
#include <resources/buffer.hpp>
#include <resources/dynamicBuffer.hpp>

#define GPU_BUFFER_BINDING_RANGE 256// bytes

namespace gfx
{
	template<typename T>
	struct Allocation
	{
		T* ptr;
		uint32_t offset;
	};

	class UniformRingBuffer
	{
	public:
		UniformRingBuffer(uint32_t size);

		template<typename T>
		Allocation<T> BumpAllocate()
		{
			uint32_t divide_and_ceil = sizeof(T) / m_Alignment + (sizeof(T) % m_Alignment == 0 ? 0 : 1);
			uint32_t alignedStride = m_Alignment * divide_and_ceil;
			uint32_t blockIndex = m_CurrentOffset;
		
			if (m_CurrentOffset + GPU_BUFFER_BINDING_RANGE == m_BufferSize)
			{
				m_HasWrapped = true;
				m_CurrentOffset = 0;
			}
			else
				m_CurrentOffset += alignedStride;

			return { .ptr = (T*)((char*)m_BufferData + blockIndex), .offset = blockIndex, };
		}

		void Upload();

		void Destroy();  

		utils::Handle<gfx::DynamicBuffer> GetBuffer();
		utils::Handle<gfx::BindGroupLayout> GetLayout();

	private:
		utils::Handle<gfx::DynamicBuffer> m_Buffer; 
		utils::Handle<gfx::BindGroupLayout> m_Layout;

		void* m_BufferData; 

		bool m_HasWrapped = false;
		uint32_t m_BufferSize;
		uint32_t m_CurrentOffset;
		uint32_t m_Alignment;
	};
}

#endif // !__UNIFORMS_HPP__
