#include <dawn/resources/dawnShader.hpp>
#include <dawn/resources/dawnResourceManager.hpp>
#include <dawn/dawnDevice.hpp>
#include <assert.hpp>

#include <shaderc/shaderc.hpp>
#include <tint/tint.h>

#include <filesystem>
#include <sstream>

namespace gfx
{
	DawnShader::DawnShader()
		:	s_VS(nullptr), s_PS(nullptr), s_CP(nullptr), s_Pipeline(nullptr), s_Compute(nullptr), s_PipelineType(gfx::ShaderPipelineType::GRAPHICS)
	{
	}

	DawnShader::DawnShader(const ShaderDescriptor& desc)
	{
		DawnDevice* dInstance = (DawnDevice*)Device::instance;
		wgpu::Device device = dInstance->GetDawnDevice();

		DawnResourceManager* rm = (DawnResourceManager*)ResourceManager::instance;

		shaderc::Compiler spirvCompiler;
		shaderc::CompileOptions spirvOptions;

		spirvOptions.SetOptimizationLevel(shaderc_optimization_level_performance);
		
		// VS compilation
		if (desc.VS.enabled)
		{
			shaderc::SpvCompilationResult module = spirvCompiler.CompileGlslToSpv(
				reinterpret_cast<const char*>(desc.VS.sourceCode.data()),
				shaderc_vertex_shader,
				std::filesystem::current_path().string().c_str(),
				spirvOptions
			);

			std::stringstream out;
			out << "Shader compilation error: " << module.GetErrorMessage() << std::endl;
			GFX_ASSERT(module.GetCompilationStatus() == shaderc_compilation_status_success, out.str());

			std::vector<uint32_t> VSspirv = { module.cbegin(), module.cend() };

			tint::Program program = tint::spirv::reader::Read(VSspirv);
			auto result = tint::wgsl::writer::Generate(program, tint::wgsl::writer::Options());

			wgpu::ShaderSourceWGSL VSwgsl;
			VSwgsl.code = result.Get().wgsl.c_str();
			wgpu::ShaderModuleDescriptor descriptor;
			descriptor.nextInChain = &VSwgsl;
			s_VS = device.CreateShaderModule(&descriptor);
		}

		// PS compilation
		if (desc.PS.enabled)
		{
			shaderc::SpvCompilationResult module = spirvCompiler.CompileGlslToSpv(
				reinterpret_cast<const char*>(desc.PS.sourceCode.data()),
				shaderc_fragment_shader,
				std::filesystem::current_path().string().c_str(),
				spirvOptions
			);

			std::stringstream out;
			out << "Shader compilation error: " << module.GetErrorMessage() << std::endl;
			GFX_ASSERT(module.GetCompilationStatus() == shaderc_compilation_status_success, out.str());

			std::vector<uint32_t> PSspirv = { module.cbegin(), module.cend() };

			tint::Program program = tint::spirv::reader::Read(PSspirv);
			auto result = tint::wgsl::writer::Generate(program, tint::wgsl::writer::Options());

			wgpu::ShaderSourceWGSL PSwgsl;
			PSwgsl.code = result.Get().wgsl.c_str();
			wgpu::ShaderModuleDescriptor descriptor;
			descriptor.nextInChain = &PSwgsl;
			s_PS = device.CreateShaderModule(&descriptor);
		}
		
		// Pipeline layout creation
		wgpu::BindGroupLayout bgls[] = { nullptr, nullptr, nullptr, nullptr };
		wgpu::PipelineLayoutDescriptor pipelineDesc = {};
		{
			DawnBindGroupLayout* bgl0 = rm->Get(desc.bindLayouts[0]);
			if (bgl0)
				bgls[0] = bgl0->s_BindGroupLayout;
			DawnBindGroupLayout* bgl1 = rm->Get(desc.bindLayouts[1]);
			if (bgl1)
				bgls[1] = bgl1->s_BindGroupLayout;
			DawnBindGroupLayout* bgl2 = rm->Get(desc.bindLayouts[2]);
			if (bgl2)
				bgls[2] = bgl2->s_BindGroupLayout;
			DawnBindGroupLayout* bgl3 = rm->Get(desc.bindLayouts[3]);
			if (bgl3)
				bgls[3] = bgl3->s_BindGroupLayout;

			pipelineDesc.bindGroupLayouts = bgls;
			pipelineDesc.bindGroupLayoutCount = 4;

			pipelineDesc.immediateDataRangeByteSize = kMaxPushConstantByteRange;
		}
		wgpu::PipelineLayout pipelineLayout = device.CreatePipelineLayout(&pipelineDesc);

		s_PipelineType = desc.type;

		// Graphics state 
		if (s_PipelineType == gfx::ShaderPipelineType::GRAPHICS)
		{
			wgpu::RenderPipelineDescriptor wgpuDesc = {};

			wgpuDesc.layout = pipelineLayout;

			struct VertexBinding
			{
				std::vector<wgpu::VertexAttribute> attributes;
				wgpu::VertexBufferLayout buffer;
			};

			std::vector<VertexBinding> vBindings;
			std::vector<wgpu::VertexBufferLayout> wgpuBuffers;

			// VS state
			{
				if (desc.VS.enabled)
				{
					vBindings.resize(desc.graphicsState.vertexBufferBindings.size());
					wgpuBuffers.resize(desc.graphicsState.vertexBufferBindings.size());
						
					int iBuffer = 0;
					int iShaderLocation = 0;
					for (const auto& vBuffer : desc.graphicsState.vertexBufferBindings)
					{
						vBindings[iBuffer].buffer.arrayStride = vBuffer.byteStride;
						vBindings[iBuffer].buffer.stepMode = wgpu::VertexStepMode::Vertex;
						vBindings[iBuffer].buffer.attributeCount = vBuffer.attributes.size();
						vBindings[iBuffer].attributes.resize(vBuffer.attributes.size());

						int iAttribute = 0;
						for (const auto& bAttribute : vBuffer.attributes)
						{
							vBindings[iBuffer].attributes[iAttribute].format = gfx::DecodeVertexFormatType(bAttribute.format);
							vBindings[iBuffer].attributes[iAttribute].offset = bAttribute.byteOffset;
							vBindings[iBuffer].attributes[iAttribute].shaderLocation = iShaderLocation;
							++iShaderLocation;
							++iAttribute;
						} 

						vBindings[iBuffer].buffer.attributes = vBindings[iBuffer].attributes.data();
						wgpuBuffers[iBuffer] = std::move(vBindings[iBuffer].buffer); 
						++iBuffer;
					} 

					wgpuDesc.vertex.buffers = wgpuBuffers.data();
					wgpuDesc.vertex.bufferCount = wgpuBuffers.size();

					wgpuDesc.vertex.module = s_VS;
				}
			}

			// Primitive state
			{
				wgpuDesc.primitive.topology = wgpu::PrimitiveTopology::TriangleList;
				wgpuDesc.primitive.stripIndexFormat = wgpu::IndexFormat::Undefined;
				wgpuDesc.primitive.frontFace = wgpu::FrontFace::CCW;
				wgpuDesc.primitive.cullMode = wgpu::CullMode::None;
			}

			// MultiSample state
			{
				wgpuDesc.multisample.count = 1;
				wgpuDesc.multisample.mask = 0xFFFFFFFF;
				wgpuDesc.multisample.alphaToCoverageEnabled = false;
			}

			DawnRenderPassLayout* rpl = rm->Get(desc.graphicsState.renderPassLayout);
			if (rpl)
			{
				// Depth state
				{
					if (rpl->s_DepthEnabled)
					{
						s_DepthState.depthWriteEnabled = rpl->s_DepthEnabled;
						s_DepthState.format = rpl->s_DepthFormat;
						s_DepthState.depthCompare = gfx::DecodeCompareType(desc.graphicsState.depthTest);

						wgpuDesc.depthStencil = &s_DepthState;
					}
				}

				// Fragment state
				{
					if (desc.PS.enabled)
					{
						s_FragmentState.module = s_PS;
						for (int i = 0; i < rpl->s_ColorTargetCount; ++i)
						{
							rpl->s_ColorTargets[i].blend = &rpl->s_ColorBlends[i];
						}

						s_FragmentState.targetCount = rpl->s_ColorTargetCount;
						s_FragmentState.targets = rpl->s_ColorTargets;

						wgpuDesc.fragment = &s_FragmentState;
					}
				}
			}

			s_Pipeline = device.CreateRenderPipeline(&wgpuDesc);
		}
	}

	void DawnShader::Destroy()
	{
		s_PS = nullptr;
		s_CP = nullptr;
		s_VS = nullptr;
		s_Pipeline = nullptr;
		s_Compute = nullptr;
	}
}
