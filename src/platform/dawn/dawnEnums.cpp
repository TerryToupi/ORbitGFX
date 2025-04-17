#include <platform/dawn/dawnEnums.hpp>

namespace gfx
{
	wgpu::ShaderStage DecodeShaderType(const gfx::ShaderStage& type)
	{
		struct FlagMap {
			gfx::ShaderStage gfxFlag; 
			wgpu::ShaderStage wgpuFlag;
		};

		const FlagMap flagMaping[] =
		{
			{ gfx::ShaderStage::VERTEX, wgpu::ShaderStage::Vertex },
			{ gfx::ShaderStage::FRAGMENT, wgpu::ShaderStage::Fragment },
			{ gfx::ShaderStage::COMPUTE, wgpu::ShaderStage::Compute },
		};

		unsigned int typeValue = static_cast<unsigned int>(type); 

		wgpu::ShaderStage returnFlag = wgpu::ShaderStage::None;

		bool first = true;
		for (const auto& flag : flagMaping) 
		{ 
			if (typeValue & static_cast<unsigned int>(flag.gfxFlag)) 
			{   
				if (first)
					returnFlag = flag.wgpuFlag;
				else
					returnFlag |= flag.wgpuFlag; 
				
				first = false;
			}
		}

		return returnFlag;
	}

	wgpu::BufferBindingType DecodeBufferBindingType(const gfx::BufferBindingType& type)
	{
		struct FlagMap {
			gfx::BufferBindingType gfxFlag;
			wgpu::BufferBindingType wgpuFlag;
		};

		const FlagMap flagMaping[] =
		{
			{ gfx::BufferBindingType::UNIFORM, wgpu::BufferBindingType::Uniform },
			{ gfx::BufferBindingType::UNIFORM_DYNAMIC_OFFSET, wgpu::BufferBindingType::Uniform },
			{ gfx::BufferBindingType::STORAGE, wgpu::BufferBindingType::Storage },
			{ gfx::BufferBindingType::READ_ONLY_STORAGE, wgpu::BufferBindingType::ReadOnlyStorage },
			{ gfx::BufferBindingType::READ_WRITE_STORAGE, wgpu::BufferBindingType::Storage },
		};

		unsigned int typeValue = static_cast<unsigned int>(type);

		for (const auto& flag : flagMaping) 
		{ 
			if (typeValue & static_cast<unsigned int>(flag.gfxFlag)) 
			{
				return flag.wgpuFlag;
			}
		} 

		return wgpu::BufferBindingType::Undefined;
	}

	wgpu::CompareFunction DecodeCompareType(const gfx::Compare& type)
	{ 
		struct FlagMap {
			gfx::Compare gfxFlag;
			wgpu::CompareFunction wgpuFlag;
		};

		const FlagMap flagMaping[] =
		{
            { gfx::Compare::UNDEFINED, wgpu::CompareFunction::Undefined },
			{ gfx::Compare::NEVER, wgpu::CompareFunction::Never },
			{ gfx::Compare::LESS, wgpu::CompareFunction::Less },
			{ gfx::Compare::LESS_OR_EQUAL, wgpu::CompareFunction::LessEqual },
			{ gfx::Compare::GREATER, wgpu::CompareFunction::Greater },
			{ gfx::Compare::GREATER_OR_EQUAL, wgpu::CompareFunction::GreaterEqual },
			{ gfx::Compare::EQUAL, wgpu::CompareFunction::Equal },
			{ gfx::Compare::NOT_EQUAL, wgpu::CompareFunction::NotEqual },
			{ gfx::Compare::ALAWAYS, wgpu::CompareFunction::Always },
		};

		unsigned int typeValue = static_cast<unsigned int>(type);

		for (const auto& flag : flagMaping)
		{
			if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
			{
				return flag.wgpuFlag;
			}
		} 

		return wgpu::CompareFunction::Undefined;
	}

	wgpu::VertexFormat DecodeVertexFormatType(const gfx::VertexFormat& type)
	{ 
		struct FlagMap {
			gfx::VertexFormat gfxFlag;
			wgpu::VertexFormat wgpuFlag;
		};

		const FlagMap flagMaping[] =
		{ 
			{ gfx::VertexFormat::F16,	wgpu::VertexFormat::Float16 },
			{ gfx::VertexFormat::F16x2, wgpu::VertexFormat::Float16x2 },
			{ gfx::VertexFormat::F16x4, wgpu::VertexFormat::Float16x4 },
			{ gfx::VertexFormat::I16,	wgpu::VertexFormat::Sint16 },
			{ gfx::VertexFormat::I16x2, wgpu::VertexFormat::Sint16x2 },
			{ gfx::VertexFormat::I16x4, wgpu::VertexFormat::Sint16x4 },
			{ gfx::VertexFormat::U16,	wgpu::VertexFormat::Uint16 },
			{ gfx::VertexFormat::U16x2, wgpu::VertexFormat::Uint16x2 },
			{ gfx::VertexFormat::U16x4, wgpu::VertexFormat::Uint16x4 },

			{ gfx::VertexFormat::F32,	wgpu::VertexFormat::Float32 },
			{ gfx::VertexFormat::F32x2, wgpu::VertexFormat::Float32x2 },
			{ gfx::VertexFormat::F32x3, wgpu::VertexFormat::Float32x3 },
			{ gfx::VertexFormat::F32x4, wgpu::VertexFormat::Float32x4 },
			{ gfx::VertexFormat::I32,	wgpu::VertexFormat::Sint32 },
			{ gfx::VertexFormat::I32x2, wgpu::VertexFormat::Sint32x2 },
			{ gfx::VertexFormat::I32x3, wgpu::VertexFormat::Sint32x3 },
			{ gfx::VertexFormat::I32x4, wgpu::VertexFormat::Sint32x4 },
			{ gfx::VertexFormat::U32,	wgpu::VertexFormat::Uint32 },
			{ gfx::VertexFormat::U32x2, wgpu::VertexFormat::Uint32x2 },
			{ gfx::VertexFormat::U32x3, wgpu::VertexFormat::Uint32x3 },
			{ gfx::VertexFormat::U32x4, wgpu::VertexFormat::Uint32x4 },
		};

		unsigned int typeValue = static_cast<unsigned int>(type);

		for (const auto& flag : flagMaping)
		{
			if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
			{
				return flag.wgpuFlag;
			}
		}

		return wgpu::VertexFormat::Float32;
	}

	wgpu::FilterMode DecodeFilterModeType(const gfx::Filter& type)
	{
		struct FlagMap {
			gfx::Filter gfxFlag;
			wgpu::FilterMode wgpuFlag;
		};

		const FlagMap flagMaping[] =
		{
			{ gfx::Filter::NEAREST, wgpu::FilterMode::Nearest },
			{ gfx::Filter::LINEAR, wgpu::FilterMode::Linear },
			{ gfx::Filter::CUBIC, wgpu::FilterMode::Undefined },
		};

		unsigned int typeValue = static_cast<unsigned int>(type);

		for (const auto& flag : flagMaping)
		{
			if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
			{
				return flag.wgpuFlag;
			}
		}

		return wgpu::FilterMode::Undefined;
	}

	wgpu::AddressMode DecodeWarpType(const gfx::Wrap& type)
	{ 
		struct FlagMap {
			gfx::Wrap gfxFlag;
			wgpu::AddressMode wgpuFlag;
		};

		const FlagMap flagMaping[] =
		{
			{ gfx::Wrap::REPEAT, wgpu::AddressMode::Repeat },
			{ gfx::Wrap::REPEAT_MIRRORED, wgpu::AddressMode::MirrorRepeat },
			{ gfx::Wrap::CLAMP_TO_EDGE, wgpu::AddressMode::ClampToEdge },
			{ gfx::Wrap::CLAMP_TO_BORDER, wgpu::AddressMode::Undefined },
			{ gfx::Wrap::MIRROR_CLAMP_TO_EDGE, wgpu::AddressMode::Undefined },
		};

		unsigned int typeValue = static_cast<unsigned int>(type);

		for (const auto& flag : flagMaping)
		{
			if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
			{
				return flag.wgpuFlag;
			}
		}

		return wgpu::AddressMode::Undefined;
	}

	wgpu::PrimitiveTopology DecodeTopologyType(const gfx::Topology& type)
	{
		struct FlagMap {
			gfx::Topology gfxFlag;
			wgpu::PrimitiveTopology wgpuFlag;
		};

		const FlagMap flagMaping[] =
		{
			{ gfx::Topology::POINT_LIST, wgpu::PrimitiveTopology::PointList },
			{ gfx::Topology::LINE_LIST, wgpu::PrimitiveTopology::LineList },
			{ gfx::Topology::LINE_STRIP, wgpu::PrimitiveTopology::LineStrip },
			{ gfx::Topology::TRIANGLE_LIST, wgpu::PrimitiveTopology::TriangleList },
			{ gfx::Topology::TRIANGLE_STRIP, wgpu::PrimitiveTopology::TriangleStrip },
			{ gfx::Topology::TRIANGLE_FAN, wgpu::PrimitiveTopology::Undefined },
			{ gfx::Topology::PATCH_LIST, wgpu::PrimitiveTopology::Undefined },
		}; 

		unsigned int typeValue = static_cast<unsigned int>(type);

		for (const auto& flag : flagMaping)
		{
			if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
			{
				return flag.wgpuFlag;
			}
		}

		return wgpu::PrimitiveTopology::Undefined;
	}

	wgpu::CullMode DecodeCullModeType(const gfx::CullMode& type)
	{
		struct FlagMap {
			gfx::CullMode gfxFlag;
			wgpu::CullMode wgpuFlag;
		};

		const FlagMap flagMaping[] =
		{
			{ gfx::CullMode::NONE, wgpu::CullMode::None },
			{ gfx::CullMode::FRONT_FACE, wgpu::CullMode::Front },
			{ gfx::CullMode::BACK_FACE, wgpu::CullMode::Back },
			{ gfx::CullMode::FRONT_AND_BACK, wgpu::CullMode::Undefined },
		};

		unsigned int typeValue = static_cast<unsigned int>(type);

		for (const auto& flag : flagMaping)
		{
			if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
			{
				return flag.wgpuFlag;
			}
		}

		return wgpu::CullMode::Undefined;
	}

	wgpu::TextureFormat DecodeTextureFormatType(const gfx::TextureFormat& type)
	{
		struct FlagMap {
			gfx::TextureFormat gfxFlag;
			wgpu::TextureFormat wgpuFlag;
		};

		const FlagMap flagMaping[] =
		{
			{ gfx::TextureFormat::RGBA32_FLOAT, wgpu::TextureFormat::RGBA32Float },
			{ gfx::TextureFormat::D24_STENCIL_8, wgpu::TextureFormat::Depth24PlusStencil8 },
			{ gfx::TextureFormat::D32_FLOAT, wgpu::TextureFormat::Depth32Float },
			{ gfx::TextureFormat::D32_FLOAT_STENCIL_8, wgpu::TextureFormat::Depth32FloatStencil8 },
			{ gfx::TextureFormat::D24_PLUS, wgpu::TextureFormat::Depth24Plus },
			{ gfx::TextureFormat::D16_UNORM, wgpu::TextureFormat::Depth16Unorm },
			{ gfx::TextureFormat::RGBA16_FLOAT, wgpu::TextureFormat::RGBA16Float },
			{ gfx::TextureFormat::RGBA8_UNORM, wgpu::TextureFormat::RGBA8Unorm },
			{ gfx::TextureFormat::RG16_FLOAT, wgpu::TextureFormat::RG16Float },
			{ gfx::TextureFormat::RG32_FLOAT, wgpu::TextureFormat::RG32Float },
			{ gfx::TextureFormat::R32_FLOAT, wgpu::TextureFormat::R32Float },
			{ gfx::TextureFormat::R16_FLOAT, wgpu::TextureFormat::R16Float },
			{ gfx::TextureFormat::RGBA8_UNORM_SRGB, wgpu::TextureFormat::RGBA8UnormSrgb },
			{ gfx::TextureFormat::BGRA8_UNORM_SRGB, wgpu::TextureFormat::BGRA8UnormSrgb }, 
			{ gfx::TextureFormat::RGBA8_LINEAR, wgpu::TextureFormat::RGBA8Sint }, 
			{ gfx::TextureFormat::BGRA8_UNORM, wgpu::TextureFormat::BGRA8Unorm }, 
		};

		unsigned int typeValue = static_cast<unsigned int>(type);

		for (const auto& flag : flagMaping)
		{
			if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
			{
				return flag.wgpuFlag;
			}
		}

		return wgpu::TextureFormat::Undefined;
	}

	gfx::TextureFormat EncodeTextureFormatType(const wgpu::TextureFormat& type)
	{
		struct FlagMap {
			wgpu::TextureFormat wgpuFlag;
			gfx::TextureFormat gfxFlag;
		};

		const FlagMap flagMapping[] =
		{
			{ wgpu::TextureFormat::RGBA32Float, gfx::TextureFormat::RGBA32_FLOAT },
			{ wgpu::TextureFormat::Depth24PlusStencil8, gfx::TextureFormat::D24_STENCIL_8 },
			{ wgpu::TextureFormat::Depth32Float, gfx::TextureFormat::D32_FLOAT },
			{ wgpu::TextureFormat::Depth32FloatStencil8, gfx::TextureFormat::D32_FLOAT_STENCIL_8 },
			{ wgpu::TextureFormat::Depth24Plus, gfx::TextureFormat::D24_PLUS },
			{ wgpu::TextureFormat::Depth16Unorm, gfx::TextureFormat::D16_UNORM },
			{ wgpu::TextureFormat::RGBA16Float, gfx::TextureFormat::RGBA16_FLOAT },
			{ wgpu::TextureFormat::RGBA8Unorm, gfx::TextureFormat::RGBA8_UNORM },
			{ wgpu::TextureFormat::RG16Float, gfx::TextureFormat::RG16_FLOAT },
			{ wgpu::TextureFormat::RG32Float, gfx::TextureFormat::RG32_FLOAT },
			{ wgpu::TextureFormat::R32Float, gfx::TextureFormat::R32_FLOAT },
			{ wgpu::TextureFormat::R16Float, gfx::TextureFormat::R16_FLOAT },
			{ wgpu::TextureFormat::RGBA8UnormSrgb, gfx::TextureFormat::RGBA8_UNORM_SRGB },
			{ wgpu::TextureFormat::BGRA8UnormSrgb, gfx::TextureFormat::BGRA8_UNORM_SRGB },
			{ wgpu::TextureFormat::RGBA8Sint, gfx::TextureFormat::RGBA8_LINEAR },
			{ wgpu::TextureFormat::BGRA8Unorm, gfx::TextureFormat::BGRA8_UNORM },
		};

		unsigned int typeValue = static_cast<unsigned int>(type);

		for (const auto& flag : flagMapping)
		{
			if (typeValue == static_cast<unsigned int>(flag.wgpuFlag))
			{
				return flag.gfxFlag;
			}
		}

		return gfx::TextureFormat::UNDEFINED;
	}

	wgpu::BufferUsage DecodeBufferUsageType(const gfx::BufferUsage& type)
	{
		struct FlagMap {
			gfx::BufferUsage gfxFlag;
			wgpu::BufferUsage wgpuFlag;
		};

		const FlagMap flagMaping[] =
		{
			{ gfx::BufferUsage::MAP_READ, wgpu::BufferUsage::MapRead },
			{ gfx::BufferUsage::MAP_WRITE, wgpu::BufferUsage::MapWrite },
			{ gfx::BufferUsage::COPY_SRC, wgpu::BufferUsage::CopySrc },
			{ gfx::BufferUsage::COPY_DST, wgpu::BufferUsage::CopyDst },
			{ gfx::BufferUsage::INDEX, wgpu::BufferUsage::Index },
			{ gfx::BufferUsage::VERTEX, wgpu::BufferUsage::Vertex },
			{ gfx::BufferUsage::UNIFORM, wgpu::BufferUsage::Uniform },
			{ gfx::BufferUsage::STORAGE, wgpu::BufferUsage::Storage },
			{ gfx::BufferUsage::INDIRECT, wgpu::BufferUsage::Indirect },
			{ gfx::BufferUsage::QUERY_RESOLVE, wgpu::BufferUsage::QueryResolve },
		};

		unsigned int typeValue = static_cast<unsigned int>(type);

		wgpu::BufferUsage returnFlag = wgpu::BufferUsage::None;

		bool first = true;
		for (const auto& flag : flagMaping)
		{
			if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
			{
				if (first)
					returnFlag = flag.wgpuFlag;
				else
					returnFlag |= flag.wgpuFlag;

				first = false;
			}
		}

		return returnFlag;
	}

	wgpu::TextureDimension DecodeTextureType(const gfx::TextureType& type)
	{
		struct FlagMap {
			gfx::TextureType gfxFlag;
			wgpu::TextureDimension wgpuFlag;
		};

		const FlagMap flagMaping[] =
		{
			{ gfx::TextureType::D1, wgpu::TextureDimension::e1D },
			{ gfx::TextureType::D2, wgpu::TextureDimension::e2D },
			{ gfx::TextureType::D3, wgpu::TextureDimension::e3D },
		};

		unsigned int typeValue = static_cast<unsigned int>(type);

		for (const auto& flag : flagMaping)
		{
			if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
			{
				return flag.wgpuFlag;
			}
		}

		return wgpu::TextureDimension::Undefined;
	}

	wgpu::TextureViewDimension DecodeTextureDimentionType(const gfx::TextureDimention& type)
	{
		struct FlagMap {
			gfx::TextureDimention gfxFlag;
			wgpu::TextureViewDimension wgpuFlag;
		};

		const FlagMap flagMaping[] =
		{
			{ gfx::TextureDimention::D1,			wgpu::TextureViewDimension::e1D },
			{ gfx::TextureDimention::D2,			wgpu::TextureViewDimension::e2D },
			{ gfx::TextureDimention::D2_ARRAY,		wgpu::TextureViewDimension::e2DArray },
			{ gfx::TextureDimention::CUBE,			wgpu::TextureViewDimension::Cube },
			{ gfx::TextureDimention::CUBE_ARRAY,	wgpu::TextureViewDimension::CubeArray },
			{ gfx::TextureDimention::D3,			wgpu::TextureViewDimension::e3D },
		};

		unsigned int typeValue = static_cast<unsigned int>(type);

		for (const auto& flag : flagMaping)
		{
			if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
			{
				return flag.wgpuFlag;
			}
		}

		return wgpu::TextureViewDimension::Undefined;
	}

	wgpu::TextureAspect DecodeTextureAspectType(const gfx::TextureAspect& type)
	{
		struct FlagMap {
			gfx::TextureAspect gfxFlag;
			wgpu::TextureAspect wgpuFlag;
		};

		const FlagMap flagMaping[] =
		{
			{ gfx::TextureAspect::NONE, wgpu::TextureAspect::Undefined },
			{ gfx::TextureAspect::ALL, wgpu::TextureAspect::All },
			{ gfx::TextureAspect::STENCIL_ONLY, wgpu::TextureAspect::StencilOnly },
			{ gfx::TextureAspect::DEPTH_ONLY, wgpu::TextureAspect::DepthOnly },
			{ gfx::TextureAspect::PLANE_0_ONLY, wgpu::TextureAspect::Plane0Only },
			{ gfx::TextureAspect::PLANE_1_ONLY, wgpu::TextureAspect::Plane1Only },
			{ gfx::TextureAspect::PLANE_2_ONLY, wgpu::TextureAspect::Plane2Only },
		};

		unsigned int typeValue = static_cast<unsigned int>(type);

		for (const auto& flag : flagMaping)
		{
			if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
			{
				return flag.wgpuFlag;
			}
		}

		return wgpu::TextureAspect::Undefined;
	}

	wgpu::TextureUsage DecodeTextureUsageType(const gfx::TextureUsage& type)
	{
		struct FlagMap {
			gfx::TextureUsage gfxFlag;
			wgpu::TextureUsage wgpuFlag;
		};

		const FlagMap flagMaping[] =
		{
			{ gfx::TextureUsage::COPY_DST, wgpu::TextureUsage::CopySrc },
			{ gfx::TextureUsage::COPY_DST, wgpu::TextureUsage::CopyDst },
			{ gfx::TextureUsage::TEXTURE_BINDING, wgpu::TextureUsage::TextureBinding },
			{ gfx::TextureUsage::STORAGE_BINDING, wgpu::TextureUsage::StorageBinding },
			{ gfx::TextureUsage::RENDER_ATTACHMENT, wgpu::TextureUsage::RenderAttachment },
			{ gfx::TextureUsage::TRANSIENT, wgpu::TextureUsage::TransientAttachment },
		};

		unsigned int typeValue = static_cast<unsigned int>(type);

		wgpu::TextureUsage returnFlag = wgpu::TextureUsage::None;

		bool first = true;
		for (const auto& flag : flagMaping)
		{
			if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
			{
				if (first)
					returnFlag = flag.wgpuFlag;
				else
					returnFlag |= flag.wgpuFlag;

				first = false;
			}
		}

		return returnFlag;
	}

	wgpu::BlendFactor DecodeBlendFactorType(const gfx::BlendFactor& type)
	{
		struct FlagMap {
			gfx::BlendFactor gfxFlag;
			wgpu::BlendFactor wgpuFlag;
		};

		const FlagMap flagMaping[] =
		{
			{ gfx::BlendFactor::SRC_ALPHA, wgpu::BlendFactor::SrcAlpha },
			{ gfx::BlendFactor::ONE_MINUS_SRC_ALPHA, wgpu::BlendFactor::OneMinusSrcAlpha },
			{ gfx::BlendFactor::ONE, wgpu::BlendFactor::One },
			{ gfx::BlendFactor::ZERO, wgpu::BlendFactor::Zero },
		};

		unsigned int typeValue = static_cast<unsigned int>(type);

		for (const auto& flag : flagMaping)
		{
			if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
			{
				return flag.wgpuFlag;
			}
		}

		return wgpu::BlendFactor::Undefined;
	}

	wgpu::BlendOperation DecodeBlendOperationType(const gfx::BlendOperation& type)
	{
		struct FlagMap {
			gfx::BlendOperation gfxFlag;
			wgpu::BlendOperation wgpuFlag;
		};

		const FlagMap flagMaping[] =
		{
			{ gfx::BlendOperation::ADD, wgpu::BlendOperation::Add },
			{ gfx::BlendOperation::SUB, wgpu::BlendOperation::Subtract },
			{ gfx::BlendOperation::MIN, wgpu::BlendOperation::Min },
			{ gfx::BlendOperation::MAX, wgpu::BlendOperation::Max },
		};

		unsigned int typeValue = static_cast<unsigned int>(type);

		for (const auto& flag : flagMaping)
		{
			if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
			{
				return flag.wgpuFlag;
			}
		}

		return wgpu::BlendOperation::Undefined;
	}

	wgpu::StoreOp DecodeStoreOperationType(const gfx::StoreOperation& type)
	{
		struct FlagMap {
			gfx::StoreOperation gfxFlag;
			wgpu::StoreOp wgpuFlag;
		};

		const FlagMap flagMaping[] =
		{
			{ gfx::StoreOperation::STORE, wgpu::StoreOp::Store },
			{ gfx::StoreOperation::DISCARD, wgpu::StoreOp::Discard },
		};

		unsigned int typeValue = static_cast<unsigned int>(type);

		for (const auto& flag : flagMaping)
		{
			if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
			{
				return flag.wgpuFlag;
			}
		}

		return wgpu::StoreOp::Undefined;
	}

	wgpu::LoadOp DecodeLoadOperationType(const gfx::LoadOperation& type)
	{
		struct FlagMap {
			gfx::LoadOperation gfxFlag;
			wgpu::LoadOp wgpuFlag;
		};

		const FlagMap flagMaping[] =
		{
			{ gfx::LoadOperation::CLEAR, wgpu::LoadOp::Clear },
			{ gfx::LoadOperation::LOAD, wgpu::LoadOp::Load },
		};

		unsigned int typeValue = static_cast<unsigned int>(type);

		for (const auto& flag : flagMaping)
		{
			if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
			{
				return flag.wgpuFlag;
			}
		}

		return wgpu::LoadOp::Undefined;
	}

	unsigned int DecodeTextureFormatToAlignmentType(const gfx::TextureFormat& type)
	{
		struct FlagMap {
			gfx::TextureFormat gfxFlag;
			unsigned int wgpuFlag;
		};

		const FlagMap flagMaping[] =
		{
			{ gfx::TextureFormat::RGBA32_FLOAT, 16 },
			{ gfx::TextureFormat::D24_STENCIL_8, 4 },
			{ gfx::TextureFormat::D32_FLOAT, 4 },
			{ gfx::TextureFormat::D32_FLOAT_STENCIL_8, 5 },
			{ gfx::TextureFormat::D24_PLUS, 3 },
			{ gfx::TextureFormat::D16_UNORM, 2 },
			{ gfx::TextureFormat::RGBA16_FLOAT, 8 },
			{ gfx::TextureFormat::RGBA8_UNORM, 4 },
			{ gfx::TextureFormat::RG16_FLOAT, 4 },
			{ gfx::TextureFormat::RG32_FLOAT, 8 },
			{ gfx::TextureFormat::R32_FLOAT, 4 },
			{ gfx::TextureFormat::R16_FLOAT, 2 },
			{ gfx::TextureFormat::RGBA8_UNORM_SRGB, 4 },
			{ gfx::TextureFormat::BGRA8_UNORM_SRGB, 4 },
			{ gfx::TextureFormat::RGBA8_LINEAR, 4 },
			{ gfx::TextureFormat::BGRA8_UNORM, 4 },
		};

		unsigned int typeValue = static_cast<unsigned int>(type);

		for (const auto& flag : flagMaping)
		{
			if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
			{
				return flag.wgpuFlag;
			}
		}

		return 0;
	}
}
