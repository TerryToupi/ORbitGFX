#ifndef __DYNAMIC_BUFFER_HPP__
#define __DYNAMIC_BUFFER_HPP__

#include <enums.hpp>
#include <handle.hpp>
#include <resources/bindGroupLayout.hpp>

namespace gfx
{
	class DynamicBuffer;

	struct DynamicBufferDescriptor
	{
		gfx::BufferUsage usage = gfx::BufferUsage::UNIFORM;
		uint32_t bufferSize = 0;
		uint32_t bufferRange = 0;
		utils::Handle<BindGroupLayout> bindGroupLayout;
	};
}

#endif // !__DYNAMIC_BUFFER_HPP__
