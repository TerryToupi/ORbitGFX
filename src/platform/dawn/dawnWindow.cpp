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
        
        m_Data.surface = wgpu::glfw::CreateSurfaceForWindow(device->GetDawnInstance(), m_Window);

        m_Data.surface.GetCapabilities(device->GetDawnAdapter(), &m_Data.surfaceCapabilities);
        wgpu::SurfaceConfiguration config = {};

        config.device = device->GetDawnDevice();
        config.format = m_Data.surfaceCapabilities.formats[0];
        config.width = m_WindowConfig.width;
        config.height = m_WindowConfig.height; 
        config.presentMode = wgpu::PresentMode::Immediate;

        m_SurfaceFormat = EncodeTextureFormatType(m_Data.surfaceCapabilities.formats[0]);

        m_Data.surface.Configure(&config);

        glfwSetWindowUserPointer(m_Window, &m_Data);
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int Width, int Height) {
            DawnDevice* device = (DawnDevice*)Device::instance;
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            data.surface.Unconfigure();

			data.surface.GetCapabilities(device->GetDawnAdapter(), &data.surfaceCapabilities);
			wgpu::SurfaceConfiguration config = {};

			config.device = device->GetDawnDevice();
			config.format = data.surfaceCapabilities.formats[0];
			config.width = Width;
			config.height = Height; 
			config.presentMode = wgpu::PresentMode::Immediate;

			data.surface.Configure(&config);

            data.width = Width;
            data.height = Height;
            });
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
            glfwPollEvents();
            func();
            m_Data.surface.Present();
        }
    }

    gfx::TextureFormat DawnWindow::GetSurfaceFormat()
    {
        return m_SurfaceFormat;
    }

    void DawnWindow::GetWindowSize(int* width, int* heigh)
    { 
        glfwGetWindowSize(m_Window, width, heigh);
    }

    bool DawnWindow::GetKey(Key key)
    {
        if (glfwGetKey(m_Window, static_cast<int>(key)) == GLFW_PRESS)
            return true;

        return false;
    }

    bool DawnWindow::GetMouseButton(Button button)
    {
        if (glfwGetMouseButton(m_Window, static_cast<int>(button)) == GLFW_PRESS)
            return true;

        return false;
    }

    void DawnWindow::GetMousePos(double* x, double* y)
    { 
        glfwGetCursorPos(m_Window, x, y);
    }

    const wgpu::Surface& DawnWindow::GetDawnSurface()
    { 
        return m_Data.surface;
    } 

    const wgpu::SurfaceCapabilities& DawnWindow::GetDawnSurfaceCapabilities()
    { 
        return m_Data.surfaceCapabilities;
    }
}
