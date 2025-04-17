#ifndef __DAWN_RENDERER_HPP__
#define __DAWN_RENDERER_HPP__

#include<deque>
#include<functional>

#include <platform/dawn/dawnCommon.hpp>
#include <platform/dawn/render/dawnCommandBuffer.hpp>
#include <platform/dawn/render/dawnRenderPassRenderer.hpp>
#include <renderer/render/renderer.hpp>

namespace gfx
{ 
	class DawnRenderer : public Renderer
	{
	public:
		virtual RenderPassRenderer* RequestPassRenderer() override;
		virtual CommandBuffer* BeginCommandRecording() override;
        
    private:
		// render pass rendering
		DawnRenderPassRenderer m_RenderPassRenderer;

		// command buffers
		DawnCommandBuffer m_mainBuffer;
	};
}

#endif // !__DAWN_RENDERER_HPP__
