#pragma once

namespace epi
{

class epiBaseArray
{
public:
    epiBaseArray() = default;
    epiBaseArray(const epiBaseArray& rhs) = default;
    epiBaseArray& operator=(const epiBaseArray& rhs) = default;
    epiBaseArray(epiBaseArray&&) = default;
    epiBaseArray& operator=(epiBaseArray&&) = default;
    virtual ~epiBaseArray() = default;

    virtual epiByte* GetData() = 0;
    virtual epiSize_t GetSize() const = 0;
    virtual epiSize_t GetSizeOfItem() const = 0;
};

template<typename T>
class epiArray : public epiBaseArray
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
    epiArray() = default;

    template<typename It>
    epiArray(It begin, It end)
        : m_Vector{begin, end}
    {
    }

    epiArray(std::initializer_list<T> list)
        : m_Vector{list}
    {
    }

    epiByte* GetData() override
    {
        return reinterpret_cast<epiByte*>(m_Vector.data());
    }

    const T* data() const
    {
        return reinterpret_cast<const T*>(m_Vector.data());
    }

    T* data()
    {
        return reinterpret_cast<T*>(m_Vector.data());
    }

    epiSize_t GetSize() const override
    {
        return m_Vector.size();
    }

    epiSize_t GetSizeOfItem() const override
    {
        return sizeof(T);
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

    void Resize(epiSize_t size)
    {
        m_Vector.resize(size);
    }

    T& PushBack(T&& value = T())
    {
        m_Vector.push_back(std::forward<T&&>(value));
        return m_Vector.back();
    }

    epiSize_t Size() const
    {
        return m_Vector.size();
    }

public:
    auto begin() -> typename iterator
    {
        return m_Vector.begin();
    }

    auto end() -> typename iterator
    {
        return m_Vector.end();
    }

    auto begin() const -> typename const_iterator
    {
        return m_Vector.cbegin();
    }

    auto end() const -> typename const_iterator
    {
        return m_Vector.cend();
    }

    auto cbegin() const -> typename const_iterator
    {
        return m_Vector.cbegin();
    }

    auto cend() const -> typename const_iterator
    {
        return m_Vector.cend();
    }

    auto rbegin() -> typename reverse_iterator
    {
        return m_Vector.rbegin();
    }

    auto rend() -> typename reverse_iterator
    {
        return m_Vector.rend();
    }

    auto crbegin() -> typename const_reverse_iterator
    {
        return m_Vector.crbegin();
    }

    auto crend() -> typename const_reverse_iterator
    {
        return m_Vector.crend();
    }

    T& operator[](const epiS32 index)
    {
        return m_Vector[index];
    }

    const T& operator[](const epiS32 index) const
    {
        return m_Vector[index];
    }

    friend epiBool operator==(const epiArray<T>& lhs, const epiArray<T>& rhs)
    {
        if (&lhs == &rhs)
        {
            return true;
        }

        if (lhs.GetSize() != rhs.GetSize())
        {
            return false;
        }

        for (epiU32 i = 0; i < lhs.GetSize(); ++i)
        {
            if (!epiEqual(lhs[i], rhs[i]))
            {
                return false;
            }
        }

        return true;
    }

    friend epiBool operator!=(const epiArray<T>& lhs, const epiArray<T>& rhs)
    {
        return !(operator==(lhs, rhs));
    }

    void push_back(const T& value)
    {
        m_Vector.push_back(value);
    }

    void push_back(T&& value)
    {
        m_Vector.push_back(std::forward<T&&>(value));
    }

    template<typename ...Args>
    T& emplace_back(Args&& ...args)
    {
        return m_Vector.emplace_back(std::forward<Args&&>(args)...);
    }

    T& back()
    {
        return m_Vector.back();
    }

    const T& back() const
    {
        return m_Vector.back();
    }

protected:
    std::vector<T> m_Vector;
};

template<typename T>
using epiPtrArray = epiArray<T*>;

}
