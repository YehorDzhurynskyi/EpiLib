#pragma once

#include "json.hpp"
using json_t = nlohmann::json;

template<typename T>
class FiniteFloating final
{
    static_assert(std::is_floating_point<T>::value);
public:
    FiniteFloating() = default;
    FiniteFloating(T value) : m_Value(value) { Validate(); }

    operator T() const { Validate(); return m_Value; }
    operator T&() { Validate(); return m_Value; }

    friend void from_json(const json_t& j, FiniteFloating& f)
    {
        j.get_to(f.m_Value);
    }

    friend void to_json(json_t& j, const FiniteFloating& f)
    {
        j = f.m_Value;
    }

protected:
    void Validate() const
    {
        assert(std::isfinite(m_Value));
    }

protected:
    T m_Value;
};
