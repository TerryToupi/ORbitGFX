#include <dawn/resources/dawnResourceManager.hpp> 

namespace gfx
{
	utils::Handle<Shader> DawnResourceManager::Create(const ShaderDescriptor& desc)
	{
		return m_Shaders.Insert(DawnShader(desc));
	}

	utils::Handle<BindGroup> DawnResourceManager::Create(const BindGroupDescriptor& desc)
	{
	 	return m_BindGroups.Insert(DawnBindGroup(desc));
	}

	utils::Handle<BindGroupLayout> DawnResourceManager::Create(const BindGroupLayoutDescriptor& desc)
	{
		return m_BindGroupLayouts.Insert(DawnBindGroupLayout(desc));
	}

	utils::Handle<Texture> DawnResourceManager::Create(const TextureDescriptor& desc)
	{
		return m_Textures.Insert(DawnTexture(desc));
	}

	utils::Handle<Sampler> DawnResourceManager::Create(const SamplerDescriptor& desc)
	{
		return m_Samplers.Insert(DawnSampler(desc));
	}

	utils::Handle<Buffer> DawnResourceManager::Create(const BufferDescriptor& desc)
	{
		return m_Buffers.Insert(DawnBuffer(desc));
	}

	utils::Handle<DynamicBuffer> DawnResourceManager::Create(const gfx::DynamicBufferDescriptor& desc)
	{
		return m_DynamicBuffers.Insert(DawnDynamicBuffer(desc));
	}

	utils::Handle<RenderPass> DawnResourceManager::Create(const gfx::RenderPassDescriptor& desc)
	{
		return m_RenderPasses.Insert(DawnRenderPass(desc));
	}

    utils::Handle<RenderPassLayout> DawnResourceManager::Create(const gfx::RenderPassLayoutDescriptor& desc)
    {
        return m_RenderPassLayouts.Insert(DawnRenderPassLayout(desc));
    }

    utils::Handle<FrameBuffer> DawnResourceManager::Create(const gfx::FrameBufferDescriptor& desc)
    {
        return m_FrameBuffers.Insert(DawnFrameBuffer(desc));
    }

	void DawnResourceManager::Remove(utils::Handle<Shader> handle)
	{ 
		DawnShader* shader = m_Shaders.Get(handle);
		if (shader == nullptr)
			return; 

		shader->Destroy();
		m_Shaders.Remove(handle);
	} 

	void DawnResourceManager::Remove(utils::Handle<BindGroup> handle) 
	{
		DawnBindGroup* bindGroup = m_BindGroups.Get(handle);
		if (bindGroup == nullptr)
			return;

		bindGroup->Destroy();
		m_BindGroups.Remove(handle);
	} 

	void DawnResourceManager::Remove(utils::Handle<BindGroupLayout> handle) 
	{ 
		DawnBindGroupLayout* bgl = m_BindGroupLayouts.Get(handle);
		if (bgl == nullptr)
			return;

		bgl->Destroy();
		m_BindGroupLayouts.Remove(handle);
	} 

	void DawnResourceManager::Remove(utils::Handle<Texture> handle) 
	{
		DawnTexture* texture = m_Textures.Get(handle);
		if (texture == nullptr)
			return;

		texture->Destroy();
		m_Textures.Remove(handle);
	} 

	void DawnResourceManager::Remove(utils::Handle<Sampler> handle) 
	{
		DawnSampler* sampler = m_Samplers.Get(handle);
		if (sampler == nullptr)
			return;

		sampler->Destroy();
		m_Samplers.Remove(handle);
	} 

	void DawnResourceManager::Remove(utils::Handle<Buffer> handle) 
	{
		DawnBuffer* buffer = m_Buffers.Get(handle);
		if (buffer == nullptr)
			return;

		buffer->Destroy();
		m_Buffers.Remove(handle);
	} 

	void DawnResourceManager::Remove(utils::Handle<DynamicBuffer> handle)
	{
		DawnDynamicBuffer* buffer = m_DynamicBuffers.Get(handle);
		if (buffer == nullptr)
			return;

		buffer->Destroy();
		m_DynamicBuffers.Remove(handle);
	}

	void DawnResourceManager::Remove(utils::Handle<RenderPass> handle)
	{
		DawnRenderPass* renderPass = m_RenderPasses.Get(handle);
		if (renderPass == nullptr)
			return;

		renderPass->Destroy();
		m_RenderPasses.Remove(handle);
	}

    void DawnResourceManager::Remove(utils::Handle<RenderPassLayout> handle)
    {
		DawnRenderPassLayout* renderPassLayout = m_RenderPassLayouts.Get(handle);
		if (renderPassLayout == nullptr)
			return;

		renderPassLayout->Destroy();
		m_RenderPassLayouts.Remove(handle);
    }

    void DawnResourceManager::Remove(utils::Handle<FrameBuffer> handle)
    {
		DawnFrameBuffer* frameBuffer = m_FrameBuffers.Get(handle);
		if (frameBuffer == nullptr)
			return;

		frameBuffer->Destroy();
		m_FrameBuffers.Remove(handle);
    }

	utils::Handle<Shader> DawnResourceManager::Add(const DawnShader& shader)
	{
		return m_Shaders.Insert(shader);
	}

	utils::Handle<BindGroup> DawnResourceManager::Add(const DawnBindGroup& bindGroup)
	{
		return m_BindGroups.Insert(bindGroup);
	}

	utils::Handle<BindGroupLayout> DawnResourceManager::Add(const DawnBindGroupLayout& bindGroupLayout)
	{
		return m_BindGroupLayouts.Insert(bindGroupLayout);
	}

	utils::Handle<Texture> DawnResourceManager::Add(const DawnTexture& texture)
	{
		return m_Textures.Insert(texture);
	}

	utils::Handle<Sampler> DawnResourceManager::Add(const DawnSampler& sampler)
	{
		return m_Samplers.Insert(sampler);
	}

	utils::Handle<Buffer> DawnResourceManager::Add(const DawnBuffer& buffer)
	{
		return m_Buffers.Insert(buffer);
	}

	utils::Handle<DynamicBuffer> DawnResourceManager::Add(const DawnDynamicBuffer& buffer)
	{
		return m_DynamicBuffers.Insert(buffer);
	}

	utils::Handle<RenderPass> DawnResourceManager::Add(const DawnRenderPass& renderPass)
	{
		return m_RenderPasses.Insert(renderPass);
	}

    utils::Handle<RenderPassLayout> DawnResourceManager::Add(const DawnRenderPassLayout& renderPassLayout)
    {
        return m_RenderPassLayouts.Insert(renderPassLayout);
    }

    utils::Handle<FrameBuffer> DawnResourceManager::Add(const DawnFrameBuffer& frameBuffer)
    {
        return m_FrameBuffers.Insert(frameBuffer);
    }

	DawnShader* DawnResourceManager::Get(utils::Handle<Shader> handle)
	{
		return m_Shaders.Get(handle);
	}

	DawnBindGroup* DawnResourceManager::Get(utils::Handle<BindGroup> handle) 
	{
		return m_BindGroups.Get(handle);
	}

	DawnBindGroupLayout* DawnResourceManager::Get(utils::Handle<BindGroupLayout> handle) 
	{
		return m_BindGroupLayouts.Get(handle);
	}

	DawnTexture* DawnResourceManager::Get(utils::Handle<Texture> handle) 
	{
		return m_Textures.Get(handle);
	}

	DawnSampler* DawnResourceManager::Get(utils::Handle<Sampler> handle) 
	{
		return m_Samplers.Get(handle);
	}

	DawnBuffer* DawnResourceManager::Get(utils::Handle<Buffer> handle) 
	{
		return m_Buffers.Get(handle);
	}

	DawnDynamicBuffer* DawnResourceManager::Get(utils::Handle<DynamicBuffer> handle)
	{
		return m_DynamicBuffers.Get(handle);
	}

	DawnRenderPass* DawnResourceManager::Get(utils::Handle<RenderPass> handle)
	{
		return m_RenderPasses.Get(handle);
	}

    DawnRenderPassLayout* DawnResourceManager::Get(utils::Handle<RenderPassLayout> handle)
    {
        return m_RenderPassLayouts.Get(handle);
    }

    DawnFrameBuffer* DawnResourceManager::Get(utils::Handle<FrameBuffer> handle)
    {
        return m_FrameBuffers.Get(handle);
    }
}
