#include <dawn/resources/dawnRenderPass.hpp>
#include <dawn/resources/dawnResourceManager.hpp>
#include <assert.hpp>

namespace gfx
{
	DawnRenderPass::DawnRenderPass()
	{
		for (int i = 0; i < kMaxColorAttachments; ++i)
		{
			s_ColorAttachments[i] = {};
		}

		s_DepthAttachment = {};
	}

	DawnRenderPass::DawnRenderPass(const RenderPassDescriptor& desc)
	{
        DawnResourceManager* rm = (DawnResourceManager*)ResourceManager::instance;
        
        DawnRenderPassLayout* rpl = rm->Get(desc.layout);
		GFX_ASSERT(rpl, "Provided Render pipeline layout in Dawn Renderpass creation was NULL!");
        
		int index = 0;
		for (const auto& target : desc.colorTargets)
		{
			s_ColorAttachments[index] =
			{
				.loadOp = gfx::DecodeLoadOperationType(target.loadOp),
				.storeOp = gfx::DecodeStoreOperationType(target.storeOp),
				.clearValue = { target.clearColor.r, target.clearColor.g, target.clearColor.b, target.clearColor.a }
			};

			++index;
		}
		s_ColorAttachmentCount = index;
        
        if (rpl->s_DepthEnabled)
        {
            s_DepthAttachment.depthLoadOp = gfx::DecodeLoadOperationType(desc.depthTarget.loadOp);
            s_DepthAttachment.depthStoreOp = gfx::DecodeStoreOperationType(desc.depthTarget.storeOp);
            s_DepthAttachment.depthClearValue = desc.depthTarget.clearZ;
            s_DepthAttachment.stencilLoadOp = gfx::DecodeLoadOperationType(desc.depthTarget.stencilLoadOp);
            s_DepthAttachment.stencilStoreOp = gfx::DecodeStoreOperationType(desc.depthTarget.stencilStoreOp);
        }
        
        s_DepthEnabled = rpl->s_DepthEnabled;
	}

	void DawnRenderPass::Destroy()
	{
	}
}
