#pragma once

// ============================= PROPERTY =============================
#define epiWritePropertyEx(_Key, _Json, _Value) \
    do                                          \
    {                                           \
        assert(_Json.IsObject());               \
        assert(!_Json.HasMember(#_Key));        \
        _Json[#_Key] = _Value;                  \
    } while (false)                             \

#define epiWriteProperty(_Key, _Json)           \
    epiWritePropertyEx(_Key, _Json, m_##_Key)   \

#define epiReadPropertyEx(_Key, _Type, _Json, _Value)   \
    do                                                  \
    {                                                   \
        assert(_Json.IsObject());                       \
        assert(_Json.HasMember(#_Key));                 \
        const auto it = _Json.FindMember(#_Key);        \
        if (it != _Json.MemberEnd())                    \
        {                                               \
            assert(it->value.Is##_Type());              \
            _Value = it->value.Get##_Type();            \
        }                                               \
    } while (false)                                     \

#define epiReadProperty(_Key, _Type, _Json)          \
    epiReadPropertyEx(_Key, _Type, _Json, m_##_Key)  \

#define epiReadPropertyDefaultEx(_Key, _Type, _Json, _Default, _Value)  \
    do                                                                  \
    {                                                                   \
        assert(_Json.IsObject());                                       \
        const auto it = _Json.FindMember(#_Key);                        \
        if (it != _Json.MemberEnd())                                    \
        {                                                               \
            assert(it->value.Is##_Type());                              \
            _Value = it->value.Get##_Type();                            \
        }                                                               \
        else                                                            \
        {                                                               \
            _Value = _Default;                                          \
        }                                                               \
    } while (false)                                                     \

#define epiReadPropertyDefault(_Key, _Type, _Json, _Default)          \
    epiReadPropertyDefaultEx(_Key, _Type, _Json, _Default, m_##_Key)  \

// ============================= VECTOR =============================
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

// ============================= OBJECT =============================
#define epiReadObject(_Value, _Json) \
    do                              \
    {                               \
        assert(_Json.IsObject());   \
        _Value.Deserialize(_Json);  \
    } while (false)                 \

#define epiReadObjectByKeyEx(_Key, _Value)      \
    do                                          \
    {                                           \
        assert(json.HasMember(#_Key));          \
        const auto it = json.FindMember(#_Key); \
        if (it != json.MemberEnd())             \
        {                                       \
            epiReadObject(_Value, it->value);   \
        }                                       \
    } while (false)                             \

#define epiReadObjectByKey(_Key)         \
    epiReadObjectByKeyEx(_Key, m_##_Key) \

// ============================= ARRAY =============================
#define epiReadArrayBegin(_Json)                        \
    do                                                  \
    {                                                   \
        assert(_Json.IsArray());                        \
        epiS32 index = -1;                              \
        for (const json_t& itemJson : _Json.GetArray()) \
        {                                               \
            ++index;                                    \

#define epiReadArrayEnd()   \
        }                   \
    } while (false)         \

#define epiReadArrayVectorBeginEx(_Key, _Json, _Value)  \
do                                                      \
{                                                       \
    assert(_Json.HasMember(#_Key));                     \
    const auto it = _Json.FindMember(#_Key);            \
    if (it != _Json.MemberEnd())                        \
    {                                                   \
        epiReadArrayBegin(it->value);                   \
        auto& item = _Value.Push();                     \

#define epiReadArrayVectorBegin(_Key, _Json)         \
    epiReadArrayVectorBeginEx(_Key, _Json, m_##_Key) \

#define epiReadArrayVectorEnd() \
        epiReadArrayEnd();      \
    }                           \
} while (false)                 \

#define epiReadArray(_Key, _Json)           \
do                                          \
{                                           \
    assert(m_##_Key.empty());               \
    assert(_Json.HasMember(#_Key));         \
    const json_t& arr = _Json[#_Key];       \
    m_##_Key.reserve(arr.size());           \
    for (auto& j : arr)                     \
    {                                       \
        auto& v = m_##_Key.emplace_back();  \
        v.Deserialization(j);               \
    }                                       \
}                                           \
while (false)                               \

#define epiWriteArray(_Key, _Json)          \
do                                          \
{                                           \
    assert(!_Json.HasMember(#_Key));        \
    json_t& arr = _Json[#_Key];             \
    for (auto& v : m_##_Key)                \
    {                                       \
        arr.push_back(json_t::object());    \
        v.Serialization(arr.back());        \
    }                                       \
}                                           \
while (false)                               \

// ============================= MAP =============================
#define epiReadMapBegin(_Json)                                      \
    do                                                              \
    {                                                               \
        assert(_Json.IsObject());                                   \
    for (json_t::ConstMemberIterator iter = _Json.MemberBegin();    \
        iter != _Json.MemberEnd();                                  \
        ++iter)                                                     \
    {                                                               \
        const std::string& k = iter->name.GetString();              \
        const json_t& v = iter->value;                              \

#define epiReadHashMapBegin(_Key, _Json)        \
do                                              \
{                                               \
    assert(_Json.HasMember(#_Key));             \
    const auto it = _Json.FindMember(#_Key);    \
    if (it != _Json.MemberEnd())                \
    {                                           \
        epiReadMapBegin(it->value);             \

#define epiReadHashMapEnd()     \
            epiReadMapEnd();    \
        }                       \
    } while (false)             \

#define epiReadMapEnd() \
        }               \
    } while (false)     \
