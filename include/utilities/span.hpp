#ifndef __SPAN_HPP__
#define __SPAN_HPP__

#include <vector>
#include <initializer_list>

namespace utils
{
	template<typename T>
	class Span
	{
	public:
		Span() = default;
		Span(std::vector<T> list) : m_Data(list.data()), m_Size(list.size()) {}
		Span(std::initializer_list<T> initializer_list) : m_Data(initializer_list.begin()), m_Size(initializer_list.size()) {}
		Span(T* data, size_t size) : m_Data(data), m_Size(size) {}

		template<size_t N>
		Span(T(&array)[N]) : m_Data(array), m_Size(sizeof(array) / sizeof(T)) {}

		explicit Span(T* data) : m_Data(data), m_Size(1) {}
		explicit Span(T& data) : m_Data(&data), m_Size(1) {}

		operator std::initializer_list<T>() const
		{
			return std::initializer_list<T>(begin(), end());
		}

		const T* begin() const { return m_Data; }
		const T* end() const { return m_Data + m_Size; }
		//T* begin() { return m_Data; }
		//T* end() { return m_Data + m_Size; }

		size_t size() const { return m_Size; }

	private:
		const T* m_Data = nullptr;
		size_t m_Size = 0;
	};
}

#endif