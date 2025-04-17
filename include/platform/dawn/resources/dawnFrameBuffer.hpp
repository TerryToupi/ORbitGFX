#ifndef __DAWN_FRAMEBUFFER_HPP__
#define __DAWN_FRAMEBUFFER_HPP__

#include <platform/dawn/dawnEnums.hpp>
#include <platform/dawn/dawnCommon.hpp>
#include <renderer/resources/frameBuffer.hpp>


namespace gfx
{
    class DawnFrameBuffer
    {
    public:
        DawnFrameBuffer();
        DawnFrameBuffer(const gfx::FrameBufferDescriptor& desc);
        void Destroy();

    public:
        uint32_t s_ColorAttachmentCount = 0;
        wgpu::TextureView s_ColorAttachments[kMaxColorAttachments];
        wgpu::TextureView s_DepthAttachment;
    };
}

#endif
