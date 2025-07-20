#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <enums.hpp>
#include <render/passRenderer.hpp>
#include <render/uniforms.hpp>

namespace gfx
{
	class Renderer
	{
	public:
		static inline Renderer* instance = nullptr;

		static void INIT();
		static void SHUTDOWN();

		virtual CommandBuffer* BeginCommandRecording(gfx::CommandBufferType type) = 0;
		virtual UniformRingBuffer* RequestUniformRingBuffer() = 0;

	private:
		virtual void Init() = 0;
		virtual void ShutDown() = 0;
	};
}

#endif
