#ifndef __RENDERPASS_RENDERER_HPP__
#define __RENDERPASS_RENDERER_HPP__

#include <utilities/handle.hpp>
#include <renderer/resources/frameBuffer.hpp>
#include <renderer/resources/renderPass.hpp>
#include <renderer/render/drawStream.hpp>

namespace gfx
{
    class RenderPassRenderer
    {
    public:
        virtual ~RenderPassRenderer() = default;
        
        virtual void DrawPass(DrawStream& cmds) {
            exit(1);
        };
    
    public:
        bool s_SurfacePass = false;
        utils::Handle<FrameBuffer> s_FrameBuffer;
        utils::Handle<RenderPass> s_RenderPass;
    };
}

#endif
