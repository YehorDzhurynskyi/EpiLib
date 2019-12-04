#pragma once

#include "EpiCore/pch.h"

namespace epi
{

class BaseHashMap
{
public:
    virtual ~BaseHashMap() = default;

    virtual epiByte* Get(epiHash_t hash) = 0;
};

template<typename T>
class HashMap final : public BaseHashMap
{
public:
    using key_type = typename std::map<epiHash_t, T>::key_type;
    using mapped_type = typename std::map<epiHash_t, T>::mapped_type;
    using key_compare = typename std::map<epiHash_t, T>::key_compare;
    using value_compare = typename std::map<epiHash_t, T>::value_compare;
    using value_type = typename std::map<epiHash_t, T>::value_type;
    using allocator_type = typename std::map<epiHash_t, T>::allocator_type;
    using pointer = typename std::map<epiHash_t, T>::pointer;
    using const_pointer = typename std::map<epiHash_t, T>::const_pointer;
    using reference = typename std::map<epiHash_t, T>::reference;
    using const_reference = typename std::map<epiHash_t, T>::const_reference;
    using size_type = typename std::map<epiHash_t, T>::size_type;
    using difference_type = typename std::map<epiHash_t, T>::difference_type;
    using iterator = typename std::map<epiHash_t, T>::iterator;
    using const_iterator = typename std::map<epiHash_t, T>::const_iterator;
    using reverse_iterator = typename std::map<epiHash_t, T>::reverse_iterator;
    using const_reverse_iterator = typename std::map<epiHash_t, T>::const_reverse_iterator;

public:
    epiByte* Get(epiHash_t hash) override
    {
        auto it = m_Map.find(hash);
        return it != m_Map.end() ? reinterpret_cast<epiByte*>(&it->second) : nullptr;
    }

    epiBool Has(epiHash_t hash) const
    {
        return m_Map.find(hash) != m_Map.end();
    }

public:
    auto begin() -> typename std::map<epiHash_t, T>::iterator
    {
        return m_Map.begin();
    }

    auto end() -> typename std::map<epiHash_t, T>::iterator
    {
        return m_Map.end();
    }

    auto cbegin() const -> typename std::map<epiHash_t, T>::const_iterator
    {
        return m_Map.cbegin();
    }

    auto cend() const -> typename std::map<epiHash_t, T>::const_iterator
    {
        return m_Map.cend();
    }

    T& operator[](const epiHash_t hash)
    {
        return m_Map[hash];
    }

    const T& operator[](const epiHash_t hash) const
    {
        return m_Map[hash];
    }

protected:
    std::map<epiHash_t, T> m_Map;
};

}
