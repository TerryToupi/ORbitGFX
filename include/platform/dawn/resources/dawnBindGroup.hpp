#ifndef __DAWN_BIND_GROUP_HPP__
#define __DAWN_BIND_GROUP_HPP__ 

#include <dawn/dawnCommon.hpp>
#include <dawn/dawnEnums.hpp>

#include <resources/bindGroup.hpp>

namespace gfx
{
	class DawnBindGroup
	{
	public:
		DawnBindGroup(); 
		DawnBindGroup(const BindGroupDescriptor& desc);
		void Destroy();

	public:
		wgpu::BindGroup s_BindGroup;
	};
}

#endif // !__DAWN_BIND_GROUP_HPP__
