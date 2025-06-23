#include <dawn/dawnWindow.hpp>
#include <dawn/dawnDevice.hpp>
#include <dawn/dawnEnums.hpp>

#include <assert.hpp>

namespace gfx
{
    void DawnWindow::Init(const WindowDescriptor& desc)
    { 
        m_WindowConfig = desc;

        DawnDevice* device = (DawnDevice*)Device::instance;
        
        if (!glfwInit())
            GFX_ASSERT(false, "GFLW failed to initialize!");

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        m_Window = glfwCreateWindow(m_WindowConfig.width, m_WindowConfig.height, m_WindowConfig.name.c_str(), nullptr, nullptr);
        GFX_ASSERT(m_Window != nullptr, "Unable to fetch GLFW window!");
        
        m_Surface = wgpu::glfw::CreateSurfaceForWindow(device->GetDawnInstance(), m_Window);

        m_Surface.GetCapabilities(device->GetDawnAdapter(), &m_SurfaceCapabilities);
        wgpu::SurfaceConfiguration config = {};

        config.device = device->GetDawnDevice();
        config.format = m_SurfaceCapabilities.formats[0];
        config.width = m_WindowConfig.width;
        config.height = m_WindowConfig.height; 
        config.presentMode = wgpu::PresentMode::Immediate;

        m_SurfaceFormat = EncodeTextureFormatType(m_SurfaceCapabilities.formats[0]);

        m_Surface.Configure(&config);
    } 

    void DawnWindow::ShutDown()
    { 
        glfwDestroyWindow(m_Window); 
        glfwTerminate();
    } 

    void DawnWindow::Run(const GameLoop& func)
    { 
        //// main loop
        while (!glfwWindowShouldClose(m_Window))
        { 
            func();
            m_Surface.Present();
            glfwPollEvents();
        }
    }

    gfx::TextureFormat DawnWindow::GetSurfaceFormat()
    {
        return m_SurfaceFormat;
    }

    bool DawnWindow::GetKey(Key key)
    {
        if (glfwGetKey(m_Window, static_cast<int>(key)) == GLFW_PRESS)
            return true;

        return false;
    }

    void DawnWindow::GetMousePos(double* x, double* y)
    { 
        glfwGetCursorPos(m_Window, x, y);
    }

    const wgpu::Surface& DawnWindow::GetDawnSurface()
    { 
        return m_Surface;
    } 

    const wgpu::SurfaceCapabilities& DawnWindow::GetDawnSurfaceCapabilities()
    { 
        return m_SurfaceCapabilities;
    }
}
