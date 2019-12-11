#pragma once

// ============================= PROPERTY =============================
#define epiWriteProperty(_Key, _Json)           \
{                                               \
    assert(_Json.is_object());                  \
    assert(_Json.find(#_Key) == _Json.end());   \
    _Json[#_Key] = m_##_Key;                    \
}                                               \

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

// ============================= VECTOR =============================
#if 0 // TODO: implement

#define epiReadVectorEx(_Key, _ElType, _Json, _Value, _N)   \
    do                                                      \
    {                                                       \
        assert(_Json.IsObject());                           \
        assert(_Json.HasMember(#_Key));                     \
        const auto it = _Json.FindMember(#_Key);            \
        if (it != _Json.MemberEnd())                        \
        {                                                   \
            assert(it->value.IsArray());                    \
            auto vec = it->value.GetArray();                \
            assert(vec.Size() == _N);                       \
            for (int i = 0; i < _N; ++i)                    \
            {                                               \
                assert(vec[i].Is##_ElType());               \
                _Value[i] = vec[i].Get##_ElType();          \
            }                                               \
        }                                                   \
    } while (false)                                         \

#define epiReadVector2Ex(_Key, _ElType, _Json, _Value)   \
    epiReadVectorEx(_Key, _ElType, _Json, _Value, 2)     \

#define epiReadVector2(_Key, _ElType, _Json)             \
    epiReadVector2Ex(_Key, _ElType, _Json, m_##_Key)     \

#define epiReadVector3Ex(_Key, _ElType, _Json, _Value)   \
    epiReadVectorEx(_Key, _ElType, _Json, _Value, 3)     \

#define epiReadVector3(_Key, _ElType, _Json)             \
    epiReadVector3Ex(_Key, _ElType, _Json, m_##_Key)     \

#define epiReadVector4Ex(_Key, _ElType, _Json, _Value)   \
    epiReadVectorEx(_Key, _ElType, _Json, _Value, 4)     \

#define epiReadVector4(_Key, _ElType, _Json)             \
    epiReadVector4Ex(_Key, _ElType, _Json, m_##_Key)     \

#endif

// ============================= OBJECT =============================

#define epiReadObject(_Key, _Json)              \
{                                               \
    assert(_Json.is_object());                  \
    assert(_Json[#_Key].is_object());           \
    assert(_Json.find(#_Key) != _Json.end());   \
    m_##_Key.Deserialization(_Json[#_Key]);     \
}                                               \

#define epiWriteObject(_Key, _Json)             \
{                                               \
    assert(_Json.is_object());                  \
    assert(_Json.find(#_Key) == _Json.end());   \
    json_t jsonObject = json_t::object();       \
    m_##_Key.Serialization(jsonObject);         \
    _Json[#_Key] = jsonObject;                  \
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

#define epiWriteArray(_Key, _Json)              \
{                                               \
    assert(_Json.is_object());                  \
    assert(_Json.find(#_Key) == _Json.end());   \
    auto arr = json_t::array();                 \
    for (auto& v : m_##_Key)                    \
    {                                           \
        auto j = json_t::object();              \
        v.Serialize(j);                         \
        arr.push_back(j);                       \
    }                                           \
    _Json[#_Key] = arr;                         \
}                                               \

// ============================= MAP =============================
#define epiReadMap(_Key, _Json)                 \
{                                               \
    assert(m_##_Key.empty());                   \
    assert(_Json.is_object());                  \
    assert(_Json.find(#_Key) != _Json.end());   \
    assert(_Json[#_Key].is_object());           \
    for (auto& [k, v] : _Json[#_Key].items())   \
    {                                           \
        auto& item = m_##_Key[k];               \
        item.Deserialize(v);                    \
    }                                           \
}                                               \

#define epiWriteMap(_Key, _Json)                \
{                                               \
    assert(_Json.is_object());                  \
    assert(_Json.find(#_Key) == _Json.end());   \
    auto map = json_t::object();                \
    for (auto& [k, v] : m_##_Key)               \
    {                                           \
        auto j = json_t::object();              \
        v.Serialize(j);                         \
        map[k] = j;                             \
    }                                           \
    _Json[#_Key] = map;                         \
}                                               \
