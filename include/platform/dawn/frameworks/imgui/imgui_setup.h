#ifndef __IMGUI_SETUP_H__
#define __IMGUI_SETUP_H__

#include <dawn/frameworks/imgui/imgui_impl_glfw.h>
#include <dawn/frameworks/imgui/imgui_impl_wgpu.h>

namespace gfx
{
	namespace UI
	{
		namespace IMGUI
		{
			void SetupIMGUI();
		}
	}
}

#endif // !__IMGUI_SETUP_H__
