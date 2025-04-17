#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <string>
#include <functional>
#include <enums.hpp>

namespace gfx
{ 
    struct WindowDescriptor
    {
        std::string name;
        uint16_t width; 
        uint16_t height;
    };

    class Window
    {
    public: 
        using GameLoop = std::function<void()>;

        static inline Window* instance = nullptr;
        
        virtual void Init(const WindowDescriptor& desc) = 0;
        virtual void ShutDown() = 0;
        virtual void Run(const GameLoop& func) = 0; 

        virtual gfx::TextureFormat GetSurfaceFormat() = 0;

    protected:
        WindowDescriptor m_WindowConfig;
        gfx::TextureFormat m_SurfaceFormat = gfx::TextureFormat::UNDEFINED;

    };
}

#endif
