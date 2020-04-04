#pragma once

#define epiSerialize(_Key, _Json) epiSerialize_Impl(#_Key, m_##_Key, _Json)
#define epiDeserialize(_Key, _Json) epiDeserialize_Impl(#_Key, m_##_Key, _Json)

namespace epi
{

// TODO: replace FiniteFloating class with getters/setters checks
template<typename T>
struct is_fundamental
    : std::integral_constant<
        bool,
        std::is_fundamental_v<T> ||
        std::is_same_v<epiString, T> ||
        std::is_same_v<FiniteFloating<float>, T> ||
        std::is_same_v<FiniteFloating<double>, T>
    >
{};

template<typename T>
struct is_arithmetic
    : std::integral_constant<
        bool,
        std::is_arithmetic_v<T> ||
        std::is_same_v<FiniteFloating<float>, T> ||
        std::is_same_v<FiniteFloating<double>, T>
    >
{};

template<typename T>
struct is_floating_point
    : std::integral_constant<
        bool,
        std::is_floating_point_v<T> ||
        std::is_same_v<FiniteFloating<float>, T> ||
        std::is_same_v<FiniteFloating<double>, T>
    >
{};

template<typename T>
struct is_integral
    : std::integral_constant<
        bool,
        std::is_integral_v<T>
    >
{};

template<typename T>
constexpr bool is_fundamental_v = is_fundamental<T>::value;

template<typename T>
constexpr bool is_arithmetic_v = is_arithmetic<T>::value;

template<typename T>
constexpr bool is_floating_point_v = is_floating_point<T>::value;

template<typename T>
constexpr bool is_integral_v = is_integral<T>::value;

}

template<typename T>
inline auto epiSerialize_Impl_Fetch(T& v)
{
    if constexpr (epi::is_fundamental_v<T>)
    {
        return v;
    }
    else if constexpr (std::is_base_of_v<epi::Object, T>)
    {
        json_t jsonObject = json_t::object();
        v.Serialize(jsonObject);
        return jsonObject;
    }
    else if constexpr (std::is_base_of_v<epi::BaseArray, T>)
    {
        auto arr = json_t::array();
        for (auto& e : v)
        {
            auto j = epiSerialize_Impl_Fetch(e);
            arr.push_back(j);
        }
        return arr;
    }
    else
    {
        static_assert(false, "Unhandled type for seriazliation (epiSerialize_Impl_Fetch)");
    }
}

template<typename T>
inline void epiDeserialize_Impl_Fetch(T& v, const json_t& json)
{
    if constexpr (epi::is_fundamental_v<T>)
    {
        if constexpr (std::is_same_v<epiBool, T>)
        {
            assert(json.is_boolean());
        }
        else if constexpr (epi::is_floating_point_v<T>)
        {
            assert(json.is_number_float());
        }
        else if constexpr (epi::is_integral_v<T>)
        {
            if constexpr (std::is_signed_v<T>)
            {
                assert(json.is_number_integer());
            }
            else
            {
                assert(json.is_number_unsigned());
            }
        }
        else if constexpr (std::is_same_v<epiString, T>)
        {
            assert(json.is_string());
        }
        json.get_to(v);
    }
    else if constexpr (std::is_base_of_v<epi::Object, T>)
    {
        assert(json.is_object());
        v.Deserialize(json);
    }
    else if constexpr (std::is_base_of_v<epi::BaseArray, T>)
    {
        assert(v.IsEmpty());
        assert(json.is_array());

        for (auto& j : json)
        {
            auto& item = v.Push();
            epiDeserialize_Impl_Fetch(item, j);
        }
    }
    else
    {
        static_assert(false, "Unhandled type for seriazliation (epiSerialize_Impl_Fetch)");
    }
}

template<typename T>
inline void epiSerialize_Impl(const char* key, T& v, json_t& json)
{
    assert(json.is_object());
    assert(json.find(key) == json.end());

    json[key] = epiSerialize_Impl_Fetch(v);
}

template<typename T>
inline void epiDeserialize_Impl(const char* key, T& v, const json_t& json)
{
    assert(json.is_object());
    assert(json.find(key) != json.end());

    epiDeserialize_Impl_Fetch(v, json[key]);
}
