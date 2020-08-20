#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiWidget.hxx"
EPI_GENREGION_END(include)

#include "EpiUI/uiAction.h"

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

// TODO: move to epi
enum uiSizePolicy
{
    // Description: The `SizeHint` is the only acceptable alternative,
    // so the widget can never grow or shrink
    // (e.g. the vertical direction of a push button).
    uiSizePolicy_Fixed = 0x1,

    // Description: The `SizeHint` is minimal, and sufficient. The widget can be expanded,
    // but there is no advantage to it being larger (e.g. the horizontal
    // direction of a push button). It cannot be smaller than the size provided by `SizeHint`.
    uiSizePolicy_Minimum = 0x2,

    // Description: The `SizeHint` is a maximum.The widget can be shrunk any amount
    // without detriment if other widgets need the space(e.g.a separator line).
    // It cannot be larger than the size provided by `SizeHint`.
    uiSizePolicy_Maximum = 0x4,

    // Description: The `SizeHint` is best, but the widget can be shrunk and
    // still be useful. The widget can be expanded, but there is no advantage
    // to it being larger than `SizeHint` (the default uiWidget policy).
    uiSizePolicy_Preferred = 0x8,

    // Description: The `SizeHint` is a sensible size, but the widget can be
    // shrunkand still be useful.The widget can make use of extra space, so
    // it should get as much space as possible(e.g.the horizontal direction of a horizontal slider).
    uiSizePolicy_Expanding = 0x10,

    // Description: The `SizeHint` is minimal, and sufficient.The widget can make use
    // of extra space, so it should get as much space
    // as possible(e.g.the horizontal direction of a horizontal slider).
    uiSizePolicy_MinimumExpanding = 0x20,

    // Description: The `SizeHint` is ignored. The widget will get as much space as possible.
    uiSizePolicy_Ignored = 0x40,

    uiSizePolicy_Grow_Mask = uiSizePolicy_Minimum | uiSizePolicy_Preferred | uiSizePolicy_Expanding | uiSizePolicy_MinimumExpanding | uiSizePolicy_Ignored,
    uiSizePolicy_Shrink_Mask = uiSizePolicy_Maximum | uiSizePolicy_Preferred | uiSizePolicy_Expanding | uiSizePolicy_Ignored,
    uiSizePolicy_Expand_Mask = uiSizePolicy_Expanding | uiSizePolicy_MinimumExpanding
};

class uiSizePolicyInfo : public Object
{
EPI_GENREGION_BEGIN(uiSizePolicyInfo)

EPI_GENHIDDEN_uiSizePolicyInfo()

public:
    constexpr static MetaTypeID TypeID{0xd3c3d009};

    enum uiSizePolicyInfo_PIDs
    {
        PID_CanExpandVertically = 0xc9be91d,
        PID_CanExpandHorizontally = 0xa12e8dbb,
        PID_RetainSizeWhenHidden = 0xc4e7f7a5,
        PID_WidthDependsOnHeight = 0x6860d6f,
        PID_HeightDependsOnWidth = 0xd10782ed,
        PID_StretchFactorVertical = 0x304ba2d1,
        PID_StretchFactorHorizontal = 0x7964dada,
        PID_COUNT = 7
    };

protected:
    epiBool GetCanExpandVertically_Callback() const;
    epiBool GetCanExpandHorizontally_Callback() const;

protected:
    epiBool m_RetainSizeWhenHidden{false};
    epiBool m_WidthDependsOnHeight{false};
    epiBool m_HeightDependsOnWidth{false};
    epiU8 m_StretchFactorVertical{0};
    epiU8 m_StretchFactorHorizontal{0};

EPI_GENREGION_END(uiSizePolicyInfo)

// TODO: move to epi
protected:
    uiSizePolicy m_SizePolicyVertical{uiSizePolicy_Preferred};
    uiSizePolicy m_SizePolicyHorizontal{uiSizePolicy_Preferred};

public:
    uiSizePolicy GetSizePolicyVertical() const { return m_SizePolicyVertical; }
    void SetSizePolicyVertical(uiSizePolicy value) { m_SizePolicyVertical = value; }
    uiSizePolicy GetSizePolicyHorizontal() const { return m_SizePolicyHorizontal; }
    void SetSizePolicyHorizontal(uiSizePolicy value) { m_SizePolicyHorizontal = value; }
};

class uiContext;
class uiLayout;
class uiWidget : public Object
{
EPI_GENREGION_BEGIN(uiWidget)

EPI_GENHIDDEN_uiWidget()

public:
    constexpr static MetaTypeID TypeID{0xac2bf3ee};

    enum uiWidget_PIDs
    {
        PID_BBox = 0xdffc9862,
        PID_Width = 0x4ddb6a2b,
        PID_Height = 0xf2e1e039,
        PID_MouseLocalUICoord = 0xb08d2bad,
        PID_Position = 0xbf5a86a3,
        PID_SizePolicyInfo = 0x7fb0de18,
        PID_Size = 0x57f28b54,
        PID_SizeMinimum = 0x11e0314c,
        PID_SizeMaximum = 0x1213d103,
        PID_SizeHint = 0xee7e8791,
        PID_Parent = 0x3a226579,
        PID_Children = 0x58e1d3ec,
        PID_Layout = 0x3d966ed4,
        PID_COUNT = 13
    };

protected:
    epiRect2f GetBBox_Callback() const;
    void SetBBox_Callback(const epiRect2f& value);
    epiFloat GetWidth_Callback() const;
    void SetWidth_Callback(epiFloat value);
    epiFloat GetHeight_Callback() const;
    void SetHeight_Callback(epiFloat value);
    epiVec2f GetMouseLocalUICoord_Callback() const;
    void SetLayout_Callback(uiLayout* value);

protected:
    epiVec2f m_Position;
    uiSizePolicyInfo m_SizePolicyInfo;
    epiVec2f m_Size;
    epiVec2f m_SizeMinimum;
    epiVec2f m_SizeMaximum;
    epiVec2f m_SizeHint;
    uiWidget* m_Parent{nullptr};
    epiPtrArray<uiWidget> m_Children;
    uiLayout* m_Layout{nullptr};

EPI_GENREGION_END(uiWidget)

public:
    virtual void Update();
    virtual void Draw(uiContext& uiContext); // TODO: refactor uiContext

    template<typename T, typename ...Args>
    T& Add(Args&& ...args)
    {
        static_assert(std::is_base_of_v<uiWidget, T>);
        T& widget = *static_cast<T*>(m_Children.PushBack(new T(std::forward<Args&&>(args)...)));
        widget.m_Parent = this;

        if (m_Layout != nullptr)
        {
            m_Layout->AddWidget(&widget);
        }

        return widget;
    }

    virtual void OnMousePrimary(uiMouseAction action);
    virtual void OnMouseWheel(epiFloat dZoom);
    virtual void OnMouseFocus(epiBool focused);
    virtual void OnResize();

protected:
    virtual epiVec2f GetMouseLocalUICoord_Internal() const;

    uiWidget* WidgetOverMouse(const epiVec2f& mouseUICoord) const;
};

EPI_NAMESPACE_END()
