#ifndef __DAWN_ENUMS_HPP__
#define __DAWN_ENUMS_HPP__ 

#include <dawn/dawnCommon.hpp> 

#include <enums.hpp>

namespace gfx
{
	wgpu::ShaderStage DecodeShaderType(const gfx::ShaderStage& type); 
	
	wgpu::BufferBindingType DecodeBufferBindingType(const gfx::BufferBindingType& type);

	wgpu::CompareFunction DecodeCompareType(const gfx::Compare& type); 

	wgpu::VertexFormat DecodeVertexFormatType(const gfx::VertexFormat& type);

	wgpu::FilterMode DecodeFilterModeType(const gfx::Filter& type); 

	wgpu::AddressMode DecodeWarpType(const gfx::Wrap& type); 

	wgpu::PrimitiveTopology DecodeTopologyType(const gfx::Topology& type); 

	wgpu::CullMode DecodeCullModeType(const gfx::CullMode& type); 

	wgpu::TextureFormat DecodeTextureFormatType(const gfx::TextureFormat& type);

	gfx::TextureFormat EncodeTextureFormatType(const wgpu::TextureFormat& type);

	wgpu::TextureSampleType DecodeTextureSampleType(const gfx::TextureSampleType& type);

	wgpu::BufferUsage DecodeBufferUsageType(const gfx::BufferUsage& type);
	
	wgpu::TextureDimension DecodeTextureType(const gfx::TextureType& type); 

	wgpu::TextureViewDimension DecodeTextureDimentionType(const gfx::TextureDimention& type);

	wgpu::TextureAspect DecodeTextureAspectType(const gfx::TextureAspect& type);

	wgpu::TextureUsage DecodeTextureUsageType(const gfx::TextureUsage& type); 

	wgpu::BlendFactor DecodeBlendFactorType(const gfx::BlendFactor& type);

	wgpu::BlendOperation DecodeBlendOperationType(const gfx::BlendOperation& type);

	wgpu::StoreOp DecodeStoreOperationType(const gfx::StoreOperation& type);

	wgpu::LoadOp DecodeLoadOperationType(const gfx::LoadOperation& type);

	unsigned int DecodeTextureFormatToAlignmentType(const gfx::TextureFormat& type);
}

#endif // !__DAWN_ENUMS_HPP__
