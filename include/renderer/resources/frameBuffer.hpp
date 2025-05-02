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
        utils::Handle<RenderPass> renderPass;
       
        utils::Handle<Texture> depthTarget;
        utils::Span<utils::Handle<Texture>> colorTargets;
    };
}

#endif
