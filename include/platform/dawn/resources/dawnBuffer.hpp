#ifndef __DAWN_BUFFER_HPP__
#define __DAWN_BUFFER_HPP__ 

#include <dawn/dawnCommon.hpp>
#include <dawn/dawnEnums.hpp>

#include <resources/buffer.hpp>

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
