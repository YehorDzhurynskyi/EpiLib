#pragma once

#include <nlohmann/json.hpp>
#include "EpiCore/Containers/Array.h"

using json_t = nlohmann::json;

#define epiSerialize(_Key, _Json) epiSerialize_Impl(#_Key, m_##_Key, _Json)
#define epiDeserialize(_Key, _Json) epiDeserialize_Impl(#_Key, m_##_Key, _Json)

template<typename T>
inline auto epiSerialize_Impl_Fetch(T& v)
{
    if constexpr (std::is_fundamental_v<T> ||
                  std::is_enum_v<T> ||
                  std::is_same_v<epiString, T> ||
                  std::is_same_v<epiWString, T>)
    {
        // TODO: maybe replace enum serialization with a string to preserve restoreability after enum order modifying
        return v;
    }
    else if constexpr (std::is_base_of_v<epi::Object, T>)
    {
        json_t jsonObject = json_t::object();
        v.Serialize(jsonObject);
        return jsonObject;
    }
    else if constexpr (std::is_base_of_v<epi::epiBaseArray, T>)
    {
        auto arr = json_t::array();
        for (auto& e : v)
        {
            auto j = epiSerialize_Impl_Fetch(e);
            arr.push_back(j);
        }
        return arr;
    }
    else if constexpr (std::is_pointer_v<T>)
    {
        // TODO: implement
        return nullptr;
    }
    else if constexpr (std::is_same_v<epiVec2f, T> || std::is_same_v<epiVec2d, T> ||
                       std::is_same_v<epiVec2s, T> || std::is_same_v<epiVec2u, T> ||
                       std::is_same_v<epiVec3f, T> || std::is_same_v<epiVec3d, T> ||
                       std::is_same_v<epiVec3s, T> || std::is_same_v<epiVec3u, T> ||
                       std::is_same_v<epiVec4f, T> || std::is_same_v<epiVec4d, T> ||
                       std::is_same_v<epiVec4s, T> || std::is_same_v<epiVec4u, T>)
    {
        auto arr = json_t::array();
        for (int i = 0; i < T::length(); ++i)
        {
            arr.push_back(epiSerialize_Impl_Fetch(v[i]));
        }
        return arr;
    }
    else if constexpr (std::is_same_v<epiRect2f, T> || std::is_same_v<epiRect2d, T> ||
                       std::is_same_v<epiRect2s, T> || std::is_same_v<epiRect2u, T>)
    {
        auto arr = json_t::array();
        arr.push_back(epiSerialize_Impl_Fetch(v.Left));
        arr.push_back(epiSerialize_Impl_Fetch(v.Top));
        arr.push_back(epiSerialize_Impl_Fetch(v.Right));
        arr.push_back(epiSerialize_Impl_Fetch(v.Bottom));
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
    if constexpr (std::is_fundamental_v<T> ||
                  std::is_enum_v<T> ||
                  std::is_same_v<epiString, T> ||
                  std::is_same_v<epiWString, T>)
    {
        if constexpr (std::is_same_v<epiBool, T>)
        {
            assert(json.is_boolean());
        }
        else if constexpr (std::is_floating_point_v<T>)
        {
            assert(json.is_number_float());
        }
        else if constexpr (std::is_enum_v<T>)
        {
            // TODO: maybe replace enum serialization with a string to preserve restoreability after enum order modifying
            assert(json.is_number_integer());
        }
        else if constexpr (std::is_integral_v<T>)
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
        else if constexpr (std::is_same_v<epiString, T> || std::is_same_v<epiWString, T>)
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
    else if constexpr (std::is_base_of_v<epi::epiBaseArray, T>)
    {
        assert(v.IsEmpty());
        assert(json.is_array());

        for (auto& j : json)
        {
            auto& item = v.PushBack();
            epiDeserialize_Impl_Fetch(item, j);
        }
    }
    else if constexpr (std::is_pointer_v<T>)
    {
        // TODO: implement
    }
    else if constexpr (std::is_same_v<epiVec2f, T> || std::is_same_v<epiVec2d, T> ||
                       std::is_same_v<epiVec2s, T> || std::is_same_v<epiVec2u, T> ||
                       std::is_same_v<epiVec3f, T> || std::is_same_v<epiVec3d, T> ||
                       std::is_same_v<epiVec3s, T> || std::is_same_v<epiVec3u, T> ||
                       std::is_same_v<epiVec4f, T> || std::is_same_v<epiVec4d, T> ||
                       std::is_same_v<epiVec4s, T> || std::is_same_v<epiVec4u, T>)
    {
        assert(json.size() == T::length());
        for (int i = 0; i < T::length(); ++i)
        {
            epiDeserialize_Impl_Fetch(v[i], json[i]);
        }
    }
    else if constexpr (std::is_same_v<epiRect2f, T> || std::is_same_v<epiRect2d, T> ||
                       std::is_same_v<epiRect2s, T> || std::is_same_v<epiRect2u, T>)
    {
        assert(json.size() == 4);
        epiDeserialize_Impl_Fetch(v.Left, json[0]);
        epiDeserialize_Impl_Fetch(v.Top, json[1]);
        epiDeserialize_Impl_Fetch(v.Right, json[2]);
        epiDeserialize_Impl_Fetch(v.Bottom, json[3]);
    }
    else
    {
        static_assert(false, "Unhandled type for seriazliation (epiDeserialize_Impl_Fetch)");
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
