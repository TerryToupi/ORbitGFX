#ifndef __DAWN_RENDERER_HPP__
#define __DAWN_RENDERER_HPP__

#include<deque>
#include<functional>

#include <dawn/dawnCommon.hpp>
#include <dawn/render/dawnCommandBuffer.hpp>
#include <dawn/render/dawnRenderPassRenderer.hpp>
#include <render/renderer.hpp>
#include <render/drawStream.hpp>
#include <MTRingBuffer.hpp>

namespace gfx
{ 
	class DawnRenderer : public Renderer
	{
	public:
		using RenderJob = std::function<void()>;

		virtual CommandBuffer* BeginCommandRecording() override;
		virtual RenderPassRenderer* RequestPassRenderer() override;

		virtual void Upload() override;

	private:
		virtual void Init() override;
		virtual void ShutDown() override;

		void Execute(const RenderJob& job);
		bool IsBusy();
		void Wait();
		inline void Poll();
        
    private:
		uint32_t m_CurrentPass = 0;
		DawnCommandBuffer m_CommandBuffers[4];
		DawnRenderPassRenderer m_RenderPassRenderers[4];

	private:
		uint32_t m_NumThreads = 0;
		utils::ThreadSafeRingBuffer<RenderJob, 6> m_JobPool;
		std::condition_variable m_WakeCondition;
		std::mutex m_WakeMutex;
		uint64_t m_CurrentLabel = 0;
		std::atomic<uint64_t> m_FinishedLabel;

	private:
		friend class DawnRenderPassRenderer;
	};
}

#endif // !__DAWN_RENDERER_HPP__
