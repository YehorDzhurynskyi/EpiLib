#pragma once

#include <iterator>
#include "EpiLib/pch.h"

namespace
{
    epiS32 rot_prev(const epiS32 pos, const epiSize_t size)
    {
        return (pos + size - 1) % size;
    }

    epiS32 rot_next(const epiS32 pos, const epiSize_t size)
    {
        return (pos + 1) % size;
    }
}

namespace epi
{

template<typename Type>
class RotatingIterator final
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = Type;
    using difference_type = std::ptrdiff_t;
    using pointer = Type*;
    using reference = Type&;

    RotatingIterator(const epiS32 position, const epiS32 cursor, Type* dataOrigin, const epiSize_t size)
        : m_Position(position)
        , m_Cursor(cursor)
        , m_DataOrigin(dataOrigin)
        , m_Size(size)
    {
        assert(IsValid());
    }

    RotatingIterator(const RotatingIterator& rhs) = default;
    RotatingIterator(RotatingIterator&& rhs) = default;
    RotatingIterator& operator=(const RotatingIterator& rhs) = default;
    RotatingIterator& operator=(RotatingIterator&& rhs) = default;
    ~RotatingIterator() = default;

    bool IsValid() const
    {
        return
            m_Position >= 0 && m_Position < m_Size &&
            m_DataOrigin != nullptr &&
            m_Cursor >= 0 && m_Cursor <= m_Size;
    }

    void swap(RotatingIterator& rhs)
    {
        std::swap(m_Position, rhs.m_Position);
        std::swap(m_Cursor, rhs.m_Cursor);
        std::swap(m_DataOrigin, rhs.m_DataOrigin);
        std::swap(m_Size, rhs.m_Size);
    }

    RotatingIterator& operator++()
    {
        Next();
        return *this;
    }

    RotatingIterator operator++(epiS32 n)
    {
        RotatingIterator tmp(*this);

        epiFor(n)
        {
            Next();
        }

        return tmp;
    }

    RotatingIterator& operator--()
    {
        Prev();
        return *this;
    }

    RotatingIterator operator--(epiS32 n)
    {
        RotatingIterator tmp(*this);

        epiFor(n)
        {
            Prev();
        }

        return tmp;
    }

    bool operator==(const RotatingIterator<Type>& rhs) const
    {
        return
            m_Position == rhs.m_Position &&
            m_Cursor == rhs.m_Cursor &&
            m_DataOrigin == rhs.m_DataOrigin &&
            m_Size == rhs.m_Size;
    }

    bool operator!=(const RotatingIterator<Type>& rhs) const
    {
        return !operator==(rhs);
    }

    Type& operator*() const
    {
        assert(IsValid());
        return m_DataOrigin[m_Position];
    }

    Type& operator->() const
    {
        assert(IsValid());
        return m_DataOrigin[m_Position];
    }

    operator RotatingIterator<const Type>() const
    {
        return RotatingIterator<const Type>(m_Position, m_Cursor, m_DataOrigin, m_Size);
    }

private:
    void Next()
    {
        assert(IsValid());
        m_Position = rot_next(m_Position, m_Size);
        --m_Cursor;
    }

    void Prev()
    {
        assert(IsValid());
        m_Position = rot_prev(m_Position, m_Size);
        ++m_Cursor;
    }

private:
    epiS32 m_Position;
    epiS32 m_Cursor;
    Type* m_DataOrigin;
    const epiSize_t m_Size;
};

template<typename Type, epiSize_t Capacity>
class RotatingBuffer
{
public:
    using iterator = RotatingIterator<Type>;
    using const_iterator = RotatingIterator<const Type>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    RotatingBuffer()
        : m_Position(-1)
        , m_Size(0)
    {}

    epiSize_t GetCapacity() const
    {
        return Capacity;
    }

    epiSize_t GetSize() const
    {
        return m_Size;
    }

    Type& Push(const Type& item)
    {
        m_Position = rot_next(m_Position, Capacity);
        m_Data[m_Position] = item;
        return _push();
    }

    Type& Push(Type&& item = Type())
    {
        m_Position = rot_next(m_Position, Capacity);
        m_Data[m_Position] = std::move(item);
        return _push();
    }

    iterator begin()
    {
        // NOTE: container is empty, it is not handled now
        assert(m_Size != 0 || m_Position != -1);

        return m_Size > 0 ?
            iterator(rot_next(m_Position, m_Size), m_Size, m_Data, m_Size) :
            end();
    }

    iterator end()
    {
        // NOTE: container is empty, it is not handled now
        assert(m_Size != 0 || m_Position != -1);

        return iterator(rot_next(m_Position, m_Size), 0, m_Data, m_Size);
    }

    const_iterator begin() const
    {
        // NOTE: container is empty, it is not handled now
        assert(m_Size != 0 || m_Position != -1);

        return m_Size > 0 ?
            const_iterator(rot_next(m_Position, m_Size), m_Size, m_Data, m_Size) :
            end();
    }

    const_iterator end() const
    {
        // NOTE: container is empty, it is not handled now
        assert(m_Size != 0 || m_Position != -1);

        return const_iterator(rot_next(m_Position, m_Size), 0, m_Data, m_Size);
    }

    reverse_iterator rbegin()
    {
        // NOTE: container is empty, it is not handled now
        assert(m_Size != 0 || m_Position != -1);

        return m_Size > 0 ?
            reverse_iterator(end()) :
            rend();
    }

    reverse_iterator rend()
    {
        // NOTE: container is empty, it is not handled now
        assert(m_Size != 0 || m_Position != -1);

        return reverse_iterator(begin());
    }

    const_reverse_iterator rbegin() const
    {
        // NOTE: container is empty, it is not handled now
        assert(m_Size != 0 || m_Position != -1);

        return m_Size > 0 ?
            const_reverse_iterator(end()) :
            rend();
    }

    const_reverse_iterator rend() const
    {
        // NOTE: container is empty, it is not handled now
        assert(m_Size != 0 || m_Position != -1);

        return const_reverse_iterator(begin());
    }

private:
    Type& _push()
    {
        Type& result = m_Data[m_Position];
        m_Size = std::min<epiSize_t>(m_Size + 1, Capacity);
        return result;
    }

private:
    epiS32 m_Position;
    epiSize_t m_Size;
    Type m_Data[Capacity];
};

}
