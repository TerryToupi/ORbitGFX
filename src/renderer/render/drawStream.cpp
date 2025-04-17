#include <renderer/render/drawStream.hpp>

namespace gfx
{
	void DrawStream::Insert(const Draw& cmd)
	{
		m_DrawCmds.emplace_back(cmd);
	}
}