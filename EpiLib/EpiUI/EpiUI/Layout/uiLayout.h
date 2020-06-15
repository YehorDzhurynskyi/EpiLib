#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/Layout/uiLayout.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiUI/uiWidget.h"

EPI_NAMESPACE_BEGIN()

#if 0
// TODO: move to epi
enum class uiSizeContraint
{
    // Description: The main widget's minimum size is set to `SizeMinimum`,
    // unless the widget already has a minimum size.
    Default,

    // Description: The main widget's size is set to `SizeHint`;
    // it cannot be resized at all.
    Fixed,

    // Description: The main widget's minimum size is set to `SizeMinimum`;
    // it cannot be smaller.
    Minimum,

    // Description: The main widget's maximum size is set to maximumSize();
    // it cannot be larger.
    Maximum,

    // Description: The main widget's minimum size is set to `SizeMinimum`
    // and its maximum size is set to maximumSize().
    MinMax
};
#endif

// TODO: move to epi
enum uiAlignment
{
    uiAlignment_Left = 0x1,
    uiAlignment_Right = 0x2,
    uiAlignment_HCenter = 0x4,
    uiAlignment_Justify = 0x8,

    uiAlignment_Top = 0x10,
    uiAlignment_Bottom = 0x20,
    uiAlignment_VCenter = 0x40,
    uiAlignment_Baseline = 0x80,

    uiAlignment_Center = uiAlignment_HCenter | uiAlignment_VCenter,

    uiAlignment_Horizontal_Mask = uiAlignment_Left | uiAlignment_Right | uiAlignment_HCenter | uiAlignment_Justify,
    uiAlignment_Vertical_Mask = uiAlignment_Top | uiAlignment_Bottom | uiAlignment_VCenter | uiAlignment_Baseline
};

class uiLayoutItem : public Object
{
    EPI_GENREGION_BEGIN(uiLayoutItem)

EPI_GENHIDDEN_uiLayoutItem()

public:
    constexpr static MetaTypeID TypeID{0x240ad309};

    enum uiLayoutItem_PIDs
    {
        PID_Widget = 0x82551be6,
        PID_COUNT = 1
    };

protected:
    uiWidget* m_Widget{nullptr};

EPI_GENREGION_END(uiLayoutItem)

// TODO: move to epi
protected:
    uiAlignment m_Alignment{uiAlignment_Center};

public:
    uiAlignment GetAlignment() const { return m_Alignment; }
    void SetAlignment(uiAlignment value) { m_Alignment = value; }
};

class uiLayout : public Object
{
EPI_GENREGION_BEGIN(uiLayout)

EPI_GENHIDDEN_uiLayout()

public:
    constexpr static MetaTypeID TypeID{0x13e886dc};

    enum uiLayout_PIDs
    {
        PID_Items = 0x20dfc649,
        PID_Position = 0xbf5a86a3,
        PID_Size = 0x57f28b54,
        PID_COUNT = 3
    };

protected:
    epiArray<uiLayoutItem> m_Items;
    epiVec2f m_Position;
    epiVec2f m_Size;

EPI_GENREGION_END(uiLayout)

public:
    virtual void OnResize() = 0;

    uiLayoutItem& AddWidget(uiWidget* widget);
};

EPI_NAMESPACE_END()
