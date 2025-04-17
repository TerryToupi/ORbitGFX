#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <render/renderPassRenderer.hpp>
#include <render/commandBuffer.hpp>

namespace gfx
{
	class Renderer
	{
	public:
		static inline Renderer* instance = nullptr;

		static void INIT();
		static void SHUTDOWN();

		virtual RenderPassRenderer* RequestPassRenderer() = 0;
		virtual CommandBuffer* BeginCommandRecording() = 0;
	};
}

#endif
