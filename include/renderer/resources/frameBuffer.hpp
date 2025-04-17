#ifndef __FRAMEBUFFER_HPP__
#define __FRAMEBUFFER_HPP__

#include <utilities/span.hpp>
#include <utilities/handle.hpp>
#include <renderer/enums.hpp>

#include <renderer/resources/texture.hpp>
#include <renderer/resources/renderPass.hpp>

namespace gfx
{
    class FrameBuffer;
    
    struct FrameBufferDescriptor
    {
        struct ColorTargets
        {
            utils::Handle<Texture> target;
            uint8_t viewIndex = 0;
        };
        
        struct DepthTarget
        {
            utils::Handle<Texture> depth;
            uint8_t viewIndex = 0;
        };

        uint32_t width = 0;
        uint32_t height = 0;
        utils::Handle<RenderPass> renderPass;
       
        DepthTarget depthTarget;
        utils::Span<ColorTargets> colorTargets;
    };
}

#endif
