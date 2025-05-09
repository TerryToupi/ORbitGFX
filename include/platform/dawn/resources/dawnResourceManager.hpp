#ifndef __DAWN_RESOURCE_MANAGER_HPP__ 
#define __DAWN_RESOURCE_MANAGER_HPP__ 

#include <pool.hpp>

#include <resources/resourceManger.hpp> 

#include <dawn/resources/dawnBindGroup.hpp>
#include <dawn/resources/dawnBindGroupLayout.hpp>
#include <dawn/resources/dawnBuffer.hpp>
#include <dawn/resources/dawnRenderPass.hpp>
#include <dawn/resources/dawnRenderPassLayout.hpp>
#include <dawn/resources/dawnSampler.hpp>
#include <dawn/resources/dawnShader.hpp>
#include <dawn/resources/dawnTexture.hpp>
#include <dawn/resources/dawnFrameBuffer.hpp>

namespace gfx
{ 
	class DawnResourceManager : public ResourceManager
	{
	public: 
		virtual void Init() override {};
		virtual void ShutDown() override {};

		virtual utils::Handle<Shader>			Create(const gfx::ShaderDescriptor& desc) override;
		virtual utils::Handle<BindGroup>		Create(const gfx::BindGroupDescriptor& desc) override;
		virtual utils::Handle<BindGroupLayout>	Create(const gfx::BindGroupLayoutDescriptor& desc) override;
		virtual utils::Handle<Texture>			Create(const gfx::TextureDescriptor& desc) override;
		virtual utils::Handle<Sampler>			Create(const gfx::SamplerDescriptor& desc) override;
		virtual utils::Handle<Buffer>			Create(const gfx::BufferDescriptor& desc) override;
		virtual utils::Handle<RenderPass>		Create(const gfx::RenderPassDescriptor& desc) override;
        virtual utils::Handle<RenderPassLayout> Create(const gfx::RenderPassLayoutDescriptor& desc) override;
        virtual utils::Handle<FrameBuffer>      Create(const gfx::FrameBufferDescriptor& desc) override;

		virtual void Remove(utils::Handle<Shader> handle) override;
		virtual void Remove(utils::Handle<BindGroup> handle) override;
		virtual void Remove(utils::Handle<BindGroupLayout> handle) override;
		virtual void Remove(utils::Handle<Texture> handle) override;
		virtual void Remove(utils::Handle<Sampler> handle) override;
		virtual void Remove(utils::Handle<Buffer> handle) override;
		virtual void Remove(utils::Handle<RenderPass> handle) override;
        virtual void Remove(utils::Handle<RenderPassLayout> handle) override;
        virtual void Remove(utils::Handle<FrameBuffer> handle) override;

		utils::Handle<Shader>			Add(const DawnShader& shader);
		utils::Handle<BindGroup>		Add(const DawnBindGroup& bindGroup);
		utils::Handle<BindGroupLayout>	Add(const DawnBindGroupLayout& bindGroupLayout);
		utils::Handle<Texture>			Add(const DawnTexture& texture);
		utils::Handle<Sampler>			Add(const DawnSampler& sampler);
		utils::Handle<Buffer>			Add(const DawnBuffer& buffer);
		utils::Handle<RenderPass>		Add(const DawnRenderPass& renderPass);
        utils::Handle<RenderPassLayout> Add(const DawnRenderPassLayout& renderPassLayout);
        utils::Handle<FrameBuffer>      Add(const DawnFrameBuffer& frameBuffer);

		DawnShader*				Get(utils::Handle<Shader> handle);
		DawnBindGroup*			Get(utils::Handle<BindGroup> handle);
		DawnBindGroupLayout*	Get(utils::Handle<BindGroupLayout> handle);
		DawnTexture*			Get(utils::Handle<Texture> handle);
		DawnSampler*			Get(utils::Handle<Sampler> handle);
		DawnBuffer*				Get(utils::Handle<Buffer> handle);
		DawnRenderPass*			Get(utils::Handle<RenderPass> handle);
        DawnRenderPassLayout*   Get(utils::Handle<RenderPassLayout> handle);
        DawnFrameBuffer*        Get(utils::Handle<FrameBuffer> handle);

	private: 
		utils::Pool<DawnShader, Shader> m_Shaders{ 32u, "Shaders" };
		utils::Pool<DawnBindGroup, BindGroup> m_BindGroups{ 32u, "BindGroups" };
		utils::Pool<DawnBindGroupLayout, BindGroupLayout> m_BindGroupLayouts{ 32u, "BindGroupLayouts" };
		utils::Pool<DawnTexture, Texture> m_Textures{ 32u, "Textures" };
		utils::Pool<DawnSampler, Sampler> m_Samplers{ 32u, "Samplers" };
		utils::Pool<DawnBuffer, Buffer> m_Buffers{ 32u, "Buffers" };
		utils::Pool<DawnRenderPass, RenderPass> m_RenderPasses{ 32u, "RenderPasses" };
        utils::Pool<DawnRenderPassLayout, RenderPassLayout> m_RenderPassLayouts{ 32u, "RenderPassLayouts" };
        utils::Pool<DawnFrameBuffer, FrameBuffer> m_FrameBuffers{ 32u, "FrameBuffers" };

	};
}

#endif // !__DAWN_RESOURCE_MANAGER_HPP__ 
