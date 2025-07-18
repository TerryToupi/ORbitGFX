#ifndef __DAWN_PASS_RENDERER_HPP__
#define __DAWN_PASS_RENDERER_HPP__

#include <render/passRenderer.hpp>
#include <dawn/dawnCommon.hpp>

namespace gfx
{
	class DawnRenderer;

	class DawnCommandBuffer : public CommandBuffer
	{
	public:
		virtual void BeginRenderPass(
			utils::Handle<RenderPass> renderPass,
			utils::Handle<FrameBuffer> frameBuffer,
			utils::Span<uint32_t> drawCalls	
		) override;

		virtual void BeginSurfacePass(
			utils::Handle<RenderPass> renderPass,
			utils::Span<uint32_t> drawCalls	
		) override;

		virtual void BeginComputePass(
			utils::Span<utils::Handle<Texture>> textureWrite,
			utils::Span<utils::Handle<Buffer>> bufferWrite,
			utils::Span<Dispatch> dispatches
		) override;

		virtual void Submit() override;

	private:
		wgpu::CommandEncoder m_CommandEncoder;

	private:
		friend class DawnRenderer;
	};
}

#endif // !__DAWN_PASS_RENDERER_HPP__
