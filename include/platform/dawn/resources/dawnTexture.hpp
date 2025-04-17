#ifndef __DAWN_TEXTURE_HPP__ 
#define __DAWN_TEXTURE_HPP__ 

#include <vector>

#include <dawn/dawnCommon.hpp>
#include <dawn/dawnEnums.hpp>

#include <resources/texture.hpp>

namespace gfx
{
	class DawnTexture
	{ 
	public:
		DawnTexture();
		DawnTexture(const TextureDescriptor& desc);
		void Destroy();

	public:
		uint8_t s_TextureViewCount = 0;
		wgpu::Texture s_Texture;
		wgpu::TextureView s_TextureViews[kMaxTextureViews];
	};
}

#endif