#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextInstance.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class gfxTextInstance : public Object
{
    friend class gfxTextFont;
EPI_GENREGION_BEGIN(gfxTextInstance)
public:
    EPI_GENHIDDEN_gfxTextInstance()

    constexpr static MetaTypeID TypeID{0x124f2235};

    enum gfxTextInstance_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxTextInstance)

protected:
    gfxTextInstance() = default;

protected:
    
};

EPI_NAMESPACE_END()
