#pragma once

#include "MetaObject.h"

namespace epi
{

class Object;
class PropertyPointer final
{
public:
    static PropertyPointer CreateFromProperty(Object& self, const MetaProperty* property);
    static PropertyPointer CreateFromArray(epiBaseArray& self, MetaTypeID nestedTypeId, epiU32 idx);

    template<typename T, typename T_ = std::remove_reference_t<std::remove_cv_t<T>>>
    T Get() const
    {
        if constexpr (std::is_base_of_v<Object, T_> ||
                      MetaType::IsMultiDimensional<T_>() ||
                      MetaType::IsString<T_>())
        {
            static_assert(std::is_reference_v<T>);
            epiAssert(MetaType::IsCompound(m_TypeID) ||
                      MetaType::IsMultiDimensional(m_TypeID) ||
                      MetaType::IsString(m_TypeID), "Type missmatch");

            return *reinterpret_cast<T_*>(Get());
        }
        else if constexpr (MetaType::IsFundamental<T_>())
        {
            static_assert(!std::is_reference_v<T>);
            static_assert(!std::is_pointer_v<T>);
            epiAssert(m_TypeID == MetaType::TypeOf<T_>(), "Type missmatch");

            void* v = Get();
            return *reinterpret_cast<T_*>(&v);
        }
        else
        {
            static_assert(false, "Unhandled case!");
        }
    }

    template<typename T, typename T_ = std::remove_reference_t<std::remove_cv_t<T>>>
    void Set(T value)
    {
        if constexpr (std::is_base_of_v<Object, T_> ||
                      MetaType::IsMultiDimensional<T_>() ||
                      MetaType::IsString<T_>())
        {
            static_assert(std::is_reference_v<T>);
            epiAssert(MetaType::IsCompound(m_TypeID) ||
                      MetaType::IsMultiDimensional(m_TypeID) ||
                      MetaType::IsString(m_TypeID), "Type missmatch");

            Set(*reinterpret_cast<T_*>(value));
        }
        else if constexpr (MetaType::IsFundamental<T_>())
        {
            static_assert(!std::is_reference_v<T>);
            static_assert(!std::is_pointer_v<T>);
            epiAssert(m_TypeID == MetaType::TypeOf<T_>(), "Type missmatch");

            Set(*reinterpret_cast<void**>(&value));
        }
        else
        {
            static_assert(false, "Unhandled case!");
        }
    }

    MetaTypeID GetTypeID() const { return m_TypeID; }

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
    MetaTypeID m_TypeID{MetaTypeID_None};
};

}
