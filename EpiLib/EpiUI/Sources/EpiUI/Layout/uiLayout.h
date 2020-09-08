#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/Layout/uiLayout.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiUI/uiWidget.h"

EPI_NAMESPACE_BEGIN()

enum class uiSizeContraint
{
EPI_GENREGION_BEGIN(uiSizeContraint)
    Default = 0,
    Fixed = 1,
    Minimum = 2,
    Maximum = 3,
    MinMax = 4,
    NoContraint = 5
EPI_GENREGION_END(uiSizeContraint)
};

enum uiAlignment
{
EPI_GENREGION_BEGIN(uiAlignment)
    uiAlignment_Left = (1 << 1),
    uiAlignment_Right = (1 << 2),
    uiAlignment_HCenter = (1 << 3),
    uiAlignment_Justify = (1 << 4),
    uiAlignment_Top = (1 << 5),
    uiAlignment_Bottom = (1 << 6),
    uiAlignment_VCenter = (1 << 7),
    uiAlignment_Baseline = (1 << 8),
    uiAlignment_Center = uiAlignment_HCenter | uiAlignment_VCenter,
    uiAlignment_Horizontal_Mask = uiAlignment_Left | uiAlignment_Right | uiAlignment_HCenter | uiAlignment_Justify,
    uiAlignment_Vertical_Mask = uiAlignment_Top | uiAlignment_Bottom | uiAlignment_VCenter | uiAlignment_Baseline
EPI_GENREGION_END(uiAlignment)
};

class uiLayoutItem : public Object
{
    EPI_GENREGION_BEGIN(uiLayoutItem)

EPI_GENHIDDEN_uiLayoutItem()

public:
    constexpr static epiMetaTypeID TypeID{0x240ad309};

    enum uiLayoutItem_PIDs
    {
        PID_Widget = 0x82551be6,
        PID_COUNT = 1
    };

protected:
    uiWidget* m_Widget{nullptr};

EPI_GENREGION_END(uiLayoutItem)
};

class uiLayout : public Object
{
EPI_GENREGION_BEGIN(uiLayout)

EPI_GENHIDDEN_uiLayout()

public:
    constexpr static epiMetaTypeID TypeID{0x13e886dc};

    enum uiLayout_PIDs
    {
        PID_Items = 0x20dfc649,
        PID_Position = 0xbf5a86a3,
        PID_Size = 0x57f28b54,
        PID_Alignment = 0xae3f9cff,
        PID_COUNT = 4
    };

protected:
    epiArray<uiLayoutItem> m_Items{};
    epiVec2f m_Position{};
    epiVec2f m_Size{};
    uiAlignment m_Alignment{uiAlignment_Center};

EPI_GENREGION_END(uiLayout)

public:
    virtual void OnResize() = 0;

    uiLayoutItem& AddWidget(uiWidget* widget);
};

EPI_NAMESPACE_END()
