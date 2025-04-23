#ifndef __COMMANDBUFFER_HPP__
#define __COMMANDBUFFER_HPP__

#include <handle.hpp>

#include <resources/frameBuffer.hpp>
#include <resources/renderPass.hpp>
#include <render/renderPassRenderer.hpp>
#include <enums.hpp>

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

    public:
        CommandBufferState s_State = CommandBufferState::EMPTY;
    };
}

#endif
