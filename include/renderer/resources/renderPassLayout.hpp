#ifndef __RENDER_PASS_LAYOUT_HPP__
#define __RENDER_PASS_LAYOUT_HPP__

#include <span.hpp>
#include <enums.hpp>

namespace gfx
{
    class RenderPassLayout;
    
    struct RenderPassLayoutDescriptor
    {
        struct DepthDescriptor
        {
            bool depthTarget = false;
            TextureFormat depthTargetFormat = TextureFormat::D32_FLOAT;
            gfx::Compare depthTest = gfx::Compare::UNDEFINED;
        };

        struct BlendDescriptor
        {
            BlendOperation colorOp = BlendOperation::ADD;
            BlendFactor srcColorFactor = BlendFactor::SRC_ALPHA;
            BlendFactor dstColorFactor = BlendFactor::ONE_MINUS_SRC_ALPHA;
            BlendOperation alphaOp = BlendOperation::ADD;
            BlendFactor srcAlphaFactor = BlendFactor::ONE;
            BlendFactor dstAlphaFactor = BlendFactor::ZERO;
        };
        
        struct ColorTargetDescriptor
        {
            bool enabled = true;
            TextureFormat format = TextureFormat::RGBA8_UNORM;
            BlendDescriptor blend = {};
        };
        
        utils::Span<ColorTargetDescriptor> colorTargets;
        DepthDescriptor depth;
    };
}

#endif
