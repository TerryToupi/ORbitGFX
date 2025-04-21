#include <dawn/resources/dawnFrameBuffer.hpp>
#include <dawn/resources/dawnResourceManager.hpp>
#include <dawn/dawnDevice.hpp>
#include <assert.hpp>

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
        GFX_ASSERT(renderPass, "Provided Render Pass in Dawn Frame Buffer creation was NULL!");

        
        s_DepthAttachment = nullptr;
        const DawnTexture* depth = rm->Get(desc.depthTarget);
        if (depth && renderPass->s_DepthEnabled)
        {
            s_DepthAttachment = depth->s_Texture.CreateView();
        }

        GFX_ASSERT(desc.colorTargets.size() < kMaxColorAttachments, "Provided color target size in the Dawn Frame Buffer was greated than the max available color attachments!");
        
        uint32_t index = 0;
        for (const auto& target : desc.colorTargets)
        {
            s_ColorAttachments[index] = nullptr;
            const DawnTexture* texture = rm->Get(target);
            if (texture)
            {
                s_ColorAttachments[index] = texture->s_Texture.CreateView();
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
