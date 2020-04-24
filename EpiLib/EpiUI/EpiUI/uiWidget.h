#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiWidget.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class uiWidget : public Object
{
EPI_GENREGION_BEGIN(uiWidget)
public:
    EPI_GENHIDDEN_uiWidget()

    constexpr static MetaTypeID TypeID{0xac2bf3ee};

    enum uiWidget_PIDs
    {
        PID_Position = 0xbf5a86a3,
        PID_Width = 0x4ddb6a2b,
        PID_Height = 0xf2e1e039,
        PID_BBox = 0xdffc9862,
        PID_COUNT = 4
    };

protected:
    const epiVec2f& GetPosition_Callback() const;
    void SetPosition_Callback(const epiVec2f& value);
    epiFloat GetWidth_Callback() const;
    void SetWidth_Callback(epiFloat value);
    epiFloat GetHeight_Callback() const;
    void SetHeight_Callback(epiFloat value);

protected:
    epiRect2f m_BBox;

EPI_GENREGION_END(uiWidget)

public:
    virtual void OnMousePrimary(const epiVec2f& mouseLocalUICoord) {}
    virtual void OnMouseWheel(epiFloat dZoom) {}
};

EPI_NAMESPACE_END()
