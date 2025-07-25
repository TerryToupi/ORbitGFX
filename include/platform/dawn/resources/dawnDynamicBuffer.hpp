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
		void Resize();
		void Destroy();

	public:
		DynamicBufferDescriptor s_Desc;

		wgpu::Buffer s_Buffer;
		wgpu::BindGroup s_BindGroup;
	};
}

#endif // !__DAWN_DYNAMIC_BUFFER_HPP__
