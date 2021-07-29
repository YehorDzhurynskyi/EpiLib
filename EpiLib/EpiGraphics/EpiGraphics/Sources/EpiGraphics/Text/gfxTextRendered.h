#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextRendered.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxImage.h"

EPI_NAMESPACE_BEGIN()

class gfxTextRendered : public Object
{
    friend class gfxTextFace;
EPI_GENREGION_BEGIN(gfxTextRendered)

EPI_GENHIDDEN_gfxTextRendered()

public:
    constexpr static epiMetaTypeID TypeID{0x55328726};

    enum gfxTextRendered_PIDs
    {
        PID_Image = 0x4fc2b5b,
        PID_COUNT = 1
    };

protected:
    gfxImage m_Image{};

EPI_GENREGION_END(gfxTextRendered)

protected:
    gfxTextRendered() = default;

public:
    gfxTextRendered(const gfxTextRendered& rhs) = delete;
    gfxTextRendered& operator=(const gfxTextRendered& rhs) = delete;
    gfxTextRendered(gfxTextRendered&& rhs) = default;
    gfxTextRendered& operator=(gfxTextRendered&& rhs) = default;
    ~gfxTextRendered() = default;
};

EPI_NAMESPACE_END()
