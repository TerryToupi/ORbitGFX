#include <dawn/frameworks/imgui/dawnImguiRenderer.hpp>
#include <dawn/dawnWindow.hpp>
#include <dawn/dawnDevice.hpp>
#include <resources/resourceManger.hpp>

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
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		//ImGui::StyleColorsDark(); 
        
		//custom theme
		ImGuiStyle* style = &ImGui::GetStyle();

		style->WindowMinSize = ImVec2(160, 20);
		style->FramePadding = ImVec2(4, 2);
		style->ItemSpacing = ImVec2(6, 2);
		style->ItemInnerSpacing = ImVec2(6, 4);
		style->Alpha = 0.95f;
		style->WindowRounding = 4.0f;
		style->FrameRounding = 2.0f;
		style->IndentSpacing = 6.0f;
		style->ItemInnerSpacing = ImVec2(2, 4);
		style->ColumnsMinSpacing = 50.0f;
		style->GrabMinSize = 14.0f;
		style->GrabRounding = 16.0f;
		style->ScrollbarSize = 12.0f;
		style->ScrollbarRounding = 16.0f;

		style->Colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
		style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.28f);
		style->Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
		style->Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
		style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style->Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
		style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
		style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.47f);
		style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
		style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
		style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
		style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
		style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
		style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_Header] = ImVec4(0.92f, 0.18f, 0.29f, 0.76f);
		style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
		style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_Separator] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
		style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
		style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
		style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
		style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
		style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
		style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.92f, 0.18f, 0.29f, 0.43f);
		style->Colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.9f);
		//style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.22f, 0.27f, 0.73f);

		ImGui_ImplGlfw_InitForOther(wImpl->GetNativeWindow(), true);

		ImGui_ImplWGPU_InitInfo init_info;
		init_info.Device = device.MoveToCHandle();
		init_info.NumFramesInFlight = 3;
		init_info.RenderTargetFormat = static_cast<WGPUTextureFormat>(wImpl->GetDawnSurfaceCapabilities().formats[0]);
		init_info.DepthStencilFormat = WGPUTextureFormat_Undefined;
		ImGui_ImplWGPU_Init(&init_info); 

		ImguiRenderer::instance->s_RenderPassLayout = gfx::ResourceManager::instance->Create(gfx::RenderPassLayoutDescriptor{
			.colorTargets = {
				{.enabled = true, .format = wImpl->GetSurfaceFormat()}
				}
			});
		ImguiRenderer::instance->s_RenderPass = gfx::ResourceManager::instance->Create(gfx::RenderPassDescriptor{
			.colorTargets = {
				{.loadOp = gfx::LoadOperation::LOAD, .storeOp = gfx::StoreOperation::STORE}
			},
			.layout = ImguiRenderer::instance->s_RenderPassLayout,
			});
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

	void DawnImguiRenderer::ShutDown()
	{
		ImGui_ImplWGPU_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();  

		gfx::ResourceManager::instance->Remove(ImguiRenderer::instance->s_RenderPassLayout);
		gfx::ResourceManager::instance->Remove(ImguiRenderer::instance->s_RenderPass);
	}
}