#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiContext.hxx"
EPI_GENREGION_END(include)

#include "EpiUI/uiCamera.h"
#include "EpiUI/uiWidget.h"

#include "EpiGraphics/gfxDrawerPrimitive.h"
#include "EpiGraphics/gfxDrawerText.h"

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class uiContext : public Object
{
EPI_GENREGION_BEGIN(uiContext)
public:
    EPI_GENHIDDEN_uiContext()

    constexpr static MetaTypeID TypeID{0x23154a38};

    enum uiContext_PIDs
    {
        PID_DrawerText = 0xfed690dc,
        PID_DrawerPrimitive = 0x897a35b8,
        PID_Camera = 0x3cb0eb33,
        PID_Children = 0x58e1d3ec,
        PID_COUNT = 4
    };

protected:
    gfxDrawerText m_DrawerText;
    gfxDrawerPrimitive m_DrawerPrimitive;
    uiCamera m_Camera;
    epiPtrArray<uiWidget> m_Children;

EPI_GENREGION_END(uiContext)

public:
    template<typename T, typename ...Args>
    T& Add(Args&& ...args)
    {
        static_assert(std::is_base_of_v<uiWidget, T>);
        return *static_cast<T*>(m_Children.PushBack(new T(std::forward<Args&&>(args)...)));
    }

    void OnMouseMove(const epiVec2f& mouseNDCCoord);
    void OnMousePrimary(const epiVec2f& mouseNDCCoord);
    void OnMouseWheel(epiFloat dZoom);

    void SceneBegin();
    void SceneEnd();

protected:
    uiWidget* WidgetMouseOver() const;

private:
    epiVec2f m_MouseNDCCoord;
};

EPI_NAMESPACE_END()
