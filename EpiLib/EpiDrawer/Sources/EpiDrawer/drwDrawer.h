#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDrawer/drwDrawer.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class drwDrawer : public Object
{
EPI_GENREGION_BEGIN(drwDrawer)

EPI_GENHIDDEN_drwDrawer()

public:
    constexpr static epiMetaTypeID TypeID{0x434226da};

    enum drwDrawer_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(drwDrawer)
};

EPI_NAMESPACE_END()
