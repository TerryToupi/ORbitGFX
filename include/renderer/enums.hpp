#ifndef __ENUMS_HPP__
#define __ENUMS_HPP__

#include <cstdint>

#define UINT_BIT_SHIFT(x) (1u << x)

namespace gfx
{ 
	enum class ShaderStage : unsigned int
	{
		VERTEX = UINT_BIT_SHIFT(0),
		FRAGMENT = UINT_BIT_SHIFT(1),
		COMPUTE = UINT_BIT_SHIFT(2),
	};

	enum class ShaderPipelineType : unsigned int
	{
		GRAPHICS = UINT_BIT_SHIFT(0),
		COMPUTE = UINT_BIT_SHIFT(1)
	};

	enum class BufferBindingType : unsigned int
	{
		UNIFORM = UINT_BIT_SHIFT(0),
		UNIFORM_DYNAMIC_OFFSET = UINT_BIT_SHIFT(1),
		STORAGE = UINT_BIT_SHIFT(2),
		READ_ONLY_STORAGE = UINT_BIT_SHIFT(3),
		READ_WRITE_STORAGE = UINT_BIT_SHIFT(4),
	};

	enum class Compare : unsigned int
	{
		NEVER = UINT_BIT_SHIFT(0),
		LESS = UINT_BIT_SHIFT(1),
		LESS_OR_EQUAL = UINT_BIT_SHIFT(2),
		GREATER = UINT_BIT_SHIFT(3),
		GREATER_OR_EQUAL = UINT_BIT_SHIFT(4),
		EQUAL = UINT_BIT_SHIFT(5),
		NOT_EQUAL = UINT_BIT_SHIFT(6),
		ALAWAYS = UINT_BIT_SHIFT(7),
        UNDEFINED = UINT_BIT_SHIFT(8)
	};

	enum class VertexFormat : unsigned int
	{ 
		F16 = UINT_BIT_SHIFT(0),
		F16x2 = UINT_BIT_SHIFT(1),
		F16x4 = UINT_BIT_SHIFT(2),
		I16 = UINT_BIT_SHIFT(3),
		I16x2 = UINT_BIT_SHIFT(4),
		I16x4 = UINT_BIT_SHIFT(5),
		U16 = UINT_BIT_SHIFT(6),
		U16x2 = UINT_BIT_SHIFT(7),
		U16x4 = UINT_BIT_SHIFT(8), 

		F32 = UINT_BIT_SHIFT(9),
		F32x2 = UINT_BIT_SHIFT(10),
		F32x3 = UINT_BIT_SHIFT(11),
		F32x4 = UINT_BIT_SHIFT(12),
		I32 = UINT_BIT_SHIFT(13),
		I32x2 = UINT_BIT_SHIFT(14),
		I32x3 = UINT_BIT_SHIFT(15),
		I32x4 = UINT_BIT_SHIFT(16),
		U32 = UINT_BIT_SHIFT(17),
		U32x2 = UINT_BIT_SHIFT(18),
		U32x3 = UINT_BIT_SHIFT(19),
		U32x4 = UINT_BIT_SHIFT(20), 

		UNORM8 = UINT_BIT_SHIFT(21),
		UNORM8x2 = UINT_BIT_SHIFT(22),
		UNORM8x4 = UINT_BIT_SHIFT(23)
	};

	enum class Filter : unsigned int
	{
		NEAREST = UINT_BIT_SHIFT(0),
		LINEAR = UINT_BIT_SHIFT(1),
		CUBIC = UINT_BIT_SHIFT(2),
	};

	enum class Wrap : unsigned int
	{
		REPEAT = UINT_BIT_SHIFT(0),
		REPEAT_MIRRORED = UINT_BIT_SHIFT(1),
		CLAMP_TO_EDGE = UINT_BIT_SHIFT(2),
		CLAMP_TO_BORDER = UINT_BIT_SHIFT(3),
		MIRROR_CLAMP_TO_EDGE = UINT_BIT_SHIFT(4),
	};

	enum class Topology : unsigned int
	{
		POINT_LIST = UINT_BIT_SHIFT(0),
		LINE_LIST = UINT_BIT_SHIFT(1),
		LINE_STRIP = UINT_BIT_SHIFT(2),
		TRIANGLE_LIST = UINT_BIT_SHIFT(3),
		TRIANGLE_STRIP = UINT_BIT_SHIFT(4),
		TRIANGLE_FAN = UINT_BIT_SHIFT(5),
		PATCH_LIST = UINT_BIT_SHIFT(6),
	};

	enum class PolygonMode : unsigned int
	{
		FILL = UINT_BIT_SHIFT(0),
		LINE = UINT_BIT_SHIFT(1),
		POINT = UINT_BIT_SHIFT(2),
	};

	enum class CullMode : unsigned int
	{
		NONE = UINT_BIT_SHIFT(0),
		FRONT_FACE = UINT_BIT_SHIFT(1),
		BACK_FACE = UINT_BIT_SHIFT(2),
		FRONT_AND_BACK = UINT_BIT_SHIFT(3),
	};

	enum class TextureFormat : unsigned int
	{
		RGBA32_FLOAT = UINT_BIT_SHIFT(0),
		D32_FLOAT = UINT_BIT_SHIFT(1),
		RGBA16_FLOAT = UINT_BIT_SHIFT(2),
		RGBA8_UNORM = UINT_BIT_SHIFT(3),
		RG16_FLOAT = UINT_BIT_SHIFT(4),
		R32_FLOAT = UINT_BIT_SHIFT(5),
		RGBA8_UNORM_SRGB = UINT_BIT_SHIFT(6),
		RGBA8_LINEAR = UINT_BIT_SHIFT(7),
		BGRA8_UNORM = UINT_BIT_SHIFT(8),
		BGRA8_UNORM_SRGB = UINT_BIT_SHIFT(9), 
		RG32_FLOAT = UINT_BIT_SHIFT(10),
		R16_FLOAT = UINT_BIT_SHIFT(11),
		D24_STENCIL_8 = UINT_BIT_SHIFT(12),
		D32_FLOAT_STENCIL_8 = UINT_BIT_SHIFT(13),
		D24_PLUS = UINT_BIT_SHIFT(14),
		D16_UNORM = UINT_BIT_SHIFT(15),
		UNDEFINED = UINT_BIT_SHIFT(16)
	};

	enum class TextureSampleType : unsigned int
	{
		UNDEFINED = UINT_BIT_SHIFT(0),
		FLOAT = UINT_BIT_SHIFT(1),
		FLOAT_NO_FILTER = UINT_BIT_SHIFT(2),
		DEPTH = UINT_BIT_SHIFT(3),
		SINT = UINT_BIT_SHIFT(4),
		UINT = UINT_BIT_SHIFT(5)
	};

	enum class MemoryUsage : unsigned int
	{
		CPU_ONLY = UINT_BIT_SHIFT(0),
		GPU_ONLY = UINT_BIT_SHIFT(1),
		GPU_CPU = UINT_BIT_SHIFT(2),
		CPU_GPU = UINT_BIT_SHIFT(3),
	};

	enum class BufferUsage : unsigned int
	{
		MAP_READ = UINT_BIT_SHIFT(0),
		MAP_WRITE = UINT_BIT_SHIFT(1),
		COPY_SRC = UINT_BIT_SHIFT(2),
		COPY_DST = UINT_BIT_SHIFT(3),
		INDEX = UINT_BIT_SHIFT(4),
		VERTEX = UINT_BIT_SHIFT(5),
		UNIFORM = UINT_BIT_SHIFT(6),
		STORAGE = UINT_BIT_SHIFT(7),
		INDIRECT = UINT_BIT_SHIFT(8),
		QUERY_RESOLVE = UINT_BIT_SHIFT(9),
	};

	enum class BufferUsageHint : unsigned int
	{
		STATIC = UINT_BIT_SHIFT(0),
		DYNAMIC = UINT_BIT_SHIFT(1),
	};

	enum class TextureType : unsigned int
	{
		D1 = UINT_BIT_SHIFT(0),
		D2 = UINT_BIT_SHIFT(1),
		D3 = UINT_BIT_SHIFT(2),
	};

	enum class TextureDimention : unsigned int
	{
		D1 = UINT_BIT_SHIFT(0),
		D2 = UINT_BIT_SHIFT(1),
		D2_ARRAY = UINT_BIT_SHIFT(2),
		CUBE = UINT_BIT_SHIFT(3),
		CUBE_ARRAY = UINT_BIT_SHIFT(4),
		D3 = UINT_BIT_SHIFT(5)
	};

	enum class TextureAspect : unsigned int
	{
		NONE = UINT_BIT_SHIFT(0),
		ALL = UINT_BIT_SHIFT(1),
		STENCIL_ONLY = UINT_BIT_SHIFT(2),
		DEPTH_ONLY = UINT_BIT_SHIFT(3),
		PLANE_0_ONLY = UINT_BIT_SHIFT(4), 
		PLANE_1_ONLY = UINT_BIT_SHIFT(5), 
		PLANE_2_ONLY = UINT_BIT_SHIFT(6)
	};

	enum class TextureUsage : unsigned int
	{
		COPY_SRC = UINT_BIT_SHIFT(0),
		COPY_DST = UINT_BIT_SHIFT(1),
		TEXTURE_BINDING = UINT_BIT_SHIFT(2),
		STORAGE_BINDING = UINT_BIT_SHIFT(3),
		RENDER_ATTACHMENT = UINT_BIT_SHIFT(4),
		TRANSIENT = UINT_BIT_SHIFT(5),
	};

	enum class BlendOperation : unsigned int
	{
		ADD = UINT_BIT_SHIFT(0),
		SUB = UINT_BIT_SHIFT(1),
		MIN = UINT_BIT_SHIFT(2),
		MAX = UINT_BIT_SHIFT(3),
	};

	enum class BlendFactor : unsigned int
	{
		SRC_ALPHA = UINT_BIT_SHIFT(0),
		ONE_MINUS_SRC_ALPHA = UINT_BIT_SHIFT(1),
		ONE = UINT_BIT_SHIFT(2),
		ZERO = UINT_BIT_SHIFT(3),
	};

	enum class StoreOperation : unsigned int
	{
		STORE = UINT_BIT_SHIFT(0),
		DISCARD = UINT_BIT_SHIFT(1),
	};

	enum class LoadOperation : unsigned int
	{
		CLEAR = UINT_BIT_SHIFT(0),
		LOAD = UINT_BIT_SHIFT(1),
		DONT_CARE = UINT_BIT_SHIFT(2),
	};

	enum class CommandBufferState : unsigned int
	{
		EMPTY = UINT_BIT_SHIFT(0),
		CAPTURED = UINT_BIT_SHIFT(1),
		PENDING_UPLOAD = UINT_BIT_SHIFT(2)
	};

	enum class CommandBufferType : unsigned int
	{
		OFFSCREEN = UINT_BIT_SHIFT(0),
		MAIN = UINT_BIT_SHIFT(1)
	};

	inline gfx::ShaderStage operator|(gfx::ShaderStage lhs, gfx::ShaderStage rhs)
	{
		return static_cast<gfx::ShaderStage>(
			static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs)
			);
	}

	inline gfx::BufferUsage operator|(gfx::BufferUsage lhs, gfx::BufferUsage rhs)
	{
		return static_cast<gfx::BufferUsage>(
			static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs)
			);
	}

	inline gfx::BufferUsageHint operator|(gfx::BufferUsageHint lhs, gfx::BufferUsageHint rhs)
	{
		return static_cast<gfx::BufferUsageHint>(
			static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs)
			);
	}

	inline gfx::TextureUsage operator|(gfx::TextureUsage lhs, gfx::TextureUsage rhs)
	{
		return static_cast<gfx::TextureUsage>(
			static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs)
			);
	}
}

#endif // !__ENUMS_HPP__
