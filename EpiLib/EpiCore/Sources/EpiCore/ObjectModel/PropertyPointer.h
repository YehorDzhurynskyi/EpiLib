#pragma once

#include "MetaObject.h"

EPI_NAMESPACE_BEGIN()

class Object;
class PropertyPointer final
{
public:
    static PropertyPointer CreateFromProperty(Object& self, const MetaProperty* property);
    static PropertyPointer CreateFromArray(epiBaseArray& self, epiMetaTypeID nestedTypeId, epiU32 idx);

    template<typename T>
    auto Get() const -> std::conditional_t<MetaType::IsFundamental<T>(), T, T&>;

    template<typename T>
    void Set(std::conditional_t<MetaType::IsFundamental<T>(), T, const T&> value);

    epiBool IsReadable() const;
    epiBool IsWritable() const;

    epiMetaTypeID GetTypeID() const;

protected:
    void* Get() const;
    void Set(void* value);

protected:
    union
    {
        struct
        {
            const MetaProperty* m_Meta;
            Object* m_Self;
        };

        struct
        {
            void* m_ValueAddr;
            size_t m_SizeOf;
        };
    };

    enum class Form
    {
        None,
        Property,
        ArrayElem
    };

    Form m_Form{Form::None};
    epiMetaTypeID m_TypeID{epiMetaTypeID_None};
};

template<typename T>
auto PropertyPointer::Get() const -> std::conditional_t<MetaType::IsFundamental<T>(), T, T&>
{
    static_assert(std::is_same_v<std::decay_t<T>, T>, "Please remove the reference, cv-qualifiers from provided template argument");
    static_assert(!std::is_pointer_v<T>);
    epiAssert(IsReadable());

    if constexpr (std::is_base_of_v<Object, T> || MetaType::IsMultiDimensional<T>() || MetaType::IsString<T>())
    {
        epiAssert(MetaType::IsCompound(m_TypeID) || MetaType::IsMultiDimensional(m_TypeID) || MetaType::IsString(m_TypeID), "Type missmatch");

        return *reinterpret_cast<T*>(Get());
    }
    else if constexpr (MetaType::IsFundamental<T>())
    {
        static_assert(sizeof(T) <= sizeof(void*));

        void* v = Get();
        return *reinterpret_cast<T*>(&v);
    }
    else
    {
        static_assert(false, "Unhandled case!");
    }
}

template<typename T>
void PropertyPointer::Set(std::conditional_t<MetaType::IsFundamental<T>(), T, const T&> value)
{
    static_assert(std::is_same_v<std::decay_t<T>, T>);
    static_assert(!std::is_pointer_v<T>);
    epiAssert(IsWritable());

    if constexpr (std::is_base_of_v<Object, T> || MetaType::IsMultiDimensional<T>() || MetaType::IsString<T>())
    {
        epiAssert(MetaType::IsCompound(m_TypeID) || MetaType::IsMultiDimensional(m_TypeID) || MetaType::IsString(m_TypeID), "Type missmatch");

        Set(const_cast<void*>(reinterpret_cast<const void*>(&value)));
    }
    else if constexpr (MetaType::IsFundamental<T>())
    {
        static_assert(sizeof(T) <= sizeof(void*));

        Set(*reinterpret_cast<void**>(&value));
    }
    else
    {
        static_assert(false, "Unhandled case!");
    }
}

EPI_NAMESPACE_END()
