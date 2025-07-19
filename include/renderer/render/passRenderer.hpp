#ifndef __PASS_RENDERER_HPP__
#define __PASS_RENDERER_HPP__

#include <handle.hpp>
#include <span.hpp>
#include <resources/renderPass.hpp>
#include <resources/frameBuffer.hpp>
#include <resources/Buffer.hpp>
#include <resources/texture.hpp>
#include <render/commands.hpp>

namespace gfx
{
	class CommandBuffer
	{
	public:
		virtual void BeginRenderPass(
			utils::Handle<RenderPass> renderPass, 
			utils::Handle<FrameBuffer> frameBuffer, 
			utils::Span<uint32_t> drawCalls
		) = 0;

		virtual void BeginSurfacePass(
			utils::Handle<RenderPass> renderPass, 
			utils::Span<uint32_t> drawCalls
		) = 0;

		virtual void BeginComputePass(
			utils::Span<utils::Handle<Texture>> textureWrite, 
			utils::Span<utils::Handle<Buffer>> bufferWrite,
			utils::Span<Dispatch> dispatches
		) = 0;

		virtual void BeginImGuiPass(
			utils::Handle<RenderPass> renderPass,
			utils::Handle<FrameBuffer> frameBuffer
		) = 0;

		virtual void Submit() = 0;
	};
}

#endif
