#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiBlueprint/Drawer/bpNodeDrawerImageProvider.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxDrawer.h"

EPI_NAMESPACE_BEGIN()

class bpNodeDrawerImageProvider : public gfxDrawer
{
EPI_GENREGION_BEGIN(bpNodeDrawerImageProvider)

EPI_GENHIDDEN_bpNodeDrawerImageProvider()

public:
    constexpr static epiMetaTypeID TypeID{0x243fa401};

    enum bpNodeDrawerImageProvider_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(bpNodeDrawerImageProvider)
};

EPI_NAMESPACE_END()
