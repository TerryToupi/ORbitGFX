#ifndef __DAWN_RENDER_PASS_HPP__
#define __DAWN_RENDER_PASS_HPP__

#include <dawn/dawnEnums.hpp>
#include <dawn/dawnCommon.hpp>

#include <resources/renderPass.hpp>

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
		wgpu::RenderPassColorAttachment s_ColorAttachments[8u];
		wgpu::RenderPassDepthStencilAttachment s_DepthAttachment;

	};
}

#endif // !__DAWN_RENDER_PASS_HPP__
