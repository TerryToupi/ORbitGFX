#ifndef __DAWN_COMMAND_BUFFER_HPP__
#define __DAWN_COMMAND_BUFFER_HPP__

#include <dawn/dawnCommon.hpp>
#include <dawn/render/dawnRenderPassRenderer.hpp>

#include <render/commandBuffer.hpp>

namespace gfx
{
    class DawnCommandBuffer : public CommandBuffer
    {
    public:
        virtual RenderPassRenderer* BeginRenderPass(utils::Handle<RenderPass> renderPass, utils::Handle<FrameBuffer> frameBuffer) override;
        virtual RenderPassRenderer* BeginSurfacePass(utils::Handle<RenderPass> renderPass) override;
        virtual void EndCommandRecording(const RenderPassRenderer* passRenderer) override;
        virtual void Submit() override;
        
    private:
        wgpu::CommandBuffer m_CommandBuffer;

        friend class DawnRenderer;
        friend class DawnRenderPassRenderer;
    };
}

#endif
