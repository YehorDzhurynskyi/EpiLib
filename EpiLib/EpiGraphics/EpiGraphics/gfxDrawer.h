#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDrawer.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/Camera/gfxCamera.h"

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class gfxDrawer : public Object
{
EPI_GENREGION_BEGIN(gfxDrawer)
public:
    EPI_GENHIDDEN_gfxDrawer()

    constexpr static MetaTypeID TypeID{0x74765527};

    enum gfxDrawer_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxDrawer)

public:
    gfxDrawer(const gfxCamera& camera);

public:
    virtual void SceneBegin() {}
    virtual void SceneEnd() {}

protected:
    const gfxCamera& m_Camera; // TODO: move to epi
};

EPI_NAMESPACE_END()
