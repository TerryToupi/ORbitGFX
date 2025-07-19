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

		ImGui::StyleColorsDark();

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