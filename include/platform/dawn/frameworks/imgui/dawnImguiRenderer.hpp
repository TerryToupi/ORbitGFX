#ifndef __DAWN_IMGUI_RENDERER_HPP__
#define __DAWN_IMGUI_RENDERER_HPP__

#include <frameworks/imgui/imguiRenderer.hpp>
#include <dawn/frameworks/imgui/imgui_impl_glfw.h>
#include <dawn/frameworks/imgui/imgui_impl_wgpu.h>

namespace gfx
{
	class DawnImguiRenderer : public ImguiRenderer
	{
	public:
		virtual void Init() override;
		virtual void BeginFrame() override;
		virtual void EndFrame() override;
	};
}

#endif // !__DAWN_IMGUI_RENDERER_HPP__
