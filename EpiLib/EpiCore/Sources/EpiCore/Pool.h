#pragma once

#include "EpiLib/pch.h"

namespace epi
{

template<typename T, size_t N>
class Pool
{
    // TODO: check that T is derivative of EObject class
    // static_assert()
public:
    struct Node final
    {
        T Value;
        Node* Next;
        epiBool InUse;
        epiBool IsAlive;
    };

    struct Handle final
    {
    public:
        Handle();
        Handle(Node& node);
        Handle(const Handle& handle) = delete;
        Handle& operator=(const Handle& handle) = delete;
        Handle(Handle&& handle);
        Handle& operator=(Handle&& handle);
        ~Handle();

        epiBool IsValid() const;

        void Release();

        T* operator->();
        T& operator*();
        const T* operator->() const;
        const T& operator*() const;

    private:
        Node* m_Node;
    };

public:
    class PoolIterator final
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        PoolIterator();
        PoolIterator(Node* node);
        PoolIterator(const PoolIterator&) = default;
        PoolIterator& operator=(const PoolIterator&) = default;
        PoolIterator(PoolIterator&&) = delete;
        PoolIterator& operator=(PoolIterator&&) = delete;
        ~PoolIterator() = default;

        epiBool IsValid() const;

        PoolIterator& operator++();
        PoolIterator operator++(epiS32);
        reference operator*() const;
        pointer operator->() const;
        epiBool operator==(const PoolIterator&);
        epiBool operator!=(const PoolIterator&);
        void swap(PoolIterator& rhs);

    private:
        void Next();

    private:
        Node* m_Node;
    };

public:
    Pool()
        : m_DebugCount(0)
    {
        m_NextAvailableNode = &m_Nodes[0];

        epiFor(m_Nodes.size() - 1)
        {
            m_Nodes[index].Next = &m_Nodes[index + 1];
            m_Nodes[index].InUse = false;
            m_Nodes[index].IsAlive = false;
        }
        m_Nodes[m_Nodes.size() - 1].Next = nullptr;
        m_Nodes[m_Nodes.size() - 1].InUse = false;
        m_Nodes[m_Nodes.size() - 1].IsAlive = false;
    }

    Handle Push(T&& value)
    {
        assert(m_NextAvailableNode != nullptr);

        Node* occupiedNode = m_NextAvailableNode;
        m_NextAvailableNode = occupiedNode->Next;

        occupiedNode->InUse = true;
        occupiedNode->IsAlive = true;
        new (&occupiedNode->Value) T(std::move(value));
        ++m_DebugCount;
        return Handle(*occupiedNode);
    }

    template<typename ...Args>
    Handle Emplace(Args&& ...args)
    {
        assert(m_NextAvailableNode != nullptr);

        Node* occupiedNode = m_NextAvailableNode;
        m_NextAvailableNode = occupiedNode->Next;

        occupiedNode->InUse = true;
        occupiedNode->IsAlive = true;
        new (&occupiedNode->Value) T(std::forward<Args>(args)...);
        ++m_DebugCount;
        return Handle(*occupiedNode);
    }

    void Rescan()
    {
        for (Node& node : m_Nodes)
        {
            if (node.InUse && !node.IsAlive)
            {
                node.Next = m_NextAvailableNode;
                node.InUse = false;
                node.IsAlive = false;
                m_NextAvailableNode = &node;
                --m_DebugCount;
            }
        }
    }

    PoolIterator begin()
    {
        auto firstInUseIt = std::find_if(m_Nodes.begin(),
                                         m_Nodes.end(),
                                         [](const Node& node)
        {
            return node.InUse;
        });
        return PoolIterator(&*firstInUseIt);
    }

    PoolIterator end()
    {
        return PoolIterator();
    }

private:
    std::array<Node, N> m_Nodes;
    Node* m_NextAvailableNode;
    epiS32 m_DebugCount;
};

template<typename T, size_t N>
Pool<T, N>::Handle::Handle()
    : m_Node(nullptr)
{}

template<typename T, size_t N>
Pool<T, N>::Handle::~Handle()
{
    Release();
}

template<typename T, size_t N>
Pool<T, N>::Handle::Handle(Node& node)
    : m_Node(&node)
{}

template<typename T, size_t N>
Pool<T, N>::Handle::Handle(Handle&& handle)
{
    m_Node = handle.m_Node;
    handle.m_Node = nullptr;
}

template<typename T, size_t N>
typename Pool<T, N>::Handle& Pool<T, N>::Handle::operator=(Handle&& handle)
{
    m_Node = handle.m_Node;
    handle.m_Node = nullptr;

    return *this;
}

template<typename T, size_t N>
epiBool Pool<T, N>::Handle::IsValid() const
{
    return m_Node != nullptr;
}

template<typename T, size_t N>
void Pool<T, N>::Handle::Release()
{
    if (m_Node != nullptr)
    {
        m_Node->IsAlive = false;
        // TODO: call Release method on EObject so it could detach event handlers etc
        // m_Node->Value.Release();
    }

    m_Node = nullptr;
}

template<typename T, size_t N>
T* Pool<T, N>::Handle::operator->()
{
    assert(IsValid());
    return &m_Node->Value;
}

template<typename T, size_t N>
T& Pool<T, N>::Handle::operator*()
{
    assert(IsValid());
    return m_Node->Value;
}

template<typename T, size_t N>
const T* Pool<T, N>::Handle::operator->() const
{
    assert(IsValid());
    return &m_Node->Value;
}

template<typename T, size_t N>
const T& Pool<T, N>::Handle::operator*() const
{
    assert(IsValid());
    return m_Node->Value;
}

template<typename T, size_t N>
Pool<T, N>::PoolIterator::PoolIterator()
    : m_Node(nullptr)
{}

template<typename T, size_t N>
Pool<T, N>::PoolIterator::PoolIterator(Node* node)
    : m_Node(node)
{}

template<typename T, size_t N>
epiBool Pool<T, N>::PoolIterator::IsValid() const
{
    return m_Node != nullptr;
}

template<typename T, size_t N>
typename Pool<T, N>::PoolIterator& Pool<T, N>::PoolIterator::operator++()
{
    Next();
    return *this;
}

template<typename T, size_t N>
typename Pool<T, N>::PoolIterator Pool<T, N>::PoolIterator::operator++(epiS32 n)
{
    PoolIterator tmp(*this);

    epiFor(n)
    {
        Next();
    }

    return tmp;
}

template<typename T, size_t N>
typename Pool<T, N>::PoolIterator::reference Pool<T, N>::PoolIterator::operator*() const
{
    assert(IsValid());
    return m_Node->Value;
}

template<typename T, size_t N>
typename Pool<T, N>::PoolIterator::pointer Pool<T, N>::PoolIterator::operator->() const
{
    assert(IsValid());
    return &m_Node->Value;
}

template<typename T, size_t N>
epiBool Pool<T, N>::PoolIterator::operator==(const PoolIterator& rhs)
{
    return m_Node == rhs.m_Node;
}

template<typename T, size_t N>
epiBool Pool<T, N>::PoolIterator::operator!=(const PoolIterator& rhs)
{
    return m_Node != rhs.m_Node;
}

template<typename T, size_t N>
void Pool<T, N>::PoolIterator::swap(PoolIterator& rhs)
{
    std::swap(m_Node, rhs.m_Node);
}

template<typename T, size_t N>
void Pool<T, N>::PoolIterator::Next()
{
    assert(IsValid());
    m_Node = m_Node->Next;

    while (m_Node != nullptr && !m_Node->InUse)
    {
        assert(IsValid());
        m_Node = m_Node->Next;
    }
}

}
