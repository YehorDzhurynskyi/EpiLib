#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiContext.hxx"
EPI_GENREGION_END(include)

#include "EpiUI/uiCamera.h"
#include "EpiUI/uiPage.h"

#include "EpiGraphics/gfxContext.h"

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class uiContext : public Object
{
EPI_GENREGION_BEGIN(uiContext)

EPI_GENHIDDEN_uiContext()

public:
    constexpr static epiMetaTypeID TypeID{0x23154a38};

    enum uiContext_PIDs
    {
        PID_GFXContext = 0x42b85cd,
        PID_Page = 0xb438191e,
        PID_MouseUICoord = 0x668167cc,
        PID_COUNT = 3
    };

protected:
    epiVec2f GetMouseUICoord_Callback() const;

protected:
    gfxContext m_GFXContext{};
    uiPage m_Page{};

EPI_GENREGION_END(uiContext)

public:
    void Update();
    void Draw();

    void OnMouseMove(const epiVec2f& mouseNDCCoord);
    void OnMousePrimary(uiMouseAction action);
    void OnMouseWheel(epiFloat dZoom);
    void OnMouseFocus(epiBool focused);
    void OnResize(const epiRect2f& frame);

protected:
    epiVec2f CalcMouseUICoordFromMouseNDCCoord(const epiVec2f& mouseNDCCoord) const;

private:
    epiVec2f m_MouseNDCCoord;
};

EPI_NAMESPACE_END()
