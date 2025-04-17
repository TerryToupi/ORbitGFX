#ifndef __BIND_GROUP_HPP__
#define __BIND_GROUP_HPP__

#include <utilities/span.hpp>
#include <utilities/handle.hpp>
#include <renderer/enums.hpp>

#include <renderer/resources/bindGroupLayout.hpp>
#include <renderer/resources/texture.hpp>
#include <renderer/resources/sampler.hpp>
#include <renderer/resources/buffer.hpp>

namespace gfx
{
	class BindGroup;

	struct BindGroupDescriptor
    {
        utils::Handle<BindGroupLayout> layout;

        struct BufferEntry
        {
            uint32_t slot = 0;
            utils::Handle<Buffer> buffer;
            uint32_t byteOffset = 0;
            uint32_t range = 0;
        };
        
        struct TextureEntry
        {
            uint32_t slot = 0;
            utils::Handle<Texture> textureView;
            uint32_t viewIndex = 0;
        };
        
        struct SamplerEntry
        {
            uint32_t slot = 0;
            utils::Handle<Sampler> sampler;
        };
        
        utils::Span<BufferEntry> buffers;
        utils::Span<TextureEntry> textures;
        utils::Span<SamplerEntry> samplers;
    };
}

#endif // !__BIND_GROUP_HPP__
