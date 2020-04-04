#pragma once

// ============================= PROPERTY =============================

#define epiReadProperty(_Key, _Type, _Json)     \
{                                               \
    assert(_Json.is_object());                  \
    assert(_Json[#_Key].is_##_Type());          \
    assert(_Json.find(#_Key) != _Json.end());   \
    _Json[#_Key].get_to(m_##_Key);              \
}                                               \

#define epiReadPropertyDefault(_Key, _Type, _Json, _Default)    \
{                                                               \
    assert(_Json.is_object());                                  \
    if (_Json.find(#_Key) != _Json.end())                       \
    {                                                           \
        assert(_Json[#_Key].is_##_Type());                      \
        _Json[#_Key].get_to(m_##_Key);                          \
    }                                                           \
    else                                                        \
    {                                                           \
        m_##_Key = _Default;                                    \
    }                                                           \
}                                                               \

// ============================= OBJECT =============================

#define epiReadObject(_Key, _Json)              \
{                                               \
    assert(_Json.is_object());                  \
    assert(_Json[#_Key].is_object());           \
    assert(_Json.find(#_Key) != _Json.end());   \
    m_##_Key.Deserialization(_Json[#_Key]);     \
}                                               \

// ============================= ARRAY =============================
#define epiReadArray(_Key, _Json)               \
{                                               \
    assert(m_##_Key.IsEmpty());                 \
    assert(_Json.is_object());                  \
    assert(_Json.find(#_Key) != _Json.end());   \
    assert(_Json[#_Key].is_array());            \
    for (auto& j : _Json[#_Key])                \
    {                                           \
        auto& item = m_##_Key.Push();           \
        item.Deserialize(j);                    \
    }                                           \
}                                               \

#define epiSerialize(_Key, _Json) epiSerialize_Impl(#_Key, m_##_Key, _Json)

// TODO: replace FiniteFloating class with getters/setters checks
template< class T >
struct epi_is_fundamental
    : std::integral_constant<
        bool,
        std::is_fundamental_v<T> ||
        std::is_same_v<epiString, T> ||
        std::is_same_v<FiniteFloating<float>, T> ||
        std::is_same_v<FiniteFloating<double>, T>
    >
{};

template< class T >
constexpr bool epi_is_fundamental_v = epi_is_fundamental<T>::value;

template<typename T>
inline auto epiSerialize_Impl_Fetch(T& v)
{
    if constexpr (epi_is_fundamental_v<T>)
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
    assert(json.find(key) == json.end());

    json[key] = epiSerialize_Impl_Fetch(v);
}
