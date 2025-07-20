#include <dawn/render/dawnRenderer.hpp>
#include <dawn/dawnDevice.hpp>
#include <assert.hpp>

#include <dawn/frameworks/imgui/dawnImguiRenderer.hpp>

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

		case gfx::CommandBufferType::POST:
			m_PostEffectCB.m_CommandEncoder = device.CreateCommandEncoder();
			return static_cast<CommandBuffer*>(&m_PostEffectCB);
			break;
			
		case gfx::CommandBufferType::UI:
			m_UiCB.m_CommandEncoder = device.CreateCommandEncoder();
			return static_cast<CommandBuffer*>(&m_UiCB);
			break;
		}

		return nullptr;
	}

	UniformRingBuffer* DawnRenderer::RequestUniformRingBuffer()
	{
		return &m_PerDrawRingBuffer;
	}

	void DawnRenderer::Init()
	{
		//inirializing uniform ring buffer
		m_PerDrawRingBuffer = UniformRingBuffer(64 * 1024 * 1024);

		//initializing frameworks
		gfx::ImguiRenderer::instance = new gfx::DawnImguiRenderer();

		ImguiRenderer::instance->Init();
	}

	void DawnRenderer::ShutDown()
	{
		gfx::ImguiRenderer::instance->ShutDown();

		m_PerDrawRingBuffer.Destroy();
	}
}
