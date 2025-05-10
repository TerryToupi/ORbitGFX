#ifndef __DYNAMIC_BUFFER_HPP__
#define __DYNAMIC_BUFFER_HPP__

#include <enums.hpp>

namespace gfx
{
	class DynamicBuffer;

	struct DynamicBufferDescriptor
	{
		gfx::BufferUsage usage = gfx::BufferUsage::UNIFORM;
	};
}

#endif // !__DYNAMIC_BUFFER_HPP__
