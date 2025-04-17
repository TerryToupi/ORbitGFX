#ifndef __DAWN_RENDERER_HPP__
#define __DAWN_RENDERER_HPP__

#include<deque>
#include<functional>

#include <dawn/dawnCommon.hpp>
#include <dawn/render/dawnCommandBuffer.hpp>
#include <dawn/render/dawnRenderPassRenderer.hpp>

#include <render/renderer.hpp>

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
