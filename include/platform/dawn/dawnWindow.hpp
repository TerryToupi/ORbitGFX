#ifndef __DAWNWINDOW_HPP__
#define __DAWNWINDOW_HPP__

#include <webgpu/webgpu_glfw.h>
#include <GLFW/glfw3.h>

#include <window.hpp>

namespace gfx
{ 
    class DawnWindow : public Window
    {
    public:
        virtual void Init(const WindowDescriptor& desc) override;
        virtual void ShutDown() override;

        virtual void Run(const GameLoop& func) override;

        virtual gfx::TextureFormat GetSurfaceFormat() override;

        virtual void  GetWindowSize(int* width, int* heigh) override;

        virtual bool GetKey(Key key) override;
        virtual void GetMousePos(double* x, double* y) override;
       
        const wgpu::Surface& GetDawnSurface(); 
        const wgpu::SurfaceCapabilities& GetDawnSurfaceCapabilities();

    private:
        GLFWwindow* m_Window;
        wgpu::Surface m_Surface; 
        wgpu::SurfaceCapabilities m_SurfaceCapabilities;
    };
}

#endif
