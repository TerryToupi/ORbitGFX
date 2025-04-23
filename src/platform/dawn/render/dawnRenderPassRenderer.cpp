#include <dawn/render/dawnRenderPassRenderer.hpp>
#include <dawn/resources/dawnResourceManager.hpp>
#include <dawn/render/dawnRenderer.hpp>
#include <dawn/dawnDevice.hpp>
#include <dawn/dawnWindow.hpp>

namespace gfx
{
    void DawnRenderPassRenderer::DrawSurface(DrawStream& cmds)
    {
        DawnResourceManager* rm = (DawnResourceManager*)ResourceManager::instance;
        DawnDevice* dInstance = (DawnDevice*)Device::instance;
		DawnWindow* windowInstance = (DawnWindow*)Window::instance;

        wgpu::Device device = dInstance->GetDawnDevice();

        wgpu::RenderPassDescriptor dawnDesc = {};

		wgpu::SurfaceTexture surface;
		windowInstance->GetDawnSurface().GetCurrentTexture(&surface); 
		
		DawnRenderPass* rp = rm->Get(s_RenderPass);
		if (rp)
		{
			// There is only one surface
			rp->s_ColorAttachments[0].view = surface.texture.CreateView();

			dawnDesc.colorAttachmentCount = rp->s_ColorAttachmentCount;
			dawnDesc.colorAttachments = rp->s_ColorAttachments;
		} 
	
		wgpu::RenderPassEncoder pass = m_Encoder.BeginRenderPass(&dawnDesc);
		{
			for (const auto& cmd : cmds)
			{
				DawnShader* shader = rm->Get(cmd.shader);
				if (shader)
					pass.SetPipeline(shader->s_Pipeline);

				uint32_t ibg = 0;
				for (const auto& hBindGroup : cmd.bindGroups)
				{
					DawnBindGroup* bindGroup = rm->Get(hBindGroup);
					if (bindGroup)
					{
						pass.SetBindGroup(ibg, bindGroup->s_BindGroup);
						++ibg;
					}
				}

				DawnBuffer* indexBuffer = rm->Get(cmd.indexBuffer);
				if (indexBuffer)
					pass.SetIndexBuffer(indexBuffer->s_Buffer, wgpu::IndexFormat::Uint32);

				uint32_t ib = 0;
				for (const auto& hBuffer : cmd.vertexBuffers)
				{
					DawnBuffer* buffer = rm->Get(hBuffer);
					if (buffer)
					{
						pass.SetVertexBuffer(ib, buffer->s_Buffer);
						++ib;
					}
				}

				pass.DrawIndexed(cmd.triangleCount * 3, cmd.instanceCount);
			}
		}
		pass.End();
    }

	void DawnRenderPassRenderer::DrawFrameBuffer(DrawStream& cmds)
	{
		DawnResourceManager* rm = (DawnResourceManager*)ResourceManager::instance;
		DawnDevice* dInstance = (DawnDevice*)Device::instance;

		wgpu::Device device = dInstance->GetDawnDevice();

		wgpu::RenderPassDescriptor dawnDesc = {};

		DawnRenderPass* rp = rm->Get(s_RenderPass);
		DawnFrameBuffer* fb = rm->Get(s_FrameBuffer);
		if (rp != nullptr && fb != nullptr)
		{
			for (int i = 0; i < rp->s_ColorAttachmentCount; i++)
			{
				rp->s_ColorAttachments[i].view = fb->s_ColorAttachments[i];
			}

			if (rp->s_DepthEnabled)
				rp->s_DepthAttachment.view = fb->s_DepthAttachment;

			dawnDesc.colorAttachmentCount = rp->s_ColorAttachmentCount;
			dawnDesc.colorAttachments = rp->s_ColorAttachments;
			if (rp->s_DepthEnabled)
				dawnDesc.depthStencilAttachment = &rp->s_DepthAttachment;
		}

		wgpu::RenderPassEncoder pass = m_Encoder.BeginRenderPass(&dawnDesc);
		{
			for (const auto& cmd : cmds)
			{
				DawnShader* shader = rm->Get(cmd.shader);
				if (shader)
					pass.SetPipeline(shader->s_Pipeline);

				uint32_t ibg = 0;
				for (const auto& hBindGroup : cmd.bindGroups)
				{
					DawnBindGroup* bindGroup = rm->Get(hBindGroup);
					if (bindGroup)
					{
						pass.SetBindGroup(ibg, bindGroup->s_BindGroup);
						++ibg;
					}
				}

				DawnBuffer* indexBuffer = rm->Get(cmd.indexBuffer);
				if (indexBuffer)
					pass.SetIndexBuffer(indexBuffer->s_Buffer, wgpu::IndexFormat::Uint32);

				uint32_t ib = 0;
				for (const auto& hBuffer : cmd.vertexBuffers)
				{
					DawnBuffer* buffer = rm->Get(hBuffer);
					if (buffer)
					{
						pass.SetVertexBuffer(ib, buffer->s_Buffer);
						++ib;
					}
				}

				pass.DrawIndexed(cmd.triangleCount * 3, cmd.instanceCount);
			}
		}
		pass.End();
	}

    void DawnRenderPassRenderer::DrawPass(DrawStream& cmds)
    { 
		DawnRenderer* renderer = (DawnRenderer*)Renderer::instance;

		s_ActiveStream = std::move(cmds);
		renderer->Execute([=] {
			if (s_SurfacePass)
				DrawSurface(s_ActiveStream);
			else
				DrawFrameBuffer(s_ActiveStream);

			DawnCommandBuffer* buffer = (DawnCommandBuffer*)s_BufferHandle; 
			buffer->m_CommandBuffer = m_Encoder.Finish();
		});
    }
}