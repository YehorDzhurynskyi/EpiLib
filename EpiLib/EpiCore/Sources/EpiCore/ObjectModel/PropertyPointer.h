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

    if constexpr (MetaType::IsCompound<T>() || MetaType::IsString<T>() || MetaType::IsMultiDimensional<T>())
    {
        epiAssert(MetaType::IsCompound(m_TypeID) || MetaType::IsString(m_TypeID) || MetaType::IsMultiDimensional(m_TypeID), "Type missmatch");

        return *reinterpret_cast<T*>(Get_Static<T>());
    }
    else if constexpr (MetaType::IsFundamental<T>())
    {
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
void PropertyPointer::Set(std::conditional_t<MetaType::IsFundamental<T>(), T, const T&> value)
{
    static_assert(std::is_same_v<std::decay_t<T>, T>);
    static_assert(!std::is_pointer_v<T>);
    epiAssert(IsWritable());

    if constexpr (MetaType::IsCompound<T>() || MetaType::IsString<T>() || MetaType::IsMultiDimensional<T>())
    {
        epiAssert(MetaType::IsCompound(m_TypeID) || MetaType::IsString(m_TypeID) || MetaType::IsMultiDimensional(m_TypeID), "Type missmatch");

        Set_Static<T>(reinterpret_cast<const void*>(&value));
    }
    else if constexpr (MetaType::IsFundamental<T>())
    {
        static_assert(sizeof(T) <= sizeof(void*));

        Set_Static<T>(*reinterpret_cast<void**>(&value));
    }
    else
    {
        static_assert(false, "Unhandled case!");
    }
}

#define GetCallback(_x) { _x v = (*((_x (**)(Object*))addr))(m_Self); value = (void*)*((epiSize_t*)&v); }
#define GetCallback_Ref(_x) { const _x& v = (*((const _x& (**)(Object*))addr))(m_Self); value = (void*)&v; }

template<typename T>
void* PropertyPointer::Get_Static() const
{
    epiAssert(IsReadable());

    void* value = nullptr;

    if (m_Form == Form::ArrayElem)
    {
        value = m_ValueAddr;
    }
    else if (m_Form == Form::Property)
    {
        void* addr = (epiByte*)m_Self + (size_t)m_Meta->m_PtrRead;
        if (m_Meta->m_Flags.ReadCallback)
        {
            if constexpr (MetaType::IsFundamental<T>())
            {
                epiAssert(MetaType::IsFundamental(m_Meta->m_TypeID));
                GetCallback(T);
            }
            else if constexpr (MetaType::IsString<T>())
            {
                epiAssert(MetaType::IsString(m_Meta->m_TypeID));
                GetCallback_Ref(T);
            }
            else if constexpr (MetaType::IsMultiDimensional<T>())
            {
                epiAssert(MetaType::IsMultiDimensional(m_Meta->m_TypeID));
                GetCallback_Ref(T);
            }
            else if constexpr (MetaType::IsCompound<T>())
            {
                epiAssert(MetaType::IsCompound(m_Meta->m_TypeID));
                GetCallback_Ref(T);
            }
            else
            {
                static_assert(false, "Unexpected type id");
            }
        }
        else
        {
            if constexpr (MetaType::IsFundamental<T>())
            {
                epiAssert(MetaType::IsFundamental(m_Meta->m_TypeID));
                value = (void*)*((void**)addr);
            }
            else if constexpr (MetaType::IsString<T>())
            {
                epiAssert(MetaType::IsString(m_Meta->m_TypeID));
                value = addr;
            }
            else if constexpr (MetaType::IsMultiDimensional<T>())
            {
                epiAssert(MetaType::IsMultiDimensional(m_Meta->m_TypeID));
                value = addr;
            }
            else if constexpr (MetaType::IsCompound<T>())
            {
                epiAssert(MetaType::IsCompound(m_Meta->m_TypeID));
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

#undef GetCallback
#undef GetCallback_Ref

#define SetCallback(_x) (*((void (**)(Object*, _x))addr))(m_Self, *((_x*)&value))
#define SetCallback_Ref(_x) (*((void (**)(Object*, const _x&))addr))(m_Self, *((const _x*)value))

template<typename T>
void PropertyPointer::Set_Static(const void* value)
{
    epiAssert(IsWritable());

    if (m_Form == Form::ArrayElem)
    {
        memcpy_s(m_ValueAddr, m_SizeOf, &reinterpret_cast<Object&>(value), m_SizeOf);
    }
    else if (m_Form == Form::Property)
    {
        void* addr = (epiByte*)m_Self + (size_t)m_Meta->m_PtrWrite;
        if (m_Meta->m_Flags.WriteCallback)
        {
            if constexpr (MetaType::IsFundamental<T>())
            {
                epiAssert(MetaType::IsFundamental(m_Meta->m_TypeID));
                SetCallback(T);
            }
            else if constexpr (MetaType::IsString<T>())
            {
                epiAssert(MetaType::IsString(m_Meta->m_TypeID));
                SetCallback_Ref(T);
            }
            else if constexpr (MetaType::IsMultiDimensional<T>())
            {
                epiAssert(MetaType::IsMultiDimensional(m_Meta->m_TypeID));
                SetCallback_Ref(T);
            }
            else if constexpr (MetaType::IsCompound<T>())
            {
                epiAssert(MetaType::IsCompound(m_Meta->m_TypeID));
                SetCallback_Ref(T);
            }
            else
            {
                static_assert(false, "Unexpected type id");
            }
        }
        else
        {
            if constexpr (MetaType::IsFundamental<T>())
            {
                epiAssert(MetaType::IsFundamental(m_Meta->m_TypeID));
                *((T*)addr) = *((T*)&value);
            }
            else if constexpr (MetaType::IsString<T>())
            {
                epiAssert(MetaType::IsString(m_Meta->m_TypeID));
                *((T*)addr) = *((const T*)value);
            }
            else if constexpr (MetaType::IsMultiDimensional<T>())
            {
                epiAssert(MetaType::IsMultiDimensional(m_Meta->m_TypeID));
                *((T*)addr) = *((const T*)value);
            }
            else if constexpr (MetaType::IsCompound<T>())
            {
                epiAssert(MetaType::IsCompound(m_Meta->m_TypeID));
                *((T*)addr) = *((const T*)value);
            }
            else
            {
                static_assert(false, "Unexpected type id");
            }
        }
    }
}

#undef SetCallback
#undef SetCallback_Ref

EPI_NAMESPACE_END()
