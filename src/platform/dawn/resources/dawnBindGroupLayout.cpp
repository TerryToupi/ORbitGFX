#include <platform/dawn/resources/dawnBindGroupLayout.hpp>
#include <platform/dawn/dawnDevice.hpp>

namespace gfx
{
	DawnBindGroupLayout::DawnBindGroupLayout()
		:	s_BindGroupLayout(nullptr)
	{
	}

	DawnBindGroupLayout::DawnBindGroupLayout(const BindGroupLayoutDescriptor& desc)
	{
		DawnDevice* deviceInstance = (DawnDevice*)Device::instance;
		wgpu::Device device = deviceInstance->GetDawnDevice();
        
        wgpu::BindGroupLayoutEntry entries[kMaxLayoutBindings];
		wgpu::BindGroupLayoutDescriptor layoutDesc = {};
        
        if ((desc.bufferBindings.size() + desc.textureBindings.size() + desc.samplerBindings.size()) > kMaxLayoutBindings)
        {
            //TODO: assert false
            return;
        }

		int index = 0;
		for (const auto& bufferBinding : desc.bufferBindings)
		{
            entries[index].binding = bufferBinding.slot;
            entries[index].visibility = gfx::DecodeShaderType(bufferBinding.visibility);
            entries[index].buffer.type = gfx::DecodeBufferBindingType(bufferBinding.type);
			++index;
		}
		for (const auto& textureBinding : desc.textureBindings)
		{
            entries[index].binding = textureBinding.slot;
            entries[index].visibility = gfx::DecodeShaderType(textureBinding.visibility);
            entries[index].texture.viewDimension = gfx::DecodeTextureDimentionType(textureBinding.viewDimention);
            entries[index].texture.sampleType = wgpu::TextureSampleType::Float;
			++index;
		}
		for (const auto& samplerBinding : desc.samplerBindings)
		{
            entries[index].binding = samplerBinding.slot;
            entries[index].visibility = gfx::DecodeShaderType(samplerBinding.visibility);
            entries[index].sampler.type = samplerBinding.comparison == true ? wgpu::SamplerBindingType::Comparison : wgpu::SamplerBindingType::Filtering;
			++index;
		}

		layoutDesc.entries = entries;
		layoutDesc.entryCount = index;
		
        s_BindGroupLayout = device.CreateBindGroupLayout(&layoutDesc);
	}

	void DawnBindGroupLayout::Destroy()
	{
        s_BindGroupLayout = nullptr;
	}
}
