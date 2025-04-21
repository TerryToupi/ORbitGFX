#include <render/renderer.hpp> 

#include <dawn/dawnDevice.hpp>
#include <dawn/dawnWindow.hpp> 
#include <dawn/resources/dawnResourceManager.hpp>
#include <dawn/render/dawnRenderer.hpp>

#include <log.hpp>

namespace gfx
{
    void Renderer::INIT()
    {
        diag::Logger::Init();

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

        GFX_TRACE("Renderer status: initialized");
    }

    void Renderer::SHUTDOWN()
    {
        GFX_TRACE("Renderer stattus: shutting down");

        gfx::ResourceManager::instance->ShutDown();
        gfx::Window::instance->ShutDown();
        gfx::Device::instance->ShutDown();
        
        diag::Logger::ShutDown();
    }
}