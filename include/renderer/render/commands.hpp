#ifndef __COMMANDS_HPP__
#define __COMMANDS_HPP__

#include <resources/shader.hpp>
#include <resources/bindGroup.hpp>
#include <resources/buffer.hpp>
#include <resources/dynamicBuffer.hpp>

using namespace utils;

namespace gfx
{
	struct Draw
	{
		Handle<Shader> shader;
		Handle<BindGroup> bindGroups[3];
		Handle<DynamicBuffer> dynamicBuffer;
		Handle<Buffer> indexBuffer;
		Handle<Buffer> vertexBuffers[3];
		uint32_t indexOffset = 0;
		uint32_t vertexOffset = 0;
		uint32_t instanceOffset = 0;
		uint32_t instanceCount = 1;
		uint32_t dynamicBufferOffset = 0;
		uint32_t triangleCount = 0;
	};

	struct Dispatch
	{
		Handle<Shader> shader;
		Handle<BindGroup> bindGroups[3];
		Handle<DynamicBuffer> dynamicBuffer;
		uint32_t dynamicBufferOffset = 0;
	};
}

#endif // !__COMMANDS_HPP__
