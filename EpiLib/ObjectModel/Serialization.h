#pragma once

// ============================= PROPERTY =============================
#if 0
#define epiWritePropertyEx(_Key, _Json, _Value) \
    do                                          \
    {                                           \
        assert(_Json.IsObject());               \
        assert(!_Json.HasMember(#_Key));        \
        _Json[#_Key] = _Value;                  \
    } while (false)                             \

#else
#define epiWritePropertyEx(_Key, _Json, _Value) assert(!"Not implemented!")
#endif

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
#define epiReadArrayBegin(_Key, _Json)                                  \
do                                                                      \
{                                                                       \
    assert(_Json.HasMember(#_Key));                                     \
    assert(_Json.IsArray());                                            \
    const auto it = _Json.FindMember(#_Key);                            \
    for (json_t::ConstMemberIterator iter = it->value.MemberBegin();    \
        iter != it->value.MemberEnd();                                  \
        ++iter)                                                         \
    {                                                                   \
        const auto& v = iter->value;                                    \

#define epiReadArrayEnd()   \
    }                       \
} while (false)             \

#define epiReadArray(_Key, _Json)           \
    epiReadArrayBegin(_Key, _Json)          \
    auto& item = m_##_Key.emplace_back();   \
    item.Deserialization(v);                \
    epiReadArrayEnd()                       \

#if 0
#define epiWriteArray(_Key, _Json)          \
do                                          \
{                                           \
    assert(!_Json.HasMember(#_Key));        \
    json_t& arr = _Json[#_Key];             \
    epiS32 index = 0;                       \
    for (auto& v : m_##_Key)                \
    {                                       \
        rapidjson::Value j(rapidjson::kObjectType); \
        v.Serialization(j);        \
        arr[index++] = j;    \
    }                                       \
}                                           \
while (false)                               \

#else
#define epiWriteArray(_Key, _Json) assert(!"Not implemented!")
#endif

// ============================= MAP =============================
#define epiReadMapBegin(_Key, _Json)                                    \
do                                                                      \
{                                                                       \
    assert(m_##_Key.empty());                                           \
    assert(_Json.IsObject());                                           \
    assert(_Json.HasMember(#_Key));                                     \
    const auto it = _Json.FindMember(#_Key);                            \
    for (json_t::ConstMemberIterator iter = it->value.MemberBegin();    \
        iter != it->value.MemberEnd();                                  \
        ++iter)                                                         \
    {                                                                   \
        const std::string& k = iter->name.GetString();                  \
        const json_t& v = iter->value;                                  \

#define epiReadMapEnd() \
    }                   \
} while (false)         \

#define epiReadMap(_Key, _Json)     \
    epiReadMapBegin(_Key, _Json)    \
    auto& item = m_##_Key[k];       \
    item.Deserialization(v);        \
    epiReadMapEnd()                 \

#if 0
#define epiWriteMap(_Key, _Json)                    \
do                                                  \
{                                                   \
    assert(!_Json.HasMember(#_Key));                \
    auto& map = _Json[#_Key];                       \
    for (auto& [k, v] : m_##_Key)                   \
    {                                               \
        jsot_t j(kJsonType); \
        v.Serialization(j);                         \
        map[k] = j;    \
    }                                               \
} while (false)                                     \

#else
#define epiWriteMap(_Key, _Json) assert(!"Not implemented!")
#endif
