#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiWidget.hxx"
EPI_GENREGION_END(include)

#include "EpiUI/uiAction.h"

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

enum uiSizePolicy : epiS32
{
EPI_GENREGION_BEGIN(uiSizePolicy)
    uiSizePolicy_Fixed = (1 << 1),
    uiSizePolicy_Minimum = (1 << 2),
    uiSizePolicy_Maximum = (1 << 3),
    uiSizePolicy_Preferred = (1 << 4),
    uiSizePolicy_Expanding = (1 << 5),
    uiSizePolicy_MinimumExpanding = (1 << 6),
    uiSizePolicy_Ignored = (1 << 7),
    uiSizePolicy_Grow_Mask = uiSizePolicy_Minimum | uiSizePolicy_Preferred | uiSizePolicy_Expanding | uiSizePolicy_MinimumExpanding | uiSizePolicy_Ignored,
    uiSizePolicy_Shrink_Mask = uiSizePolicy_Maximum | uiSizePolicy_Preferred | uiSizePolicy_Expanding | uiSizePolicy_Ignored,
    uiSizePolicy_Expand_Mask = uiSizePolicy_Expanding | uiSizePolicy_MinimumExpanding
EPI_GENREGION_END(uiSizePolicy)
};

class uiSizePolicyInfo : public Object
{
EPI_GENREGION_BEGIN(uiSizePolicyInfo)

EPI_GENHIDDEN_uiSizePolicyInfo()

public:
    constexpr static epiMetaTypeID TypeID{0xd3c3d009};

    enum uiSizePolicyInfo_PIDs
    {
        PID_CanExpandVertically = 0xc9be91d,
        PID_CanExpandHorizontally = 0xa12e8dbb,
        PID_RetainSizeWhenHidden = 0xc4e7f7a5,
        PID_WidthDependsOnHeight = 0x6860d6f,
        PID_HeightDependsOnWidth = 0xd10782ed,
        PID_StretchFactorVertical = 0x304ba2d1,
        PID_StretchFactorHorizontal = 0x7964dada,
        PID_SizePolicyVertical = 0xb375145,
        PID_SizePolicyHorizontal = 0x48fd0d1e,
        PID_COUNT = 9
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
    uiSizePolicy m_SizePolicyVertical{uiSizePolicy_Preferred};
    uiSizePolicy m_SizePolicyHorizontal{uiSizePolicy_Preferred};

EPI_GENREGION_END(uiSizePolicyInfo)
};

class uiContext;
class uiLayout;
class uiWidget : public Object
{
EPI_GENREGION_BEGIN(uiWidget)

EPI_GENHIDDEN_uiWidget()

public:
    constexpr static epiMetaTypeID TypeID{0xac2bf3ee};

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
    epiVec2f m_Position{};
    uiSizePolicyInfo m_SizePolicyInfo{};
    epiVec2f m_Size{};
    epiVec2f m_SizeMinimum{};
    epiVec2f m_SizeMaximum{};
    epiVec2f m_SizeHint{};
    uiWidget* m_Parent{nullptr};
    epiPtrArray<uiWidget> m_Children{};
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
