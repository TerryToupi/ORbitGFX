#include <dawn/frameworks/imgui/dawnImguiRenderer.hpp>
#include <dawn/dawnWindow.hpp>
#include <dawn/dawnDevice.hpp>

namespace gfx
{
	void DawnImguiRenderer::Init()
	{
		DawnDevice* dImpl = (DawnDevice*)Device::instance;
		DawnWindow* wImpl = (DawnWindow*)Window::instance;

		wgpu::Device device = dImpl->GetDawnDevice();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOther(wImpl->GetNativeWindow(), true);

		ImGui_ImplWGPU_InitInfo init_info;
		init_info.Device = device.MoveToCHandle();
		init_info.NumFramesInFlight = 3;
		init_info.RenderTargetFormat = WGPUTextureFormat_RGBA8Unorm;
		init_info.DepthStencilFormat = WGPUTextureFormat_Depth32Float;
		ImGui_ImplWGPU_Init(&init_info);
	}

	void DawnImguiRenderer::Begin()
	{
		ImGui_ImplWGPU_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void DawnImguiRenderer::End()
	{
		ImGui::Render();

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		// Update and Render additional Platform Windows
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}
}