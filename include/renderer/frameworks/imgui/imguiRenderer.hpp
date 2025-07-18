#ifndef __IMGUI_RENDERER_HPP__
#define __IMGUI_RENDERER_HPP__

namespace gfx
{
	class ImguiRenderer
	{
	public:
		static inline ImguiRenderer* instance = nullptr;

		virtual void Init() = 0;
		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;
	};
}

#endif // !__IMGUI_RENDERER_HPP__
