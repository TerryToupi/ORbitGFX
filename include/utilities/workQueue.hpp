#ifndef __WORK_QUEUE_HPP__
#define __WORK_QUEUE_HPP__

#include <functional>
#include <deque>

namespace utils
{
	class WorkQueue
	{
	public:
		using work = std::function<void()>;

		WorkQueue() = default;
		virtual ~WorkQueue() = default;
		
		void Append(const work& func)
		{
			m_Workers.emplace_back(func);
		} 

		void Flush()
		{
			while (!m_Workers.empty())
			{
				auto& func = m_Workers.front(); 
				func();
				m_Workers.pop_front();
			}
		}

		bool Empty()
		{
			return m_Workers.empty();
		}

	private:
		std::deque<work> m_Workers;
	};
}

#endif // !__DELETION_QUEUE_HPP__
