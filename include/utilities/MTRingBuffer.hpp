#ifndef __THREAD_SAFE_RING_BUFFER__

#include <mutex>

namespace utils 
{
	template <typename T, size_t capacity>
	class ThreadSafeRingBuffer
	{
	public:
		inline bool push_back(const T& item)
		{
			bool result = false;
			m_lock.lock();
			size_t next = (m_head + 1) % capacity;
			if (next != m_tail)
			{
				m_data[m_head] = item;
				m_head = next;
				result = true;
			}
			m_lock.unlock();
			return result;
		}

		inline bool pop_front(T& item)
		{
			bool result = false;
			m_lock.lock();
			if (m_tail != m_head)
			{
				item = m_data[m_tail];
				m_tail = (m_tail + 1) % capacity;
				result = true;
			}
			m_lock.unlock();
			return result;
		}

	private:
		T m_data[capacity];
		size_t m_head = 0;
		size_t m_tail = 0;
		std::mutex m_lock;
	};
}

#endif // !__THREAD_SAFE_RING_BUFFER__

