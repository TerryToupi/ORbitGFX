#include <dawn/resources/dawnDynamicBuffer.hpp>

namespace gfx
{
    DawnDynamicBuffer::DawnDynamicBuffer()
        :   s_Buffer(nullptr)
    {
    }

    DawnDynamicBuffer::DawnDynamicBuffer(const DynamicBufferDescriptor& desc)
    {
    }

    void DawnDynamicBuffer::Destroy()
    {
        if (s_Buffer != nullptr)
            s_Buffer.Destroy();
    }
}