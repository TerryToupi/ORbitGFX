#ifndef __IMGUI_RENDERER_HPP__
#define __IMGUI_RENDERER_HPP__

#include <imgui.h>
#include <handle.hpp>
#include <resources/renderPass.hpp>
#include <resources/renderPassLayout.hpp>

namespace gfx
{
	class ImguiRenderer
	{
	public:
		static inline ImguiRenderer* instance = nullptr;

		virtual void Init() = 0;
		virtual void Begin() = 0;
		virtual void End() = 0;
		virtual void ShutDown() = 0;

	public:
		utils::Handle<RenderPass> s_RenderPass;
		utils::Handle<RenderPassLayout> s_RenderPassLayout;
	};
}

#endif // !__IMGUI_RENDERER_HPP__
