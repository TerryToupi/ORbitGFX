#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__ 

#include <span.hpp>
#include <enums.hpp>

namespace gfx
{
	class Texture; 

	struct TextureViewDescriptor
	{
		gfx::TextureFormat format = gfx::TextureFormat::RGBA8_UNORM;
		gfx::TextureDimention dimention = gfx::TextureDimention::D2;
		gfx::TextureAspect aspect = gfx::TextureAspect::ALL;
		gfx::TextureUsage usage = gfx::TextureUsage::TEXTURE_BINDING | gfx::TextureUsage::COPY_DST;
		uint32_t baseMipLevel = 0;
		uint32_t mipLevelCount = UINT_MAX;
		uint32_t baseArrayLayer = 0;
		uint32_t arrayLayerCount = UINT_MAX;
	}; 

	struct TextureUplaodDescriptor
	{ 
		bool upload = false;
		uint64_t uploadSize = 0;
		const void* uploadData = nullptr;
	};

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

		TextureViewDescriptor view = {};
		TextureUplaodDescriptor uploadDesc = {};
	};
}

#endif // !__TEXTURE__HPP__
