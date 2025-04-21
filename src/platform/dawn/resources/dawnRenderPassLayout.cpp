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
