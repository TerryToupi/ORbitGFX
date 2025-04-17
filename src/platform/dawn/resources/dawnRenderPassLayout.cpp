#include <platform/dawn/resources/dawnRenderPassLayout.hpp>

namespace gfx
{
    DawnRenderPassLayout::DawnRenderPassLayout()
        :   s_DepthEnabled(false), s_ColorTargetCount(0)
    {
        for (int i = 0; i < kMaxColorAttachments; ++i)
        {
            s_ColorTargets[i] = {};
        }
    }

    DawnRenderPassLayout::DawnRenderPassLayout(const gfx::RenderPassLayoutDescriptor& desc)
    {
        s_Blend = std::make_shared<wgpu::BlendState>();

        s_Blend->color.operation = gfx::DecodeBlendOperationType(desc.blend.colorOp);
        s_Blend->color.srcFactor = gfx::DecodeBlendFactorType(desc.blend.srcColorFactor);
        s_Blend->color.dstFactor = gfx::DecodeBlendFactorType(desc.blend.dstColorFactor);
        
        s_Blend->alpha.operation = gfx::DecodeBlendOperationType(desc.blend.alphaOp);
        s_Blend->alpha.srcFactor = gfx::DecodeBlendFactorType(desc.blend.srcAlphaFactor);
        s_Blend->alpha.dstFactor = gfx::DecodeBlendFactorType(desc.blend.dstAlphaFactor);
        
        int index = 0;
        for (const auto& colorTarget : desc.colorTargets)
        {
            s_ColorTargets[index].format = gfx::DecodeTextureFormatType(colorTarget.format);
            s_ColorTargets[index].blend = s_Blend.get();
            ++index;
        }
        s_ColorTargetCount = index;
        
        s_DepthEnabled = desc.depth.depthTarget;
        if (s_DepthEnabled)
        {
            s_DepthTarget.format = gfx::DecodeTextureFormatType(desc.depth.depthTargetFormat);
            s_DepthTarget.depthCompare = gfx::DecodeCompareType(desc.depth.depthTest);
        }
    }
    
    void DawnRenderPassLayout::Destroy()
    {
    }
}
