#pragma once

namespace epi
{

template<typename T>
class Handle final
{
public:
    Handle()
        : m_Value(nullptr)
    {}

    explicit Handle(std::unique_ptr<T>&& value)
        : m_Value(std::move(value))
    {
        assert(m_Value);
    }

    template<typename U>
    Handle(Handle<U>&& rhs)
        : m_Value(rhs.Release())
    {
        static_assert(std::is_base_of<T, U>::value);
    }

    Handle(Handle&&) = default;
    Handle& operator=(Handle&&) = default;
    Handle(const Handle&) = delete;
    Handle& operator=(const Handle&) = delete;
    ~Handle() = default;

    template<typename ... Args>
    static Handle New(Args&& ... args)
    {
        return Handle(std::make_unique<T>(std::forward<Args&&>(args)...));
    }

    epiByte* GetValue()
    {
        return reinterpret_cast<epiByte*>(m_Value.get());
    }

    T* Get()
    {
        return m_Value.get();
    }

    T* Release()
    {
        return m_Value.release();
    }

public:
    T* operator->()
    {
        assert(m_Value);
        return m_Value.get();
    }

    T& operator*()
    {
        assert(m_Value);
        return *m_Value;
    }

protected:
    std::unique_ptr<T> m_Value;
};

using BaseHandle = Handle<epiByte>;

}
