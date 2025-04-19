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
		wgpu::Texture s_Texture;
		wgpu::TextureView s_TextureView;
	};
}

#endif