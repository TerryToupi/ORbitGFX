#include <dawn/render/dawnPassRenderer.hpp>
#include <dawn/resources/dawnResourceManager.hpp>
#include <dawn/frameworks/imgui/dawnImguiRenderer.hpp>
#include <dawn/dawnDevice.hpp>
#include <dawn/dawnWindow.hpp>

namespace gfx
{
	void DawnCommandBuffer::BeginRenderPass(utils::Handle<RenderPass> renderPass, utils::Handle<FrameBuffer> frameBuffer, utils::Span<uint32_t> drawCalls)
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
			uint32_t offset = 0;
			DrawStreamDecoder decoder;

			while (offset += decoder.Decode(offset, drawCalls))
			{
				if (IS_BIT_SET(decoder.currDirty, 0))
				{
					DawnShader* shader = rm->Get(decoder.currState.shader);
					if (shader)
						pass.SetPipeline(shader->s_Graphics);
				}

				if (IS_BIT_SET(decoder.currDirty, 1))
				{
					DawnBindGroup* bindGroup0 = rm->Get(decoder.currState.bindGroups[0]);
					if (bindGroup0)
						pass.SetBindGroup(0, bindGroup0->s_BindGroup);
				}

				if (IS_BIT_SET(decoder.currDirty, 2))
				{
					DawnBindGroup* bindGroup1 = rm->Get(decoder.currState.bindGroups[1]);
					if (bindGroup1)
						pass.SetBindGroup(1, bindGroup1->s_BindGroup);
				}
				
				if (IS_BIT_SET(decoder.currDirty, 3))
				{
					DawnBindGroup* bindGroup2 = rm->Get(decoder.currState.bindGroups[2]);
					if (bindGroup2)
						pass.SetBindGroup(2, bindGroup2->s_BindGroup);
				}
				
				if (IS_BIT_SET(decoder.currDirty, 4) || IS_BIT_SET(decoder.currDirty, 13))
				{
					DawnDynamicBuffer* dynamicBuffer = rm->Get(decoder.currState.dynamicBuffer);
					if (dynamicBuffer)
						pass.SetBindGroup(3, dynamicBuffer->s_BindGroup, 1, &decoder.currState.dynamicBufferOffset);
				}

				if (IS_BIT_SET(decoder.currDirty, 5))
				{
					DawnBuffer* indexBuffer = rm->Get(decoder.currState.indexBuffer);
					if (indexBuffer)
						pass.SetIndexBuffer(indexBuffer->s_Buffer, wgpu::IndexFormat::Uint32);
				}
				
				if (IS_BIT_SET(decoder.currDirty, 6))
				{
					DawnBuffer* vertexBuffer0 = rm->Get(decoder.currState.vertexBuffers[0]);
					if (vertexBuffer0)
						pass.SetVertexBuffer(0, vertexBuffer0->s_Buffer);
				}
				
				if (IS_BIT_SET(decoder.currDirty, 7))
				{
					DawnBuffer* vertexBuffer1 = rm->Get(decoder.currState.vertexBuffers[1]);
					if (vertexBuffer1)
						pass.SetVertexBuffer(1, vertexBuffer1->s_Buffer);
				}

				if (IS_BIT_SET(decoder.currDirty, 8))
				{
					DawnBuffer* vertexBuffer2 = rm->Get(decoder.currState.vertexBuffers[2]);
					if (vertexBuffer2)
						pass.SetVertexBuffer(2, vertexBuffer2->s_Buffer);
				}

				pass.DrawIndexed(decoder.currState.triangleCount * 3, decoder.currState.instanceCount, decoder.currState.indexOffset, decoder.currState.vertexOffset, decoder.currState.instanceOffset);

				if (offset == drawCalls.size())
					break;
			}
		}
		pass.End();
	}

	void DawnCommandBuffer::BeginSurfacePass(utils::Handle<RenderPass> renderPass, utils::Span<uint32_t> drawCalls)
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
			uint32_t offset = 0;
			DrawStreamDecoder decoder;

			while (offset += decoder.Decode(offset, drawCalls))
			{
				if (IS_BIT_SET(decoder.currDirty, 0))
				{
					DawnShader* shader = rm->Get(decoder.currState.shader);
					if (shader)
						pass.SetPipeline(shader->s_Graphics);
				}

				if (IS_BIT_SET(decoder.currDirty, 1))
				{
					DawnBindGroup* bindGroup0 = rm->Get(decoder.currState.bindGroups[0]);
					if (bindGroup0)
						pass.SetBindGroup(0, bindGroup0->s_BindGroup);
				}

				if (IS_BIT_SET(decoder.currDirty, 2))
				{
					DawnBindGroup* bindGroup1 = rm->Get(decoder.currState.bindGroups[1]);
					if (bindGroup1)
						pass.SetBindGroup(1, bindGroup1->s_BindGroup);
				}
				
				if (IS_BIT_SET(decoder.currDirty, 3))
				{
					DawnBindGroup* bindGroup2 = rm->Get(decoder.currState.bindGroups[2]);
					if (bindGroup2)
						pass.SetBindGroup(2, bindGroup2->s_BindGroup);
				}
				
				if (IS_BIT_SET(decoder.currDirty, 4) || IS_BIT_SET(decoder.currDirty, 13))
				{
					DawnDynamicBuffer* dynamicBuffer = rm->Get(decoder.currState.dynamicBuffer);
					if (dynamicBuffer)
						pass.SetBindGroup(3, dynamicBuffer->s_BindGroup, 1, &decoder.currState.dynamicBufferOffset);
				}

				if (IS_BIT_SET(decoder.currDirty, 5))
				{
					DawnBuffer* indexBuffer = rm->Get(decoder.currState.indexBuffer);
					if (indexBuffer)
						pass.SetIndexBuffer(indexBuffer->s_Buffer, wgpu::IndexFormat::Uint32);
				}
				
				if (IS_BIT_SET(decoder.currDirty, 6))
				{
					DawnBuffer* vertexBuffer0 = rm->Get(decoder.currState.vertexBuffers[0]);
					if (vertexBuffer0)
						pass.SetVertexBuffer(0, vertexBuffer0->s_Buffer);
				}
				
				if (IS_BIT_SET(decoder.currDirty, 7))
				{
					DawnBuffer* vertexBuffer1 = rm->Get(decoder.currState.vertexBuffers[1]);
					if (vertexBuffer1)
						pass.SetVertexBuffer(1, vertexBuffer1->s_Buffer);
				}

				if (IS_BIT_SET(decoder.currDirty, 8))
				{
					DawnBuffer* vertexBuffer2 = rm->Get(decoder.currState.vertexBuffers[2]);
					if (vertexBuffer2)
						pass.SetVertexBuffer(2, vertexBuffer2->s_Buffer);
				}

				pass.DrawIndexed(decoder.currState.triangleCount * 3, decoder.currState.instanceCount, decoder.currState.indexOffset, decoder.currState.vertexOffset, decoder.currState.instanceOffset);

				if (offset == drawCalls.size())
					break;
			}
		}
		pass.End();
	}

	void DawnCommandBuffer::BeginComputePass(utils::Span<utils::Handle<Texture>> textureWrite, utils::Span<utils::Handle<Buffer>> bufferWrite, utils::Span<Dispatch> dispatches)
	{
	}

	void DawnCommandBuffer::BeginImGuiPass(utils::Handle<RenderPass> renderPass, utils::Handle<FrameBuffer> frameBuffer)
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
		ImGui_ImplWGPU_RenderDrawData(ImGui::GetDrawData(), pass.MoveToCHandle());
		pass.End();
	}

	void DawnCommandBuffer::Submit()
	{
		DawnDevice* deviceImpl = (DawnDevice*)Device::instance;
		wgpu::Device device = deviceImpl->GetDawnDevice();
		
		wgpu::CommandBuffer commandBuffer = m_CommandEncoder.Finish();
		device.GetQueue().Submit(1, &commandBuffer);
	}
}