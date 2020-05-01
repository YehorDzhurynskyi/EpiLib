#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiLayout.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiUI/uiWidget.h"

EPI_NAMESPACE_BEGIN()

class uiLayout : public Object
{
EPI_GENREGION_BEGIN(uiLayout)
public:
    EPI_GENHIDDEN_uiLayout()

    constexpr static MetaTypeID TypeID{0x13e886dc};

    enum uiLayout_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(uiLayout)
};

class uiLayoutBuilder final : public Object
{
EPI_GENREGION_BEGIN(uiLayoutBuilder)
public:
    EPI_GENHIDDEN_uiLayoutBuilder()

    constexpr static MetaTypeID TypeID{0xe7187c4e};

    enum uiLayoutBuilder_PIDs
    {
        PID_BBox = 0xdffc9862,
        PID_COUNT = 1
    };

protected:
    epiRect2f m_BBox;

EPI_GENREGION_END(uiLayoutBuilder)

protected:
    uiLayoutBuilder() = default;

public:
    uiLayoutBuilder(const uiLayoutBuilder& rhs) = default;
    uiLayoutBuilder& operator=(const uiLayoutBuilder& rhs) = default;
    uiLayoutBuilder(uiLayoutBuilder&& rhs) = default;
    uiLayoutBuilder& operator=(uiLayoutBuilder&& rhs) = default;
    ~uiLayoutBuilder() = default;

protected:
    const uiLayout* m_Layout{nullptr};
    std::vector<uiWidget*> m_Widgets;
};

EPI_NAMESPACE_END()
