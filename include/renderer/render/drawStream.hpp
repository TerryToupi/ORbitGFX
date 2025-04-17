#ifndef __DRAW_STREAM_HPP__
#define __DRAW_STREAM_HPP__

#include <handle.hpp>

#include <resources/shader.hpp>
#include <resources/bindGroup.hpp>
#include <resources/buffer.hpp>

#include <vector>

using namespace utils;

namespace gfx
{
	struct Draw
	{
		Handle<Shader> shader;
		Handle<BindGroup> bindGroups[3];
		uint32_t dynamicBuffer;
		Handle<Buffer> indexBuffer;
		Handle<Buffer> vertexBuffers[3];
		uint32_t indexOffset = 0;
		uint32_t vertexOffset = 0;
		uint32_t instanceOffset = 0;
		uint32_t instanceCount = 1;
		uint32_t dynamicBufferOffset[2] = {0};
		uint32_t triangleCount = 0;
	};

	class DrawStream
	{
	public:
		void Insert(const Draw& cmd);

		auto begin() { return m_DrawCmds.begin(); }
		auto end() { return m_DrawCmds.end(); }

	private:
		std::vector<Draw> m_DrawCmds;
	};
}

#endif // !__DRAW_STREAM_HPP__
