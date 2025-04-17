#ifndef __COMMANDBUFFER_HPP__
#define __COMMANDBUFFER_HPP__

#include <utilities/handle.hpp>
#include <renderer/resources/frameBuffer.hpp>
#include <renderer/resources/renderPass.hpp>
#include <renderer/render/renderPassRenderer.hpp>

namespace gfx
{
    class CommandBuffer
    {
    public:
        virtual ~CommandBuffer() = default;
        
        // TODO: assert false;
        virtual RenderPassRenderer* BeginRenderPass(utils::Handle<RenderPass> renderPass, utils::Handle<FrameBuffer> frameBuffer)
        {
            return nullptr;
        }

        virtual RenderPassRenderer* BeginSurfacePass(utils::Handle<RenderPass> renderPass)
        {
            return nullptr;
        }

        virtual void EndCommandRecording(const RenderPassRenderer* passRenderer) 
        {
            return;
        }

        virtual void Submit()
        {
            return;
        }
    };
}

#endif
