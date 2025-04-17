#include <dawn/dawnEnums.hpp>
#include <dawn/dawnDevice.hpp>
#include <dawn/resources/dawnSampler.hpp>

namespace gfx
{
	DawnSampler::DawnSampler()
		: s_Sampler(nullptr)
	{
	}

	DawnSampler::DawnSampler(const SamplerDescriptor& desc)
	{
		DawnDevice* deviceInstance = (DawnDevice*)Device::instance;
		wgpu::Device device = deviceInstance->GetDawnDevice();

		wgpu::MipmapFilterMode mipMap = desc.filters.mip == Filter::NEAREST ? wgpu::MipmapFilterMode::Nearest : wgpu::MipmapFilterMode::Linear;

		wgpu::SamplerDescriptor wdesc;
		wdesc.addressModeU = DecodeWarpType(desc.wrap);
		wdesc.addressModeV = DecodeWarpType(desc.wrap);
		wdesc.addressModeW = DecodeWarpType(desc.wrap);
		wdesc.magFilter = DecodeFilterModeType(desc.filters.mag);
		wdesc.minFilter = DecodeFilterModeType(desc.filters.min);
		wdesc.mipmapFilter = mipMap;
		wdesc.lodMaxClamp = desc.maxMip;
		wdesc.lodMinClamp = desc.minMip;
		wdesc.compare = DecodeCompareType(desc.compareType);
		wdesc.maxAnisotropy = 1;

		s_Sampler = device.CreateSampler(&wdesc);
	}

	void gfx::DawnSampler::Destroy()
	{
		s_Sampler = nullptr;
	}
}
