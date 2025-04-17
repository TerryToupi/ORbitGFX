#ifndef __POOL_HPP__
#define __POOL_HPP__

#include <vector> 
#include <string>
#include <utilities/handle.hpp>

namespace utils
{
    template<typename U, typename V>
    class Pool {
    public:
        Pool(uint32_t reserveSize, std::string debugName)
            : m_DebugName(std::move(debugName)), m_Size(reserveSize)
        {
            m_Data.resize(m_Size);
            m_Generation.resize(m_Size, 1);

            for (uint32_t i = 0; i < m_Size; i++) {
                m_FreeList.emplace_back((m_Size - 1) - i);
            }
        }

        Handle<V> Insert(const U& data)
        {
            if (m_FreeList.empty()) {
                Resize(m_Size * 2);
            }

            uint32_t index = m_FreeList.back();
            m_FreeList.pop_back();

            m_Data[index] = std::move(data);

            return { index, m_Generation[index] };
        }

        U* Get(Handle<V> handle)
        {
            if (!handle.IsValid() || handle.m_Generation != m_Generation[handle.m_Index]) {
                return nullptr;
            }

            return &m_Data[handle.m_Index];
        }

        void Remove(Handle<V> handle)
        {
            if (handle.m_Index >= m_Size || m_Generation[handle.m_Index] != handle.m_Generation) {
                return;
            }

            m_Generation[handle.m_Index]++;
            m_FreeList.emplace_back(handle.m_Index);
        }

    private:
        void Resize(uint32_t newSize)
        {
            m_Data.resize(newSize);
            m_Generation.resize(newSize, 1); 

            for (uint32_t i = 0; i < (newSize - m_Size); i++) {
                m_FreeList.emplace_back((newSize - 1) - i);
            }

            m_Size = newSize;
        }

    private:
        std::vector<U> m_Data;
        std::vector<uint16_t> m_Generation;
        std::vector<uint16_t> m_FreeList;
        std::string m_DebugName;
        uint32_t m_Size;
    };
}

#endif // !__POOL_HPP__
