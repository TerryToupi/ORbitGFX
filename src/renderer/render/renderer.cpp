#include <renderer/render/renderer.hpp> 

#include <platform/dawn/dawnDevice.hpp>
#include <platform/dawn/dawnWindow.hpp> 
#include <platform/dawn/resources/dawnResourceManager.hpp>
#include <platform/dawn/render/dawnRenderer.hpp>

namespace gfx
{
    void Renderer::INIT()
    {
        gfx::Device::instance = new gfx::DawnDevice();
        gfx::ResourceManager::instance = new gfx::DawnResourceManager();
        gfx::Window::instance = new gfx::DawnWindow();
        gfx::Renderer::instance = new gfx::DawnRenderer();

        gfx::Device::instance->Init();
        gfx::ResourceManager::instance->Init();
        gfx::Window::instance->Init({
            .name = "window",
            .width = 1024,
            .height = 720
            });
    }

    void Renderer::SHUTDOWN()
    {
        gfx::ResourceManager::instance->ShutDown();
        gfx::Window::instance->ShutDown();
        gfx::Device::instance->ShutDown();
    }
}