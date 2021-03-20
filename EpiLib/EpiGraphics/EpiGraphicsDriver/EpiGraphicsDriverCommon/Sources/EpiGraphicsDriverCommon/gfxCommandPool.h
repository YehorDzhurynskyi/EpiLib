#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxCommandPool.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class gfxCommandBuffer : public Object
{
EPI_GENREGION_BEGIN(gfxCommandBuffer)

EPI_GENHIDDEN_gfxCommandBuffer()

public:
    constexpr static epiMetaTypeID TypeID{0x29d43d9};

    enum gfxCommandBuffer_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxCommandBuffer)
};

class gfxCommandPool : public Object
{
EPI_GENREGION_BEGIN(gfxCommandPool)

EPI_GENHIDDEN_gfxCommandPool()

public:
    constexpr static epiMetaTypeID TypeID{0x60157c7f};

    enum gfxCommandPool_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxCommandPool)
};

EPI_NAMESPACE_END()
