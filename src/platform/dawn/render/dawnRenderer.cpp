#include <dawn/render/dawnRenderer.hpp>
#include <dawn/dawnDevice.hpp>
#include <assert.hpp>

namespace gfx
{
	CommandBuffer* DawnRenderer::BeginCommandRecording(gfx::CommandBufferType type)
	{
		DawnDevice* deviceImp = (DawnDevice*)Device::instance;
		wgpu::Device device = deviceImp->GetDawnDevice();

		switch (type)
		{
		case gfx::CommandBufferType::OFFSCREEN:
			m_OffScreenCB.m_CommandEncoder = device.CreateCommandEncoder();
			return static_cast<CommandBuffer*>(&m_OffScreenCB);
			break;

		case gfx::CommandBufferType::MAIN:
			m_MainCB.m_CommandEncoder = device.CreateCommandEncoder();
			return static_cast<CommandBuffer*>(&m_MainCB);
			break;
		}

		return nullptr;
	}

	void DawnRenderer::Init()
	{
	}

	void DawnRenderer::ShutDown()
	{
	}
}
