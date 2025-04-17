#ifndef __RESOURCE_MANAGER_HPP__ 
#define __RESOURCE_MANAGER_HPP__ 

#include <resources/bindGroup.hpp>
#include <resources/bindGroupLayout.hpp>
#include <resources/buffer.hpp>
#include <resources/renderPass.hpp>
#include <resources/sampler.hpp>
#include <resources/shader.hpp>
#include <resources/texture.hpp>
#include <resources/frameBuffer.hpp>
#include <resources/renderPassLayout.hpp>

#include <handle.hpp>
#include <workQueue.hpp>

namespace gfx
{
	class ResourceManager
	{
	public: 
		static inline ResourceManager* instance = nullptr;

		virtual ~ResourceManager() = default;

		virtual void Init() = 0;
		virtual void ShutDown() = 0;
		virtual void Flush() = 0;

		virtual utils::Handle<Shader>			Create(const gfx::ShaderDescriptor& desc) = 0;
		virtual utils::Handle<BindGroup>		Create(const gfx::BindGroupDescriptor& desc) = 0;
		virtual utils::Handle<BindGroupLayout>	Create(const gfx::BindGroupLayoutDescriptor& desc) = 0;
		virtual utils::Handle<Texture>			Create(const gfx::TextureDescriptor& desc) = 0;
		virtual utils::Handle<Sampler>			Create(const gfx::SamplerDescriptor& desc) = 0;
		virtual utils::Handle<Buffer>			Create(const gfx::BufferDescriptor& desc) = 0;
		virtual utils::Handle<RenderPass>		Create(const gfx::RenderPassDescriptor& desc) = 0;
        virtual utils::Handle<RenderPassLayout> Create(const gfx::RenderPassLayoutDescriptor& desc) = 0;
        virtual utils::Handle<FrameBuffer>      Create(const gfx::FrameBufferDescriptor& desc) = 0;

		virtual void Remove(utils::Handle<Shader> handle) = 0;
		virtual void Remove(utils::Handle<BindGroup> handle) = 0;
		virtual void Remove(utils::Handle<BindGroupLayout> handle) = 0;
		virtual void Remove(utils::Handle<Texture> handle) = 0;
		virtual void Remove(utils::Handle<Sampler> handle) = 0;
		virtual void Remove(utils::Handle<Buffer> handle) = 0;
		virtual void Remove(utils::Handle<RenderPass> handle) = 0;
        virtual void Remove(utils::Handle<RenderPassLayout> handle) = 0;
        virtual void Remove(utils::Handle<FrameBuffer> handle) = 0;

	protected:
		utils::WorkQueue m_DeletionQueue;
	};
}

#endif
