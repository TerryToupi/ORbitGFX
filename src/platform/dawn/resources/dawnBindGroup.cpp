#include <dawn/resources/dawnBindGroup.hpp>
#include <dawn/resources/dawnResourceManager.hpp>
#include <dawn/dawnDevice.hpp>

namespace gfx
{
	DawnBindGroup::DawnBindGroup()
		:	s_BindGroup(nullptr)
	{
	}

	DawnBindGroup::DawnBindGroup(const BindGroupDescriptor& desc)
	{
        DawnDevice* deviceInstance = (DawnDevice*)Device::instance;
        wgpu::Device device = deviceInstance->GetDawnDevice();
        
        DawnResourceManager* rm = (DawnResourceManager*)ResourceManager::instance;
        
        DawnBindGroupLayout* bgl = rm->Get(desc.layout);
        if (!bgl)
            //TODO: assert false;
            return;
       
        wgpu::BindGroupEntry bgEntries[kMaxLayoutBindings];
        wgpu::BindGroupDescriptor bgDescriptor = {};
        
        if ((desc.buffers.size() + desc.textures.size() + desc.samplers.size()) > kMaxLayoutBindings)
            //TODO: assert false;
            return;
        
        bgDescriptor.layout = bgl->s_BindGroupLayout;
        
        uint32_t index = 0;
        for (const auto& buffer : desc.buffers)
        {
            DawnBuffer* b = rm->Get(buffer.buffer);
            if (b)
            {
                bgEntries[index].binding = buffer.slot;
                bgEntries[index].buffer = b->s_Buffer;
                bgEntries[index].size = buffer.range;
                bgEntries[index].offset = buffer.byteOffset;
                ++index;
            }
        }
        for (const auto& texture : desc.textures)
        {
            DawnTexture* t = rm->Get(texture.textureView);
            if (t)
            {
                bgEntries[index].binding = texture.slot;
                bgEntries[index].textureView = t->s_TextureView;
                ++index;
            }
        }
        for (const auto& sampler : desc.samplers)
        {
            DawnSampler* s = rm->Get(sampler.sampler);
            if (s)
            {
                bgEntries[index].binding = sampler.slot;
                bgEntries[index].sampler = s->s_Sampler;
                ++index;
            }
        }
        
        bgDescriptor.entries = bgEntries;
        bgDescriptor.entryCount = index;
        
        s_BindGroup = device.CreateBindGroup(&bgDescriptor);
	}

	void DawnBindGroup::Destroy()
	{
        s_BindGroup = nullptr;
	}
}
