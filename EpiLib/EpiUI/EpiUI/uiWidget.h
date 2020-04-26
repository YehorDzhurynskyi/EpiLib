#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiWidget.hxx"
EPI_GENREGION_END(include)

#include "EpiUI/uiAction.h"

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
        PID_MouseLocalUICoord = 0xb08d2bad,
        PID_BBox = 0xdffc9862,
        PID_Parent = 0x3a226579,
        PID_Children = 0x58e1d3ec,
        PID_COUNT = 7
    };

protected:
    const epiVec2f& GetPosition_Callback() const;
    void SetPosition_Callback(const epiVec2f& value);
    epiFloat GetWidth_Callback() const;
    void SetWidth_Callback(epiFloat value);
    epiFloat GetHeight_Callback() const;
    void SetHeight_Callback(epiFloat value);
    epiVec2f GetMouseLocalUICoord_Callback() const;

protected:
    epiRect2f m_BBox;
    uiWidget* m_Parent{nullptr};
    epiPtrArray<uiWidget> m_Children;

EPI_GENREGION_END(uiWidget)

public:
    virtual void Update();

    template<typename T, typename ...Args>
    T& Add(Args&& ...args)
    {
        static_assert(std::is_base_of_v<uiWidget, T>);
        T& widget = *static_cast<T*>(m_Children.PushBack(new T(std::forward<Args&&>(args)...)));
        widget.m_Parent = this;
        return widget;
    }

    virtual void OnMousePrimary(MouseAction action);
    virtual void OnMouseWheel(epiFloat dZoom);
    virtual void OnMouseFocus(epiBool focused);

protected:
    virtual epiVec2f GetMouseLocalUICoord_Internal() const;

    uiWidget* WidgetOverMouse(const epiVec2f& mouseUICoord) const;
};

EPI_NAMESPACE_END()
