#ifndef __BIND_GROUP_LAYOUT_HPP__
#define __BIND_GROUP_LAYOUT_HPP__ 

#include <span.hpp>
#include <handle.hpp>
#include <enums.hpp>
#include <resources/bindGroupLayout.hpp>

namespace gfx
{
	class BindGroupLayout;

	struct BindGroupLayoutDescriptor
	{
        struct TextureBinding
        {
            uint32_t slot = 0;
            TextureDimention viewDimention = TextureDimention::D2;
            ShaderStage visibility = ShaderStage::VERTEX;
        };
        utils::Span<TextureBinding> textureBindings;

        struct BufferBinding
        {
            uint32_t slot = 0;
            BufferBindingType type = BufferBindingType::UNIFORM;
            ShaderStage visibility = ShaderStage::VERTEX;
        };
        utils::Span<BufferBinding> bufferBindings;

        struct SamplerBinding
        {
            uint32_t slot = 0;
            bool comparison = false;
            ShaderStage visibility = ShaderStage::VERTEX;
        };
        utils::Span<SamplerBinding> samplerBindings;
	};
}

#endif // !__BIND_GROUP_LAYOUT_HPP__
