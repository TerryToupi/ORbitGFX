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

		virtual void Upload() = 0;

	private:
		virtual void Init() = 0;
		virtual void ShutDown() = 0;
	};
}

#endif
