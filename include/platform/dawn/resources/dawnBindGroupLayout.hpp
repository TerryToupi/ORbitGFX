#ifndef __DAWN_BIND_GROUP_LAYOUT_HPP__
#define __DAWN_BIND_GROUP_LAYOUT_HPP__ 

#include <platform/dawn/dawnEnums.hpp>
#include <platform/dawn/dawnCommon.hpp>
#include <renderer/resources/bindGroupLayout.hpp>

namespace gfx
{
	class DawnBindGroupLayout
	{
	public:
		DawnBindGroupLayout();
		DawnBindGroupLayout(const BindGroupLayoutDescriptor& desc);
		void Destroy();

	public:
		wgpu::BindGroupLayout s_BindGroupLayout;
	};
}

#endif // !__DAWN_BIND_GROUP_LAYOUT_HPP__
