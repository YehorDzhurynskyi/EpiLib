#pragma once

#include"EpiLib/pch.h"

namespace epi
{

class BaseArray
{
public:
    virtual ~BaseArray() = default;

    virtual epiByte* GetData() = 0;
    virtual epiSize_t GetSize() const = 0;
};

template<typename T>
class Array : public BaseArray
{
public:
    using value_type = typename std::vector<T>::value_type;
    using allocator_type = typename std::vector<T>::allocator_type;
    using pointer = typename std::vector<T>::pointer;
    using const_pointer = typename std::vector<T>::const_pointer;
    using reference = typename std::vector<T>::reference;
    using const_reference = typename std::vector<T>::const_reference;
    using size_type = typename std::vector<T>::size_type;
    using difference_type = typename std::vector<T>::difference_type;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    using reverse_iterator = typename std::vector<T>::reverse_iterator;
    using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;

public:
    epiByte* GetData() override
    {
        return reinterpret_cast<epiByte*>(m_Vector.data());
    }

    epiSize_t GetSize() const override
    {
        return m_Vector.size();
    }

    epiBool IsEmpty() const
    {
        return m_Vector.empty();
    }

    void Clear()
    {
        m_Vector.clear();
    }

    void Reserve(epiSize_t size)
    {
        m_Vector.reserve(size);
    }

    T& Push(T&& value = T())
    {
        m_Vector.push_back(std::forward<T&&>(value));
        return m_Vector.back();
    }

    epiSize_t Size() const
    {
        return m_Vector.size();
    }

public:
    auto begin() -> typename std::vector<T>::iterator
    {
        return m_Vector.begin();
    }

    auto end() -> typename std::vector<T>::iterator
    {
        return m_Vector.end();
    }

    auto cbegin() const -> typename std::vector<T>::const_iterator
    {
        return m_Vector.cbegin();
    }

    auto cend() const -> typename std::vector<T>::const_iterator
    {
        return m_Vector.cend();
    }

    T& operator[](const epiS32 index)
    {
        return m_Vector[index];
    }

    const T& operator[](const epiS32 index) const
    {
        return m_Vector[index];
    }

    void push_back(const T& value)
    {
        m_Vector.push_back(value);
    }

    void push_back(T&& value)
    {
        m_Vector.push_back(std::forward<T&&>(value));
    }

protected:
    std::vector<T> m_Vector;
};

}
