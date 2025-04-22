#include <dawn/render/dawnRenderer.hpp>
#include <dawn/dawnDevice.hpp>

namespace gfx
{
	RenderPassRenderer* DawnRenderer::RequestPassRenderer()
	{
		DawnDevice* deviceInstance = (DawnDevice*)Device::instance;
		wgpu::Device device = deviceInstance->GetDawnDevice();

		m_RenderPassRenderer.m_Encoder = device.CreateCommandEncoder();

		return static_cast<RenderPassRenderer*>(&m_RenderPassRenderer);
	}

	CommandBuffer* DawnRenderer::BeginCommandRecording()
	{
		return static_cast<CommandBuffer*>(&m_mainBuffer);
	}

	void DawnRenderer::Init()
	{
	}

	void DawnRenderer::ShutDown()
	{
	}
}
