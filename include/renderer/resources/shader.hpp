#ifndef __SHADER_HPP__ 
#define __SHADER_HPP__ 

#include <string>
#include <vector>

#include <span.hpp>
#include <handle.hpp>
#include <enums.hpp>
#include <resources/bindGroupLayout.hpp>
#include <resources/renderPassLayout.hpp>

namespace gfx
{
	class Shader; 

	struct ShaderDescriptor
	{
		struct ShaderStage 
		{
			//TODO: change to remove the compilation stage to the loader
			//std::vector<uint8_t>& byteCode; // Bytecode for the shader stage
			bool enabled = true;
			std::string sourceCode;
			std::string entryFunc;         // Entry function name
		};

		struct VertexAttribute 
		{
			uint32_t byteOffset;
			gfx::VertexFormat format;
		};

		struct VertexBufferBinding 
		{
			uint32_t byteStride;
			std::vector<VertexAttribute> attributes;
		};

		struct GraphicsState 
		{ 
			gfx::Compare depthCompare = gfx::Compare::UNDEFINED;
			std::vector<VertexBufferBinding> vertexBufferBindings;
			utils::Handle<RenderPassLayout> renderPassLayout;
		};

		ShaderPipelineType type = ShaderPipelineType::GRAPHICS;
		ShaderStage VS; // Vertex Shader
		ShaderStage PS; // Pixel Shader
		GraphicsState graphicsState;
		utils::Span<utils::Handle<BindGroupLayout>> bindLayouts;
	};
}

#endif // !__SHADER_HPP__ 
