#include <dawn/render/dawnRenderer.hpp>
#include <dawn/dawnDevice.hpp>

#include <algorithm>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <sstream>
#include <assert.hpp>

#ifdef _WIN32 
#define NOMINMAX
#include <Windows.h>
#endif


namespace gfx
{
	RenderPassRenderer* DawnRenderer::RequestPassRenderer()
	{
		DawnDevice* deviceInstance = (DawnDevice*)Device::instance;
		wgpu::Device device = deviceInstance->GetDawnDevice();

		m_RenderPassRenderers[m_CurrentPass].m_Encoder = device.CreateCommandEncoder();
		++m_CurrentPass;

		return static_cast<RenderPassRenderer*>(&m_RenderPassRenderers[m_CurrentPass]);
	}

	void DawnRenderer::Upload()
	{
		Wait();
		
		m_CurrentPass = 0;

        DawnDevice* deviceImpl = (DawnDevice*)Device::instance;
        wgpu::Device device = deviceImpl->GetDawnDevice();

		wgpu::CommandBuffer buffers[] =
		{
			m_CommandBuffers[0].m_CommandBuffer,
			m_CommandBuffers[1].m_CommandBuffer,
			m_CommandBuffers[2].m_CommandBuffer,
			m_CommandBuffers[3].m_CommandBuffer,
		};

		device.GetQueue().Submit(4, buffers);
	}

	CommandBuffer* DawnRenderer::BeginCommandRecording()
	{
		return static_cast<CommandBuffer*>(&m_CommandBuffers[m_CurrentPass]);
	}

	void DawnRenderer::Execute(const RenderJob& job)
	{
		m_CurrentLabel += 1;

		while (!m_JobPool.push_back(job)) { Poll(); }
		m_WakeCondition.notify_one();
	}

	bool DawnRenderer::IsBusy()
	{
		return m_FinishedLabel.load() < m_CurrentLabel;
	}

	void DawnRenderer::Wait()
	{
		while (IsBusy()) { Poll(); }
	}

	inline void DawnRenderer::Poll()
	{
		m_WakeCondition.notify_one();
		std::this_thread::yield();
	}

	void DawnRenderer::Init()
	{
		// Initialize the worker execution state to 0:
		m_FinishedLabel.store(0);
		// Calculate the actual number of worker threads we want:
		m_NumThreads = 4u;

		// Create all our worker threads while immediately starting them:
		for (uint32_t threadID = 0; threadID < m_NumThreads; ++threadID)
		{
			std::thread worker([=] {

				RenderJob job; // the current job for the thread, it's empty at start.

				// This is the infinite loop that a worker thread will do 
				while (true)
				{
					if (m_JobPool.pop_front(job)) // try to grab a job from the jobPool queue
					{
						// It found a job, execute it:
						job(); // execute job
						m_FinishedLabel.fetch_add(1); // update worker label state
					}
					else
					{
						// no job, put thread to sleep
						std::unique_lock<std::mutex> lock(m_WakeMutex);
						m_WakeCondition.wait(lock);
					}
				}
			});

			#ifdef _WIN32 
			{
				// Do Windows-specific thread setup: 
				HANDLE handle = (HANDLE)worker.native_handle();

				// Put each thread on to dedicated core
				DWORD_PTR affinityMask = 1ull << threadID;
				DWORD_PTR affinity_result = SetThreadAffinityMask(handle, affinityMask);
				GFX_ASSERT((affinity_result > 0));

				// Increase thread priority:
				BOOL priority_result = SetThreadPriority(handle, THREAD_PRIORITY_HIGHEST);
				GFX_ASSERT(priority_result != 0);

				// Name the thread:
				std::wstringstream wss;
				wss << "EngineJob_" << threadID;
				HRESULT hr = SetThreadDescription(handle, wss.str().c_str());
				GFX_ASSERT(SUCCEEDED(hr));
			}
			#endif // _WIN32  

			worker.detach();
		}
	}

	void DawnRenderer::ShutDown()
	{
	}
}
