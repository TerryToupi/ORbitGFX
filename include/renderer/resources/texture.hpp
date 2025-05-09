#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__ 

#include <climits>

#include <span.hpp>
#include <enums.hpp>

namespace gfx
{
	class Texture; 

	struct TextureDescriptor
	{
		gfx::TextureFormat format = gfx::TextureFormat::RGBA8_UNORM;
		gfx::TextureUsage usage = gfx::TextureUsage::TEXTURE_BINDING | gfx::TextureUsage::COPY_DST;
		gfx::TextureType type = gfx::TextureType::D2;
		uint32_t width = 0;
		uint32_t height = 0;
		uint32_t depth = 1;
		uint32_t mipLevelCount = 1;
		uint32_t samplerCount = 1;
		
		utils::Span<uint8_t> initialData;
	};
}

#endif // !__TEXTURE__HPP__
