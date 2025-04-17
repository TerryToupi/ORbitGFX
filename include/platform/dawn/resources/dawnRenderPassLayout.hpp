#ifndef __DAWN_RENDER_PASS_LAYOUT_HPP__
#define __DAWN_RENDER_PASS_LAYOUT_HPP__

#include <platform/dawn/dawnEnums.hpp>
#include <platform/dawn/dawnCommon.hpp>
#include <renderer/resources/renderPassLayout.hpp>

namespace gfx
{
    class DawnRenderPassLayout
    {
    public:
        DawnRenderPassLayout();
        DawnRenderPassLayout(const gfx::RenderPassLayoutDescriptor& desc);
        void Destroy();
        
    public:
        std::shared_ptr<wgpu::BlendState> s_Blend; 
        
        uint32_t s_ColorTargetCount = 0;
        wgpu::ColorTargetState s_ColorTargets[kMaxColorAttachments];
        
        bool s_DepthEnabled = false;
        wgpu::DepthStencilState s_DepthTarget;
    };
}

#endif
