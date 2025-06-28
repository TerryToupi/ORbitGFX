#ifndef __COMMANDS_HPP__
#define __COMMANDS_HPP__

#include <handle.hpp>
#include <span.hpp>
#include <resources/shader.hpp>
#include <resources/bindGroup.hpp>
#include <resources/buffer.hpp>
#include <resources/dynamicBuffer.hpp>
#include <vector>

using namespace utils;

#define SET_BIT(var, bit) ((var) |= (1U << (bit)))
#define IS_BIT_SET(var, bit) (((var) & (1U << (bit))) != 0)

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

	class DrawStreamEncoder
	{
	public:
		DrawStreamEncoder();
		
		void Encode(const Draw& draw);
		std::vector<uint32_t>& Get();

	private:
		Draw m_CurrState;
		std::vector<uint32_t> m_Stream;
	};

	class DrawStreamDecoder
	{
	public:
		DrawStreamDecoder();

		uint32_t Decode(uint32_t index, Span<uint32_t> stream);

		uint32_t currDirty;
		Draw currState;
	};
}

#endif // !__COMMANDS_HPP__
