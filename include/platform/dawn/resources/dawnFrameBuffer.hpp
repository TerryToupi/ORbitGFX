#ifndef __DAWN_FRAMEBUFFER_HPP__
#define __DAWN_FRAMEBUFFER_HPP__

#include <dawn/dawnEnums.hpp>
#include <dawn/dawnCommon.hpp>

#include <resources/frameBuffer.hpp>


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
