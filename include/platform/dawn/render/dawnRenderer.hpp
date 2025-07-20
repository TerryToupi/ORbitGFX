#ifndef __DAWN_RENDERER_HPP__
#define __DAWN_RENDERER_HPP__

#include <dawn/dawnCommon.hpp>
#include <render/renderer.hpp>
#include <dawn/render/dawnPassRenderer.hpp>
#include <render/uniforms.hpp>

namespace gfx
{ 
	class DawnRenderer : public Renderer
	{
	public:
		virtual CommandBuffer* BeginCommandRecording(gfx::CommandBufferType type) override;
		virtual UniformRingBuffer* RequestUniformRingBuffer() override;

	private:
		virtual void Init() override;
		virtual void ShutDown() override;
        
    private:
		// command buffers
		DawnCommandBuffer m_OffScreenCB;
		DawnCommandBuffer m_MainCB;
		DawnCommandBuffer m_PostEffectCB;
		DawnCommandBuffer m_UiCB;

		UniformRingBuffer m_PerDrawRingBuffer;
	};
}

#endif // !__DAWN_RENDERER_HPP__
