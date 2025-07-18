#include <dawn/frameworks/imgui/imgui_setup.h> 
#include <dawn/dawnWindow.hpp>
#include <dawn/dawnDevice.hpp>

void gfx::UI::IMGUI::SetupIMGUI()
{
    DawnDevice* dImpl = (DawnDevice*)Device::instance;
    DawnWindow* wImpl = (DawnWindow*)Window::instance; 

    wgpu::Device device = dImpl->GetDawnDevice();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOther(wImpl->GetNativeWindow(), true);
#ifdef __EMSCRIPTEN__
    ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
    ImGui_ImplWGPU_InitInfo init_info;
    init_info.Device = device.MoveToCHandle();
    init_info.NumFramesInFlight = 1;
    init_info.RenderTargetFormat = static_cast<WGPUTextureFormat>(wImpl->GetDawnSurfaceCapabilities().formats[0]);
    init_info.DepthStencilFormat = WGPUTextureFormat_Undefined;
    ImGui_ImplWGPU_Init(&init_info);
}
