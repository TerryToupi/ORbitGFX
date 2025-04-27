#ifndef __DAWN_ENUMS_HPP__
#define __DAWN_ENUMS_HPP__ 

#include <dawn/dawnCommon.hpp> 

#include <enums.hpp>

namespace gfx
{
	inline wgpu::ShaderStage DecodeShaderType(const gfx::ShaderStage& type); 
	
	inline wgpu::BufferBindingType DecodeBufferBindingType(const gfx::BufferBindingType& type);

	inline wgpu::CompareFunction DecodeCompareType(const gfx::Compare& type); 

	inline wgpu::VertexFormat DecodeVertexFormatType(const gfx::VertexFormat& type);

	inline wgpu::FilterMode DecodeFilterModeType(const gfx::Filter& type); 

	inline wgpu::AddressMode DecodeWarpType(const gfx::Wrap& type); 

	inline wgpu::PrimitiveTopology DecodeTopologyType(const gfx::Topology& type); 

	inline wgpu::CullMode DecodeCullModeType(const gfx::CullMode& type); 

	inline wgpu::TextureFormat DecodeTextureFormatType(const gfx::TextureFormat& type);

	inline gfx::TextureFormat EncodeTextureFormatType(const wgpu::TextureFormat& type);

	inline wgpu::TextureSampleType DecodeTextureSampleType(const gfx::TextureSampleType& type);

	inline wgpu::BufferUsage DecodeBufferUsageType(const gfx::BufferUsage& type);
	
	inline wgpu::TextureDimension DecodeTextureType(const gfx::TextureType& type); 

	inline wgpu::TextureViewDimension DecodeTextureDimentionType(const gfx::TextureDimention& type);

	inline wgpu::TextureAspect DecodeTextureAspectType(const gfx::TextureAspect& type);

	inline wgpu::TextureUsage DecodeTextureUsageType(const gfx::TextureUsage& type); 

	inline wgpu::BlendFactor DecodeBlendFactorType(const gfx::BlendFactor& type);

	inline wgpu::BlendOperation DecodeBlendOperationType(const gfx::BlendOperation& type);

	inline wgpu::StoreOp DecodeStoreOperationType(const gfx::StoreOperation& type);

	inline wgpu::LoadOp DecodeLoadOperationType(const gfx::LoadOperation& type);

	inline unsigned int DecodeTextureFormatToAlignmentType(const gfx::TextureFormat& type);
}

#endif // !__DAWN_ENUMS_HPP__
