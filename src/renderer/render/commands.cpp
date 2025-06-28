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
		m_CurrState.dynamicBufferOffset = 0;
		m_CurrState.triangleCount = 0;

		m_Stream.reserve(256);
	}

	void DrawStreamEncoder::Encode(const Draw& draw)
	{
		uint32_t currDirty = 0;

		if (draw.shader != m_CurrState.shader)
		{
			SET_BIT(currDirty, 0);
			m_CurrState.shader = draw.shader;
		}
		if (draw.bindGroups[0] != m_CurrState.bindGroups[0])
		{
			SET_BIT(currDirty, 1);
			m_CurrState.bindGroups[0] = draw.bindGroups[0];
		}
		if (draw.bindGroups[1] != m_CurrState.bindGroups[1])
		{
			SET_BIT(currDirty, 2);
			m_CurrState.bindGroups[1] = draw.bindGroups[1];
		}
		if (draw.bindGroups[2] != m_CurrState.bindGroups[2])
		{
			SET_BIT(currDirty, 3);
			m_CurrState.bindGroups[2] = draw.bindGroups[2];
		}
		if (draw.dynamicBuffer != m_CurrState.dynamicBuffer)
		{
			SET_BIT(currDirty, 4);
			m_CurrState.dynamicBuffer = draw.dynamicBuffer;
		}
		if (draw.indexBuffer != m_CurrState.indexBuffer)
		{
			SET_BIT(currDirty, 5);
			m_CurrState.indexBuffer = draw.indexBuffer;
		}
		if (draw.vertexBuffers[0] != m_CurrState.vertexBuffers[0])
		{
			SET_BIT(currDirty, 6);
			m_CurrState.vertexBuffers[0] = draw.vertexBuffers[0];
		}
		if (draw.vertexBuffers[1] != m_CurrState.vertexBuffers[1])
		{
			SET_BIT(currDirty, 7);
			m_CurrState.vertexBuffers[1] = draw.vertexBuffers[1];
		}
		if (draw.vertexBuffers[2] != m_CurrState.vertexBuffers[2])
		{
			SET_BIT(currDirty, 8);
			m_CurrState.vertexBuffers[2] = draw.vertexBuffers[2];
		}
		if (draw.indexOffset != m_CurrState.indexOffset)
		{
			SET_BIT(currDirty, 9);
			m_CurrState.indexOffset = draw.indexOffset;
		}
		if (draw.vertexOffset != m_CurrState.vertexOffset)
		{
			SET_BIT(currDirty, 10);
			m_CurrState.vertexOffset = draw.vertexOffset;
		}
		if (draw.instanceOffset != m_CurrState.instanceOffset)
		{
			SET_BIT(currDirty, 11);
			m_CurrState.instanceOffset = draw.instanceOffset;
		}
		if (draw.instanceCount != m_CurrState.instanceCount)
		{
			SET_BIT(currDirty, 12);
			m_CurrState.instanceCount = draw.instanceCount;
		}
		if (draw.dynamicBufferOffset != m_CurrState.dynamicBufferOffset)
		{
			SET_BIT(currDirty, 13);
			m_CurrState.dynamicBufferOffset = draw.dynamicBufferOffset;
		}
		if (draw.triangleCount != m_CurrState.triangleCount)
		{
			SET_BIT(currDirty, 14);
			m_CurrState.triangleCount = draw.triangleCount;
		} 

		m_Stream.emplace_back(currDirty);

		for (uint32_t i = 0; i < 15; ++i)
		{
			if (IS_BIT_SET(currDirty, i) && i == 0)
				m_Stream.emplace_back(m_CurrState.shader.pack());
			else if (IS_BIT_SET(currDirty, i) && i == 1)
				m_Stream.emplace_back(m_CurrState.bindGroups[0].pack());
			else if (IS_BIT_SET(currDirty, i) && i == 2)
				m_Stream.emplace_back(m_CurrState.bindGroups[1].pack());
			else if (IS_BIT_SET(currDirty, i) && i == 3)
				m_Stream.emplace_back(m_CurrState.bindGroups[2].pack());
			else if (IS_BIT_SET(currDirty, i) && i == 4)
				m_Stream.emplace_back(m_CurrState.dynamicBuffer.pack());
			else if (IS_BIT_SET(currDirty, i) && i == 5)
				m_Stream.emplace_back(m_CurrState.indexBuffer.pack());
			else if (IS_BIT_SET(currDirty, i) && i == 6)
				m_Stream.emplace_back(m_CurrState.vertexBuffers[0].pack());
			else if (IS_BIT_SET(currDirty, i) && i == 7)
				m_Stream.emplace_back(m_CurrState.vertexBuffers[1].pack());
			else if (IS_BIT_SET(currDirty, i) && i == 8)
				m_Stream.emplace_back(m_CurrState.vertexBuffers[2].pack());
			else if (IS_BIT_SET(currDirty, i) && i == 9)
				m_Stream.emplace_back(m_CurrState.indexOffset);
			else if (IS_BIT_SET(currDirty, i) && i == 10)
				m_Stream.emplace_back(m_CurrState.vertexOffset);
			else if (IS_BIT_SET(currDirty, i) && i == 11)
				m_Stream.emplace_back(m_CurrState.instanceOffset);
			else if (IS_BIT_SET(currDirty, i) && i == 12)
				m_Stream.emplace_back(m_CurrState.instanceCount);
			else if (IS_BIT_SET(currDirty, i) && i == 13)
				m_Stream.emplace_back(m_CurrState.dynamicBufferOffset);
			else if (IS_BIT_SET(currDirty, i) && i == 14)
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
		currState.dynamicBufferOffset = 0;
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

		if (index >= stream.size())
			return UINT32_MAX;

		return index - currIndex;
	}
}