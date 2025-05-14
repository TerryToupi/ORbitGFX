#include <dawn/render/dawnPassRenderer.hpp>
#include <dawn/resources/dawnResourceManager.hpp>
#include <dawn/dawnDevice.hpp>
#include <dawn/dawnWindow.hpp>

namespace gfx
{
	void DawnCommandBuffer::BeginRenderPass(utils::Handle<RenderPass> renderPass, utils::Handle<FrameBuffer> frameBuffer, utils::Span<Draw> drawCalls)
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

				DawnBindGroup* bindGroup0 = rm->Get(cmd.bindGroups[0]);
				if (bindGroup0)
					pass.SetBindGroup(0, bindGroup0->s_BindGroup);

				DawnBindGroup* bindGroup1 = rm->Get(cmd.bindGroups[1]);
				if (bindGroup1)
					pass.SetBindGroup(1, bindGroup1->s_BindGroup);

				DawnBindGroup* bindGroup2 = rm->Get(cmd.bindGroups[2]);
				if (bindGroup2)
					pass.SetBindGroup(2, bindGroup2->s_BindGroup);

				DawnDynamicBuffer* dynamicBuffer = rm->Get(cmd.dynamicBuffer);
				if (dynamicBuffer)
					pass.SetBindGroup(3, dynamicBuffer->s_BindGroup, 1, &cmd.dynamicBufferOffset);

				DawnBuffer* indexBuffer = rm->Get(cmd.indexBuffer);
				if (indexBuffer)
					pass.SetIndexBuffer(indexBuffer->s_Buffer, wgpu::IndexFormat::Uint32);

				DawnBuffer* vertexBuffer0 = rm->Get(cmd.vertexBuffers[0]);
				if (vertexBuffer0)
					pass.SetVertexBuffer(0, vertexBuffer0->s_Buffer);

				DawnBuffer* vertexBuffer1 = rm->Get(cmd.vertexBuffers[1]);
				if (vertexBuffer1)
					pass.SetVertexBuffer(1, vertexBuffer1->s_Buffer);

				DawnBuffer* vertexBuffer2 = rm->Get(cmd.vertexBuffers[2]);
				if (vertexBuffer2)
					pass.SetVertexBuffer(2, vertexBuffer2->s_Buffer);

				pass.DrawIndexed(cmd.triangleCount * 3, cmd.instanceCount);
			}
		}
		pass.End();
	}

	void DawnCommandBuffer::BeginRenderPass(utils::Handle<RenderPass> renderPass, utils::Span<Draw> drawCalls)
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

				DawnBindGroup* bindGroup0 = rm->Get(cmd.bindGroups[0]);
				if (bindGroup0)
					pass.SetBindGroup(0, bindGroup0->s_BindGroup);

				DawnBindGroup* bindGroup1 = rm->Get(cmd.bindGroups[1]);
				if (bindGroup1)
					pass.SetBindGroup(1, bindGroup1->s_BindGroup);

				DawnBindGroup* bindGroup2 = rm->Get(cmd.bindGroups[2]);
				if (bindGroup2)
					pass.SetBindGroup(2, bindGroup2->s_BindGroup);

				DawnDynamicBuffer* dynamicBuffer = rm->Get(cmd.dynamicBuffer);
				if (dynamicBuffer)
					pass.SetBindGroup(3, dynamicBuffer->s_BindGroup, 1, &cmd.dynamicBufferOffset);

				DawnBuffer* indexBuffer = rm->Get(cmd.indexBuffer);
				if (indexBuffer)
					pass.SetIndexBuffer(indexBuffer->s_Buffer, wgpu::IndexFormat::Uint32);

				DawnBuffer* vertexBuffer0 = rm->Get(cmd.vertexBuffers[0]);
				if (vertexBuffer0)
					pass.SetVertexBuffer(0, vertexBuffer0->s_Buffer);

				DawnBuffer* vertexBuffer1 = rm->Get(cmd.vertexBuffers[1]);
				if (vertexBuffer1)
					pass.SetVertexBuffer(1, vertexBuffer1->s_Buffer);

				DawnBuffer* vertexBuffer2 = rm->Get(cmd.vertexBuffers[2]);
				if (vertexBuffer2)
					pass.SetVertexBuffer(2, vertexBuffer2->s_Buffer);

				pass.DrawIndexed(cmd.triangleCount * 3, cmd.instanceCount);
			}
		}
		pass.End();
	}

	void DawnCommandBuffer::BeginComputePass(utils::Span<utils::Handle<Texture>> textureWrite, utils::Span<utils::Handle<Buffer>> bufferWrite, utils::Span<Dispatch> dispatches)
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