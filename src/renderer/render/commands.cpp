#include <render/commands.hpp>

namespace gfx
{
	DrawStreamEncoder::DrawStreamEncoder()
	{
		m_CurrState.shader = Handle<Shader>();
		m_CurrState.bindGroups[0] = Handle<BindGroup>();
		m_CurrState.bindGroups[1] = Handle<BindGroup>();
		m_CurrState.bindGroups[2] = Handle<BindGroup>();
		m_CurrState.dynamicBuffer = Handle<DynamicBuffer>();
		m_CurrState.indexBuffer = Handle<Buffer>();
		m_CurrState.vertexBuffers[0] = Handle<Buffer>();
		m_CurrState.vertexBuffers[1] = Handle<Buffer>();
		m_CurrState.vertexBuffers[2] = Handle<Buffer>();
		m_CurrState.indexOffset = 0;
		m_CurrState.vertexOffset = 0;
		m_CurrState.instanceOffset = 0;
		m_CurrState.instanceCount = 1;
		m_CurrState.dynamicBufferOffset[0] = 0;
		m_CurrState.dynamicBufferOffset[1] = 0;
		m_CurrState.triangleCount = 0;

		m_Stream.reserve(256);
	}

	void DrawStreamEncoder::Encode(const Draw& draw)
	{
		uint32_t currDirty = 0;

		if (draw.shader != m_CurrState.shader)
		{
			SET_BIT(currDirty, SHADER_DBIT);
			m_CurrState.shader = draw.shader;
		}
		if (draw.bindGroups[0] != m_CurrState.bindGroups[0])
		{
			SET_BIT(currDirty, BINDGROUP0_DBIT);
			m_CurrState.bindGroups[0] = draw.bindGroups[0];
		}
		if (draw.bindGroups[1] != m_CurrState.bindGroups[1])
		{
			SET_BIT(currDirty, BINDGROUP1_DBIT);
			m_CurrState.bindGroups[1] = draw.bindGroups[1];
		}
		if (draw.bindGroups[2] != m_CurrState.bindGroups[2])
		{
			SET_BIT(currDirty, BINDGROUP2_DBIT);
			m_CurrState.bindGroups[2] = draw.bindGroups[2];
		}
		if (draw.dynamicBuffer != m_CurrState.dynamicBuffer)
		{
			SET_BIT(currDirty, DYNAMICBUFFER_DBIT);
			m_CurrState.dynamicBuffer = draw.dynamicBuffer;
		}
		if (draw.indexBuffer != m_CurrState.indexBuffer)
		{
			SET_BIT(currDirty, INDEXBUFFER_DBIT);
			m_CurrState.indexBuffer = draw.indexBuffer;
		}
		if (draw.vertexBuffers[0] != m_CurrState.vertexBuffers[0])
		{
			SET_BIT(currDirty, VERTEXBUFFER0_DBIT);
			m_CurrState.vertexBuffers[0] = draw.vertexBuffers[0];
		}
		if (draw.vertexBuffers[1] != m_CurrState.vertexBuffers[1])
		{
			SET_BIT(currDirty, VERTEXBUFFER1_DBIT);
			m_CurrState.vertexBuffers[1] = draw.vertexBuffers[1];
		}
		if (draw.vertexBuffers[2] != m_CurrState.vertexBuffers[2])
		{
			SET_BIT(currDirty, VERTEXBUFFER2_DBIT);
			m_CurrState.vertexBuffers[2] = draw.vertexBuffers[2];
		}
		if (draw.indexOffset != m_CurrState.indexOffset)
		{
			SET_BIT(currDirty, INDEXOFFSET_DBIT);
			m_CurrState.indexOffset = draw.indexOffset;
		}
		if (draw.vertexOffset != m_CurrState.vertexOffset)
		{
			SET_BIT(currDirty, VERTEXOFFSET_DBIT);
			m_CurrState.vertexOffset = draw.vertexOffset;
		}
		if (draw.instanceOffset != m_CurrState.instanceOffset)
		{
			SET_BIT(currDirty, INSTANCEOFFSET_DBIT);
			m_CurrState.instanceOffset = draw.instanceOffset;
		}
		if (draw.instanceCount != m_CurrState.instanceCount)
		{
			SET_BIT(currDirty, INSTANCECOUNT_DBIT);
			m_CurrState.instanceCount = draw.instanceCount;
		}
		if (draw.dynamicBufferOffset[0] != m_CurrState.dynamicBufferOffset[0])
		{
			SET_BIT(currDirty, DYNAMICBUFFEROFFSET0_DBIT);
			m_CurrState.dynamicBufferOffset[0] = draw.dynamicBufferOffset[0];
		}
		if (draw.dynamicBufferOffset[1] != m_CurrState.dynamicBufferOffset[1])
		{
			SET_BIT(currDirty, DYNAMICBUFFEROFFSET1_DBIT);
			m_CurrState.dynamicBufferOffset[1] = draw.dynamicBufferOffset[1];
		}
		if (draw.triangleCount != m_CurrState.triangleCount)
		{
			SET_BIT(currDirty, TRIANGLECOUNT_DBIT);
			m_CurrState.triangleCount = draw.triangleCount;
		} 

		m_Stream.emplace_back(currDirty);

		for (uint32_t i = 0; i < 16; ++i)
		{
			if (IS_BIT_SET(currDirty, i) && i == SHADER_DBIT)
				m_Stream.emplace_back(m_CurrState.shader.pack());
			else if (IS_BIT_SET(currDirty, i) && i == BINDGROUP0_DBIT)
				m_Stream.emplace_back(m_CurrState.bindGroups[0].pack());
			else if (IS_BIT_SET(currDirty, i) && i == BINDGROUP1_DBIT)
				m_Stream.emplace_back(m_CurrState.bindGroups[1].pack());
			else if (IS_BIT_SET(currDirty, i) && i == BINDGROUP2_DBIT)
				m_Stream.emplace_back(m_CurrState.bindGroups[2].pack());
			else if (IS_BIT_SET(currDirty, i) && i == DYNAMICBUFFER_DBIT)
				m_Stream.emplace_back(m_CurrState.dynamicBuffer.pack());
			else if (IS_BIT_SET(currDirty, i) && i == INDEXBUFFER_DBIT)
				m_Stream.emplace_back(m_CurrState.indexBuffer.pack());
			else if (IS_BIT_SET(currDirty, i) && i == VERTEXBUFFER0_DBIT)
				m_Stream.emplace_back(m_CurrState.vertexBuffers[0].pack());
			else if (IS_BIT_SET(currDirty, i) && i == VERTEXBUFFER1_DBIT)
				m_Stream.emplace_back(m_CurrState.vertexBuffers[1].pack());
			else if (IS_BIT_SET(currDirty, i) && i == VERTEXBUFFER2_DBIT)
				m_Stream.emplace_back(m_CurrState.vertexBuffers[2].pack());
			else if (IS_BIT_SET(currDirty, i) && i == INDEXOFFSET_DBIT)
				m_Stream.emplace_back(m_CurrState.indexOffset);
			else if (IS_BIT_SET(currDirty, i) && i == VERTEXOFFSET_DBIT)
				m_Stream.emplace_back(m_CurrState.vertexOffset);
			else if (IS_BIT_SET(currDirty, i) && i == INSTANCEOFFSET_DBIT)
				m_Stream.emplace_back(m_CurrState.instanceOffset);
			else if (IS_BIT_SET(currDirty, i) && i == INSTANCECOUNT_DBIT)
				m_Stream.emplace_back(m_CurrState.instanceCount);
			else if (IS_BIT_SET(currDirty, i) && i == DYNAMICBUFFEROFFSET0_DBIT)
				m_Stream.emplace_back(m_CurrState.dynamicBufferOffset[0]);
			else if (IS_BIT_SET(currDirty, i) && i == DYNAMICBUFFEROFFSET1_DBIT)
				m_Stream.emplace_back(m_CurrState.dynamicBufferOffset[1]);
			else if (IS_BIT_SET(currDirty, i) && i == TRIANGLECOUNT_DBIT)
				m_Stream.emplace_back(m_CurrState.triangleCount);
		}
	}

	std::vector<uint32_t>& DrawStreamEncoder::Get()
	{
		return m_Stream;
	}

	DrawStreamDecoder::DrawStreamDecoder()
	{
		currDirty = 0;

		currState.shader = Handle<Shader>();
		currState.bindGroups[0] = Handle<BindGroup>();
		currState.bindGroups[1] = Handle<BindGroup>();
		currState.bindGroups[2] = Handle<BindGroup>();
		currState.dynamicBuffer = Handle<DynamicBuffer>();
		currState.indexBuffer = Handle<Buffer>();
		currState.vertexBuffers[0] = Handle<Buffer>();
		currState.vertexBuffers[1] = Handle<Buffer>();
		currState.vertexBuffers[2] = Handle<Buffer>();
		currState.indexOffset = 0;
		currState.vertexOffset = 0;
		currState.instanceOffset = 0;
		currState.instanceCount = 1;
		currState.dynamicBufferOffset[0] = 0;
		currState.dynamicBufferOffset[1] = 0;
		currState.triangleCount = 0;
	}

	uint32_t DrawStreamDecoder::Decode(uint32_t index, Span<uint32_t> stream)
	{
		uint32_t currIndex = index;
		
		currDirty = stream[index++];

		if (IS_BIT_SET(currDirty, 0))
		{
			currState.shader.unpack(stream[index++]);
		}
		if (IS_BIT_SET(currDirty, 1))
		{
			currState.bindGroups[0].unpack(stream[index++]);
		}
		if (IS_BIT_SET(currDirty, 2))
		{
			currState.bindGroups[1].unpack(stream[index++]);
		}
		if (IS_BIT_SET(currDirty, 3))
		{
			currState.bindGroups[2].unpack(stream[index++]);
		}
		if (IS_BIT_SET(currDirty, 4))
		{
			currState.dynamicBuffer.unpack(stream[index++]);
		}
		if (IS_BIT_SET(currDirty, 5))
		{
			currState.indexBuffer.unpack(stream[index++]);
		}
		if (IS_BIT_SET(currDirty, 6))
		{
			currState.vertexBuffers[0].unpack(stream[index++]);
		}
		if (IS_BIT_SET(currDirty, 7))
		{
			currState.vertexBuffers[1].unpack(stream[index++]);
		}
		if (IS_BIT_SET(currDirty, 8))
		{
			currState.vertexBuffers[2].unpack(stream[index++]);
		}
		if (IS_BIT_SET(currDirty, 9))
		{
			currState.indexOffset = stream[index++];
		}
		if (IS_BIT_SET(currDirty, 10))
		{
			currState.vertexOffset = stream[index++];
		}
		if (IS_BIT_SET(currDirty, 11))
		{
			currState.instanceOffset = stream[index++];
		}
		if (IS_BIT_SET(currDirty, 12))
		{
			currState.instanceCount = stream[index++];
		}
		if (IS_BIT_SET(currDirty, 13))
		{
			currState.dynamicBufferOffset = stream[index++];
		}
		if (IS_BIT_SET(currDirty, 14))
		{
			currState.triangleCount = stream[index++];
		}

		return index - currIndex;
	}
}