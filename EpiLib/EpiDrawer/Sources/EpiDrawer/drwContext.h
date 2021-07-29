#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDrawer/drwContext.hxx"
EPI_GENREGION_END(include)

#include "EpiDrawer/drwDrawerPrimitive.h"
#include "EpiDrawer/drwDrawerText.h"
#include "EpiDrawer/Text/drwTextManager.h"

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class drwContext : public Object
{
EPI_GENREGION_BEGIN(drwContext)

EPI_GENHIDDEN_drwContext()

public:
    constexpr static epiMetaTypeID TypeID{0xf3cadc3a};

    enum drwContext_PIDs
    {
        PID_DrawerText = 0xfed690dc,
        PID_DrawerPrimitive = 0x897a35b8,
        PID_Camera = 0x3cb0eb33,
        PID_COUNT = 3
    };

protected:
    drwDrawerText m_DrawerText{};
    drwDrawerPrimitive m_DrawerPrimitive{};
    drwCamera* m_Camera{nullptr};

EPI_GENREGION_END(drwContext)

public:
    drwContext();
    drwContext(const drwContext& rhs) = delete;
    drwContext& operator=(const drwContext& rhs) = delete;
    drwContext(drwContext&& rhs) = delete;
    drwContext& operator=(drwContext&& rhs) = delete;

public:
    void SceneBegin();
    void SceneEnd();

private:
    // TODO: move to a proper place
    drwTextManager m_TextManager;
};

EPI_NAMESPACE_END()
