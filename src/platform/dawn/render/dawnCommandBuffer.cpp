#include <platform/dawn/render/dawnCommandBuffer.hpp>
#include <platform/dawn/render/dawnRenderer.hpp>
#include <platform/dawn/dawnDevice.hpp>

namespace gfx
{
    RenderPassRenderer* DawnCommandBuffer::BeginRenderPass(utils::Handle<RenderPass> renderPass, utils::Handle<FrameBuffer> frameBuffer)
    {
        DawnRenderer* renderer = (DawnRenderer*)Renderer::instance;
        RenderPassRenderer* passRenderer = renderer->RequestPassRenderer();

        passRenderer->s_FrameBuffer = frameBuffer;
        passRenderer->s_RenderPass = renderPass;

        return passRenderer;
    }

    RenderPassRenderer* DawnCommandBuffer::BeginSurfacePass(utils::Handle<RenderPass> renderPass)
    {
        DawnRenderer* renderer = (DawnRenderer*)Renderer::instance;
        RenderPassRenderer* passRenderer = renderer->RequestPassRenderer();

        passRenderer->s_SurfacePass = true;
        passRenderer->s_RenderPass = renderPass;

        return passRenderer;
    }

    void DawnCommandBuffer::EndCommandRecording(const RenderPassRenderer* passRenderer)
    {
        DawnRenderPassRenderer* derived = (DawnRenderPassRenderer*)passRenderer;

        m_CommandBuffer = derived->m_Encoder.Finish();
    }

    void DawnCommandBuffer::Submit()
    {
        DawnDevice* dInstance = (DawnDevice*)Device::instance;
        wgpu::Device device = dInstance->GetDawnDevice();

        device.GetQueue().Submit(1, &m_CommandBuffer);
    }
}
