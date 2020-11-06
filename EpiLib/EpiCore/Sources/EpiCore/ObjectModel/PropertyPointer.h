#pragma once

#include "MetaObject.h"


EPI_NAMESPACE_BEGIN()

enum PropertyPointerValueStringStyle
{
    PropertyPointerValueStringStyle_None = 0,
    PropertyPointerValueStringStyle_String_Quoted = (1 << 1),
    PropertyPointerValueStringStyle_Boolean_ON_OFF = (1 << 2),
    PropertyPointerValueStringStyle_Boolean_True_False = (1 << 3),
    PropertyPointerValueStringStyle_Boolean_Enabled_Disabled = (1 << 4),
    PropertyPointerValueStringStyle_Size_Repr_Bytes = (1 << 5)
};

template<typename T>
using PropertyPointerGet_t = std::conditional_t<MetaType::IsFundamental<T>() || MetaType::IsPointer<T>(), T, T&>;

template<typename T>
using PropertyPointerSet_t = std::conditional_t<MetaType::IsFundamental<T>() || MetaType::IsPointer<T>(), T, const T&>;

class Object;
class PropertyPointer final
{
public:
    static PropertyPointer CreateFromProperty(Object& self, const MetaProperty* property);
    static PropertyPointer CreateFromProperty(const Object& self, const MetaProperty* property);
    static PropertyPointer CreateFromArray(epiBaseArray& self, epiMetaTypeID nestedTypeId, epiU32 idx);

    template<typename T, typename Nested>
    static PropertyPointer CreateFromArrayInplace(T& self, epiU32 idx);

    epiString GetValueString(epiS32 style = 0) const;

    template<typename T>
    PropertyPointerGet_t<T> Get() const;

    template<typename T>
    void Set(PropertyPointerSet_t<T> value);

    epiBool IsReadable() const;
    epiBool IsWritable() const;

    epiMetaTypeID GetTypeID() const;

protected:
    template<typename T>
    void* Get_Static() const;

    template<typename T>
    void Set_Static(const void* value);

#if 0
    // NOTE: runtime lookup
    // uncomment if compile-time type deduction isn't enough
    void* Get_Dynamic() const;
    void Set_Dynamic(void* value);
#endif

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
            const MetaProperty* m_Meta;
            const Object* m_SelfConst;
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
        PropertyConst,
        ArrayElem,
        InplaceElem
    };

    Form m_Form{Form::None};
    epiMetaTypeID m_TypeID{epiMetaTypeID_None};
};

template<typename T>
PropertyPointerGet_t<T> PropertyPointer::Get() const
{
    static_assert(std::is_same_v<std::decay_t<T>, T>, "Please remove the reference, cv-qualifiers from provided template argument");
    epiAssert(IsReadable());

    if constexpr (MetaType::IsString<T>() || MetaType::IsMultiDimensional<T>() || MetaType::IsCompound<T>())
    {
        epiAssert(MetaType::IsString(m_TypeID) || MetaType::IsMultiDimensional(m_TypeID) || MetaType::IsCompound(m_TypeID), "Type missmatch");

        return *reinterpret_cast<T*>(Get_Static<T>());
    }
    else if constexpr (MetaType::IsFundamental<T>() || MetaType::IsPointer<T>())
    {
        epiAssert(MetaType::IsFundamental(m_TypeID) || MetaType::IsPointer(m_TypeID), "Type missmatch");
        static_assert(sizeof(T) <= sizeof(void*));

        void* v = Get_Static<T>();
        return *reinterpret_cast<T*>(&v);
    }
    else
    {
        static_assert(false, "Unhandled case!");
    }
}

template<typename T>
void PropertyPointer::Set(PropertyPointerSet_t<T> value)
{
    static_assert(std::is_same_v<std::decay_t<T>, T>);
    epiAssert(IsWritable());

    if constexpr (MetaType::IsString<T>() || MetaType::IsMultiDimensional<T>() || MetaType::IsCompound<T>())
    {
        epiAssert(MetaType::IsString(m_TypeID) || MetaType::IsMultiDimensional(m_TypeID) || MetaType::IsCompound(m_TypeID), "Type missmatch");

        Set_Static<T>(reinterpret_cast<const void*>(&value));
    }
    else if constexpr (MetaType::IsFundamental<T>() || MetaType::IsPointer<T>())
    {
        epiAssert(MetaType::IsFundamental(m_TypeID) || MetaType::IsPointer(m_TypeID), "Type missmatch");
        static_assert(sizeof(T) <= sizeof(void*));

        Set_Static<T>(*reinterpret_cast<void**>(&value));
    }
    else
    {
        static_assert(false, "Unhandled case!");
    }
}

template<typename T>
void* PropertyPointer::Get_Static() const
{
    epiAssert(IsReadable());

    void* value = nullptr;

    if (m_Form == Form::ArrayElem || m_Form == Form::InplaceElem)
    {
        if constexpr (MetaType::IsFundamental<T>() || MetaType::IsPointer<T>())
        {
            value = (void*)*((void**)m_ValueAddr);
        }
        else if constexpr (MetaType::IsString<T>() || MetaType::IsMultiDimensional<T>() || MetaType::IsCompound<T>())
        {
            value = m_ValueAddr;
        }
        else
        {
            static_assert(false, "Unexpected type id");
        }
    }
    else if (m_Form == Form::Property || m_Form == Form::PropertyConst)
    {
        void* addr = (epiByte*)m_Self + (size_t)m_Meta->m_PtrRead;
        if (m_Meta->m_Flags.ReadCallback)
        {
            if constexpr (MetaType::IsFundamental<T>() || MetaType::IsPointer<T>())
            {
                T v = (*((T(**)(Object*))addr))(m_Self);
                value = (void*)*((epiSize_t*)&v);
            }
            else if constexpr (MetaType::IsString<T>() || MetaType::IsMultiDimensional<T>() || MetaType::IsCompound<T>())
            {
                const T& v = (*((const T& (**)(Object*))addr))(m_Self);
                value = (void*)&v;
            }
            else
            {
                static_assert(false, "Unexpected type id");
            }
        }
        else
        {
            if constexpr (MetaType::IsFundamental<T>() || MetaType::IsPointer<T>())
            {
                value = (void*)*((void**)addr);
            }
            else if constexpr (MetaType::IsString<T>() || MetaType::IsMultiDimensional<T>() || MetaType::IsCompound<T>())
            {
                value = addr;
            }
            else
            {
                static_assert(false, "Unexpected type id");
            }
        }
    }

    return value;
}

template<typename T>
void PropertyPointer::Set_Static(const void* value)
{
    epiAssert(IsWritable());

    if (m_Form == Form::ArrayElem)
    {
        memcpy_s(m_ValueAddr, m_SizeOf, &reinterpret_cast<Object&>(value), m_SizeOf);
    }
    else if (m_Form == Form::InplaceElem)
    {
        memcpy_s(m_ValueAddr, m_SizeOf, &value, m_SizeOf);
    }
    else if (m_Form == Form::Property)
    {
        void* addr = (epiByte*)m_Self + (size_t)m_Meta->m_PtrWrite;
        if (m_Meta->m_Flags.WriteCallback)
        {
            if constexpr (MetaType::IsFundamental<T>() || MetaType::IsPointer<T>())
            {
                (*((void (**)(Object*, T))addr))(m_Self, *((T*)&value));
            }
            else if constexpr (MetaType::IsString<T>() || MetaType::IsMultiDimensional<T>() || MetaType::IsCompound<T>())
            {
                (*((void (**)(Object*, const T&))addr))(m_Self, *((const T*)value));
            }
            else
            {
                static_assert(false, "Unexpected type id");
            }
        }
        else
        {
            if constexpr (MetaType::IsFundamental<T>() || MetaType::IsPointer<T>())
            {
                *((T*)addr) = *((T*)&value);
            }
            else if constexpr (MetaType::IsString<T>() || MetaType::IsMultiDimensional<T>() || MetaType::IsCompound<T>())
            {
                *((T*)addr) = *((const T*)value);
            }
            else
            {
                static_assert(false, "Unexpected type id");
            }
        }
    }
}

template<typename T, typename Nested>
static PropertyPointer PropertyPointer::CreateFromArrayInplace(T& self, epiU32 idx)
{
    PropertyPointer ptr;
    ptr.m_ValueAddr = reinterpret_cast<epiByte*>(&self) + sizeof(Nested) * idx;
    ptr.m_SizeOf = sizeof(Nested);
    ptr.m_Form = Form::InplaceElem;

    constexpr epiMetaTypeID nestedTypeID = MetaType::TypeOf<Nested>();
    epiAssertStatic(nestedTypeID != epiMetaTypeID_None);

    ptr.m_TypeID = nestedTypeID;

    return ptr;
}

EPI_NAMESPACE_END()
