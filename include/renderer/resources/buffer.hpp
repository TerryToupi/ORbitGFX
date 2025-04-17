#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__ 

#include <enums.hpp>

namespace gfx
{
	class Buffer; 

	struct BufferDescriptor
	{ 
		gfx::BufferUsage usage = gfx::BufferUsage::UNIFORM;
		gfx::BufferUsageHint hint = gfx::BufferUsageHint::STATIC;
		uint32_t size = 0;
		const void* data = nullptr;
	};
}

#endif // !__BUFFER_HPP__
