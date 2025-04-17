#ifndef __DAWN_RENDER_PASS_HPP__
#define __DAWN_RENDER_PASS_HPP__

#include <platform/dawn/dawnEnums.hpp>
#include <platform/dawn/dawnCommon.hpp>
#include <renderer/resources/renderPass.hpp>

namespace gfx
{
	class DawnRenderPass
	{
	public:
		DawnRenderPass();
		DawnRenderPass(const RenderPassDescriptor& desc);
		void Destroy();

	public:
        bool s_DepthEnabled = false;
		uint8_t s_ColorAttachmentCount = 0;
		wgpu::RenderPassColorAttachment s_ColorAttachments[kMaxColorAttachments];
		wgpu::RenderPassDepthStencilAttachment s_DepthAttachment;

	};
}

#endif // !__DAWN_RENDER_PASS_HPP__
