#ifndef __SAMPLER_HPP__ 
#define __SAMPLER_HPP__ 

#include <enums.hpp>

namespace gfx
{
	class Sampler;
	
	struct SamplerDescriptor
	{
		struct Filters
		{
			Filter min = Filter::NEAREST;
			Filter mag = Filter::NEAREST;
			Filter mip = Filter::NEAREST;
		};

		Filters filters = {};
        Compare compareType = Compare::UNDEFINED;
		Wrap wrap = Wrap::REPEAT;
		float minMip = 0.0f;
		float maxMip = 32.0f;
	};
}

#endif // !__SAMPLER_HPP__ 
