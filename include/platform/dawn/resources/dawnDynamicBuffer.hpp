#ifndef __DAWN_DYNAMIC_BUFFER_HPP__
#define __DAWN_DYNAMIC_BUFFER_HPP__

#include <resources/dynamicBuffer.hpp>
#include <dawn/dawnEnums.hpp>

namespace gfx
{
	class DawnDynamicBuffer
	{
	public: 
	public:
		DawnDynamicBuffer();
		DawnDynamicBuffer(const DynamicBufferDescriptor& desc);
		void Destroy();

	public:
		wgpu::Buffer s_Buffer;
	};
}

#endif // !__DAWN_DYNAMIC_BUFFER_HPP__
