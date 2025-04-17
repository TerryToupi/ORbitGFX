#ifndef __DAWN_BUFFER_HPP__
#define __DAWN_BUFFER_HPP__ 

#include <platform/dawn/dawnCommon.hpp>
#include <platform/dawn/dawnEnums.hpp>
#include <renderer/resources/buffer.hpp>

namespace gfx
{
	class DawnBuffer
	{
	public:
		DawnBuffer();
		DawnBuffer(const BufferDescriptor& desc);
		void Destroy();

	public:
		wgpu::Buffer s_Buffer;
	};
}

#endif // !__DAWN_BUFFER_HPP__
