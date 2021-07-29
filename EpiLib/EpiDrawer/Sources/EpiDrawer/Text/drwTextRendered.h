#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDrawer/Text/drwTextRendered.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxImage.h"

EPI_NAMESPACE_BEGIN()

class drwTextRendered : public Object
{
    friend class gfxTextFace;
EPI_GENREGION_BEGIN(drwTextRendered)

EPI_GENHIDDEN_drwTextRendered()

public:
    constexpr static epiMetaTypeID TypeID{0x1c218b1d};

    enum drwTextRendered_PIDs
    {
        PID_Image = 0x4fc2b5b,
        PID_COUNT = 1
    };

protected:
    gfxImage m_Image{};

EPI_GENREGION_END(drwTextRendered)

protected:
    drwTextRendered() = default;

public:
    drwTextRendered(const drwTextRendered& rhs) = delete;
    drwTextRendered& operator=(const drwTextRendered& rhs) = delete;
    drwTextRendered(drwTextRendered&& rhs) = default;
    drwTextRendered& operator=(drwTextRendered&& rhs) = default;
    ~drwTextRendered() = default;
};

EPI_NAMESPACE_END()
