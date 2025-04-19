#include <dawn/resources/dawnRenderPassLayout.hpp>

namespace gfx
{
    DawnRenderPassLayout::DawnRenderPassLayout()
        :   s_DepthEnabled(false), s_ColorTargetCount(0)
    {
        for (int i = 0; i < kMaxColorAttachments; ++i)
        {
            s_ColorTargets[i] = {};
            s_ColorBlends[i] = {};
        }
    }

    DawnRenderPassLayout::DawnRenderPassLayout(const gfx::RenderPassLayoutDescriptor& desc)
    {
        //s_Blend = std::make_shared<wgpu::BlendState>();

        //s_Blend->color.operation = gfx::DecodeBlendOperationType(desc.blend.colorOp);
        //s_Blend->color.srcFactor = gfx::DecodeBlendFactorType(desc.blend.srcColorFactor);
        //s_Blend->color.dstFactor = gfx::DecodeBlendFactorType(desc.blend.dstColorFactor);
        //
        //s_Blend->alpha.operation = gfx::DecodeBlendOperationType(desc.blend.alphaOp);
        //s_Blend->alpha.srcFactor = gfx::DecodeBlendFactorType(desc.blend.srcAlphaFactor);
        //s_Blend->alpha.dstFactor = gfx::DecodeBlendFactorType(desc.blend.dstAlphaFactor);
        
        int index = 0;
        for (const auto& colorTarget : desc.colorTargets)
        {
			s_ColorBlends[index].color.operation = gfx::DecodeBlendOperationType(colorTarget.blend.colorOp);
			s_ColorBlends[index].color.srcFactor = gfx::DecodeBlendFactorType(colorTarget.blend.srcColorFactor);
			s_ColorBlends[index].color.dstFactor = gfx::DecodeBlendFactorType(colorTarget.blend.dstColorFactor);
			
			s_ColorBlends[index].alpha.operation = gfx::DecodeBlendOperationType(colorTarget.blend.alphaOp);
			s_ColorBlends[index].alpha.srcFactor = gfx::DecodeBlendFactorType(colorTarget.blend.srcAlphaFactor);
			s_ColorBlends[index].alpha.dstFactor = gfx::DecodeBlendFactorType(colorTarget.blend.dstAlphaFactor);

            s_ColorTargets[index].format = gfx::DecodeTextureFormatType(colorTarget.format);
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
