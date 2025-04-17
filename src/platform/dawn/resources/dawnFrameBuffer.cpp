#include <platform/dawn/resources/dawnFrameBuffer.hpp>
#include <platform/dawn/resources/dawnResourceManager.hpp>
#include <platform/dawn/dawnDevice.hpp>

namespace gfx
{
    DawnFrameBuffer::DawnFrameBuffer()
    {
        for (int i = 0; i < kMaxColorAttachments; ++i)
        {
            s_ColorAttachments[i] = nullptr;
        }
        
        s_DepthAttachment = nullptr;
    }

    DawnFrameBuffer::DawnFrameBuffer(const gfx::FrameBufferDescriptor& desc)
    {
        DawnResourceManager* rm = (DawnResourceManager*)ResourceManager::instance;
        DawnDevice* deviceInsance = (DawnDevice*)Device::instance;
        wgpu::Device device = deviceInsance->GetDawnDevice();
      
        const DawnRenderPass* renderPass = rm->Get(desc.renderPass);
        if (!renderPass) 
        {
            //TODO: assert
            return;
        }
        
        s_DepthAttachment = nullptr;
        const DawnTexture* depth = rm->Get(desc.depthTarget.depth);
        if (depth && renderPass->s_DepthEnabled)
        {
            s_DepthAttachment = depth->s_TextureViews[desc.depthTarget.viewIndex];
        }

        if (desc.colorTargets.size() > kMaxColorAttachments)
            // TODO: assert false;
            return;
        
        uint32_t index = 0;
        for (const auto& target : desc.colorTargets)
        {
            s_ColorAttachments[index] = nullptr;
            const DawnTexture* texture = rm->Get(target.target);
            if (texture)
            {
                s_ColorAttachments[index] = texture->s_TextureViews[target.viewIndex];
                ++index;
            }
        }
        s_ColorAttachmentCount = index;
    }

    void DawnFrameBuffer::Destroy()
    {
        s_DepthAttachment = nullptr;
        
        for (int i = 0; i < kMaxColorAttachments; ++i)
        {
            s_ColorAttachments[i] = nullptr;
        }
    }
}
