#include <dawn/dawnEnums.hpp>
#include <dawn/dawnDevice.hpp>
#include <dawn/resources/dawnTexture.hpp>
#include <dawn/dawnDevice.hpp>

namespace gfx
{
	DawnTexture::DawnTexture()
		: s_Texture(nullptr), s_TextureView(nullptr)
	{
	}

	DawnTexture::DawnTexture(const TextureDescriptor& desc)
	{
		DawnDevice* deviceInstance = (DawnDevice*)Device::instance;
		wgpu::Device device = deviceInstance->GetDawnDevice();
	
		wgpu::TextureDescriptor textureDesc =
		{
			.usage = gfx::DecodeTextureUsageType(desc.usage),
			.dimension = gfx::DecodeTextureType(desc.type),
			.size = { desc.width, desc.height, desc.depth },
			.format = gfx::DecodeTextureFormatType(desc.format),
			.mipLevelCount = desc.mipLevelCount,
			.sampleCount = desc.samplerCount,
		};

		s_Texture = device.CreateTexture(&textureDesc);
		
		wgpu::TextureViewDescriptor textureViewDesc =
		{
			.format = gfx::DecodeTextureFormatType(desc.view.format),
			.dimension = gfx::DecodeTextureDimentionType(desc.view.dimention),
			.baseMipLevel = desc.view.baseMipLevel,
			.mipLevelCount = desc.view.mipLevelCount,
			.baseArrayLayer = desc.view.baseArrayLayer,
			.arrayLayerCount = desc.view.arrayLayerCount,
			.aspect = gfx::DecodeTextureAspectType(desc.view.aspect),
			.usage = gfx::DecodeTextureUsageType(desc.view.usage)
		};
		s_TextureView = s_Texture.CreateView(&textureViewDesc);

		if (desc.uploadDesc.upload)
		{
            DawnDevice* deviceInstance = (DawnDevice*)Device::instance;
            wgpu::Device device = deviceInstance->GetDawnDevice();

            unsigned int alignment = DecodeTextureFormatToAlignmentType(desc.format);

            wgpu::TexelCopyBufferLayout imageCpyBuffer =
            {
				 .offset = 0, 
				 .bytesPerRow = desc.width * alignment, 
				 .rowsPerImage = desc.height,
            };

            wgpu::TexelCopyTextureInfo imageCpyTexture =
            {
                .texture = s_Texture,
                .mipLevel = 0,
                .origin = { 0, 0, 0 },
            };
            
            wgpu::Extent3D extent = { desc.width, desc.height, desc.depth };

			device.GetQueue().WriteTexture(
				&imageCpyTexture, 
				desc.uploadDesc.uploadData, 
				desc.uploadDesc.uploadSize, 
				&imageCpyBuffer, 
				&extent
			);
		}
	}

	void DawnTexture::Destroy()
	{
		s_Texture.Destroy();

		s_Texture = nullptr;
		s_TextureView = nullptr;
	}
}
