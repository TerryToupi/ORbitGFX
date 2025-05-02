#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__ 

#include <enums.hpp>
#include <span.hpp>

namespace gfx
{
	class Buffer; 

	struct BufferDescriptor
	{ 
		gfx::BufferUsage usage = gfx::BufferUsage::UNIFORM;
		gfx::BufferUsageHint hint = gfx::BufferUsageHint::STATIC;
		uint32_t byteSize = 0;
		utils::Span<uint8_t> initialData;
	};
}

#endif // !__BUFFER_HPP__
