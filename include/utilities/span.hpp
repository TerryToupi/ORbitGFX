#ifndef __SPAN_HPP__
#define __SPAN_HPP__

#include <initializer_list>

namespace utils
{
    template <typename T>
    class Span {
    public:
        Span(const T* data, size_t size) 
            : m_Data(data), m_Size(size) {}

        template <size_t N>
        Span(const T(&arr)[N]) 
            : m_Data(arr), m_Size(N) {}

        Span(const std::initializer_list<T> list)
            : m_Data(list.begin()), m_Size(list.size()) {}

        T* data() { return m_Data; }
        const T* data() const { return m_Data; }
        size_t size() const { return m_Size; }

        T* begin() { return m_Data; }
        T* end() { return m_Data + m_Size; }
        const T* begin() const { return m_Data; }
        const T* end() const { return m_Data + m_Size; }

    private:
        T* m_Data = nullptr;
        size_t m_Size = 0;
    };
}

#endif