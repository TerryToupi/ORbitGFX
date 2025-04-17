#ifndef __FRAMEBUFFER_HPP__
#define __FRAMEBUFFER_HPP__

#include <span.hpp>
#include <handle.hpp>
#include <enums.hpp>

#include <resources/texture.hpp>
#include <resources/renderPass.hpp>

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
