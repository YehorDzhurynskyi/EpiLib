#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxContext.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxVertexArray.h"
#include "EpiGraphics/gfxDrawerPrimitive.h"
#include "EpiGraphics/gfxDrawerText.h"
#include "EpiGraphics/Text/gfxTextManager.h"

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class gfxContext : public Object
{
EPI_GENREGION_BEGIN(gfxContext)

EPI_GENHIDDEN_gfxContext()

public:
    constexpr static epiMetaTypeID TypeID{0x30f166e8};

    enum gfxContext_PIDs
    {
        PID_DrawerText = 0xfed690dc,
        PID_DrawerPrimitive = 0x897a35b8,
        PID_NullVertexArray = 0xee1c89c1,
        PID_Camera = 0x3cb0eb33,
        PID_COUNT = 4
    };

protected:
    gfxDrawerText m_DrawerText{};
    gfxDrawerPrimitive m_DrawerPrimitive{};
    gfxVertexArray m_NullVertexArray{};
    gfxCamera* m_Camera{nullptr};

EPI_GENREGION_END(gfxContext)

public:
    gfxContext();
    gfxContext(const gfxContext& rhs) = delete;
    gfxContext& operator=(const gfxContext& rhs) = delete;
    gfxContext(gfxContext&& rhs) = delete;
    gfxContext& operator=(gfxContext&& rhs) = delete;

public:
    void SceneBegin();
    void SceneEnd();

private:
    // TODO: move to a proper place
    epi::gfxTextManager m_TextManager;
};

EPI_NAMESPACE_END()
