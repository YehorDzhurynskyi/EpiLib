#pragma once

#include <type_traits>
#include "MetaObject.h"

namespace epi
{

template<typename T>
class PropertyPointer final
{
public:
    T Get(void* self);
    void Set(void* self, T value);

protected:
    void* m_PtrWrite;
    void* m_PtrRead;
};

template<typename T>
T PropertyPointer<T>::Get(void* self)
{
    using func = T (*)();
    return ((func)m_PtrRead)(self);
}

template<typename T>
void PropertyPointer<T>::Set(void* self, T value)
{
    using func = void (*)(T);
    ((func)m_PtrWrite)(self, value);
}

}
