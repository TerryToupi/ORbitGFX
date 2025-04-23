#ifndef __RENDERPASS_RENDERER_HPP__
#define __RENDERPASS_RENDERER_HPP__

#include <handle.hpp>

#include <resources/frameBuffer.hpp>
#include <resources/renderPass.hpp>
#include <render/drawStream.hpp>

namespace gfx
{
    class CommandBuffer;

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

        CommandBuffer* s_BufferHandle;
    };
}

#endif
