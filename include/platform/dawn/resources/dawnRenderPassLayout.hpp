#ifndef __DAWN_RENDER_PASS_LAYOUT_HPP__
#define __DAWN_RENDER_PASS_LAYOUT_HPP__

#include <dawn/dawnEnums.hpp>
#include <dawn/dawnCommon.hpp>

#include <resources/renderPassLayout.hpp>

namespace gfx
{
    class DawnRenderPassLayout
    {
    public:
        DawnRenderPassLayout();
        DawnRenderPassLayout(const gfx::RenderPassLayoutDescriptor& desc);
        void Destroy();
        
    public:
        uint32_t s_ColorTargetCount = 0;
        wgpu::ColorTargetState s_ColorTargets[kMaxColorAttachments];
        wgpu::BlendState s_ColorBlends[kMaxColorAttachments];
        
        bool s_DepthEnabled = false;
        wgpu::TextureFormat s_DepthFormat;
    };
}

#endif
