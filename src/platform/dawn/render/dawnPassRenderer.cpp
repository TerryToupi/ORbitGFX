#include <dawn/render/dawnPassRenderer.hpp>
#include <dawn/resources/dawnResourceManager.hpp>
#include <dawn/dawnDevice.hpp>
#include <dawn/dawnWindow.hpp>

namespace gfx
{
	void DawnCommandBuffer::BeginRenderPass(utils::Handle<RenderPass> renderPass, utils::Handle<FrameBuffer> frameBuffer, std::vector<Draw>& drawCalls)
	{
		DawnResourceManager* rm = (DawnResourceManager*)ResourceManager::instance;
		DawnDevice* dInstance = (DawnDevice*)Device::instance;

		wgpu::Device device = dInstance->GetDawnDevice();

		wgpu::RenderPassDescriptor dawnDesc = {};

		DawnRenderPass* rp = rm->Get(renderPass);
		DawnFrameBuffer* fb = rm->Get(frameBuffer);
		if (rp != nullptr && fb != nullptr)
		{
			for (int i = 0; i < rp->s_ColorAttachmentCount; ++i)
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

		wgpu::RenderPassEncoder pass = m_CommandEncoder.BeginRenderPass(&dawnDesc);
		{
			for (const auto& cmd : drawCalls)
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

	void DawnCommandBuffer::BeginRenderPass(utils::Handle<RenderPass> renderPass, std::vector<Draw>& drawCalls)
	{
		DawnResourceManager* rm = (DawnResourceManager*)ResourceManager::instance;
		DawnDevice* dInstance = (DawnDevice*)Device::instance;
		DawnWindow* windowInstance = (DawnWindow*)Window::instance;

		wgpu::Device device = dInstance->GetDawnDevice();

		wgpu::RenderPassDescriptor dawnDesc = {};

		wgpu::SurfaceTexture surface;
		windowInstance->GetDawnSurface().GetCurrentTexture(&surface);

		DawnRenderPass* rp = rm->Get(renderPass);
		if (rp)
		{
			// There is only one surface
			rp->s_ColorAttachments[0].view = surface.texture.CreateView();

			dawnDesc.colorAttachmentCount = rp->s_ColorAttachmentCount;
			dawnDesc.colorAttachments = rp->s_ColorAttachments;
		}

		wgpu::RenderPassEncoder pass = m_CommandEncoder.BeginRenderPass(&dawnDesc);
		{
			for (const auto& cmd : drawCalls)
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

	void DawnCommandBuffer::BeginComputePass(utils::Span<utils::Handle<Texture>> textureWrite, utils::Span<utils::Handle<Buffer>> bufferWrite, std::vector<Dispatch>& dispatches)
	{
	}

	void DawnCommandBuffer::Submit()
	{
		DawnDevice* deviceImpl = (DawnDevice*)Device::instance;
		wgpu::Device device = deviceImpl->GetDawnDevice();
		
		wgpu::CommandBuffer commandBuffer = m_CommandEncoder.Finish();
		device.GetQueue().Submit(1, &commandBuffer);
	}
}