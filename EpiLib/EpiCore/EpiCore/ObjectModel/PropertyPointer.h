#pragma once

#include "MetaObject.h"

namespace epi
{

class Object;
class PropertyPointer final
{
public:
    PropertyPointer(const MetaProperty& meta)
        : m_Meta(meta)
    {}

    void* Get(Object* self);
    void Set(Object* self, void* value);

protected:
    const MetaProperty& m_Meta;
};

}
