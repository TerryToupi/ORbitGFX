#ifndef __DAWN_SAMPLER_HPP__
#define __DAWN_SAMPLER_HPP__

#include <platform/dawn/dawnCommon.hpp>
#include <renderer/resources/sampler.hpp>

namespace gfx
{
	class DawnSampler
	{ 
	public:
		DawnSampler();
		DawnSampler(const SamplerDescriptor& desc);
		void Destroy();

	public:
		wgpu::Sampler s_Sampler;
	};
}

#endif // !__DAWN_SAMPLER_HPP__
