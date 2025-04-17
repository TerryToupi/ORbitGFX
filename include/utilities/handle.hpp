#ifndef __HANDLE_HPP__
#define __HANDLE_HPP__ 

#include <cstdint>

namespace utils
{
	template<typename T>
	class Handle
	{
	public:
		Handle() : m_Index(0), m_Generation(0) {}

		bool IsValid() const { return m_Generation != 0; }
		bool operator==(const Handle<T>& other) const { return other.m_Index == m_Index && other.m_Generation == m_Generation; }
		bool operator!=(const Handle<T>& other) const { return other.m_Index != m_Index || other.m_Generation != m_Generation; }

		static Handle sentinal() { return Handle(0, 0xffff); }

		uint32_t hashKey() const { return (((uint32_t)m_Index) << 16) + (uint32_t)m_Generation; }
		uint16_t index()  const { return m_Index; }

	private:
		Handle(uint32_t index, uint32_t generation) : m_Index(index), m_Generation(generation) {}

	private:
		uint16_t m_Index;
		uint16_t m_Generation;

		template<typename U, typename V> friend class Pool;
	};
}

#endif // !__HANDLE_HPP__
