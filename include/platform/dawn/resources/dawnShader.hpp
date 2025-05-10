#ifndef __DAWN_SHADER_HPP__
#define __DAWN_SHADER_HPP__

#include <dawn/dawnEnums.hpp>
#include <dawn/dawnCommon.hpp>

#include <resources/shader.hpp>

namespace gfx
{
	class DawnShader
	{ 
	public: 
		DawnShader();
		DawnShader(const ShaderDescriptor& desc);
		void Destroy();

	public:
		gfx::ShaderPipelineType s_PipelineType;

		wgpu::ShaderModule s_VS;
		wgpu::ShaderModule s_PS;
		wgpu::ShaderModule s_CP;

		// graphics pipeline
		wgpu::RenderPipeline s_Pipeline; 
		wgpu::DepthStencilState s_DepthState;
		wgpu::FragmentState s_FragmentState;

		wgpu::ComputePipeline s_Compute;
	};
}

#endif // !1
