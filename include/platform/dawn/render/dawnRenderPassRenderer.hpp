#ifndef __DAWN_RENDER_PASS_RENDERER_HPP__
#define __DAWN_RENDER_PASS_RENDERER_HPP__

#include <renderer/render/renderPassRenderer.hpp>
#include <platform/dawn/dawnCommon.hpp>

namespace gfx
{
    class DawnRenderPassRenderer : public RenderPassRenderer
    {
    public:
        virtual void DrawPass(DrawStream& cmds) override;

    private:
        void DrawSurface(DrawStream& cmds);
        void DrawFrameBuffer(DrawStream& cmds);
        
    private:
        wgpu::CommandEncoder m_Encoder;

        friend class DawnRenderer;
        friend class DawnCommandBuffer;
    };
}

#endif
