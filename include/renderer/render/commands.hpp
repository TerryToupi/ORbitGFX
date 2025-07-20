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

#define SHADER_DBIT					0
#define BINDGROUP0_DBIT				1
#define BINDGROUP1_DBIT				2
#define BINDGROUP2_DBIT				3
#define DYNAMICBUFFER_DBIT			4
#define INDEXBUFFER_DBIT			5
#define VERTEXBUFFER0_DBIT			6
#define VERTEXBUFFER1_DBIT			7
#define VERTEXBUFFER2_DBIT			8
#define INDEXOFFSET_DBIT			9
#define VERTEXOFFSET_DBIT			10
#define INSTANCEOFFSET_DBIT			11
#define INSTANCECOUNT_DBIT			12
#define DYNAMICBUFFEROFFSET0_DBIT	13
#define DYNAMICBUFFEROFFSET1_DBIT	14
#define TRIANGLECOUNT_DBIT			15

namespace gfx
{
	struct Vector3I
	{
		uint32_t x = 0;
		uint32_t y = 0;
		uint32_t z = 0;
	};

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
		uint32_t dynamicBufferOffset[2] = {0, 0};
		uint32_t triangleCount = 0;
	};

	struct Dispatch
	{
		Handle<Shader> shader;
		Handle<BindGroup> bindGroups[3];
		Handle<DynamicBuffer> dynamicBuffer;
		uint32_t dynamicBufferOffset[2] = {0, 0};
		Vector3I threadGroupCount;
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
