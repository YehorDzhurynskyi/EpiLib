#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/Layout/uiLayoutBox.hxx"
EPI_GENREGION_END(include)

#include "EpiUI/Layout/uiLayout.h"

EPI_NAMESPACE_BEGIN()

// TODO: move to epi
enum class uiDirection
{
    LeftToRight,
    RightToLeft,
    TopToBottom,
    BottomToTop
};

class uiLayoutBox : public uiLayout
{
EPI_GENREGION_BEGIN(uiLayoutBox)

EPI_GENHIDDEN_uiLayoutBox()

public:
    constexpr static MetaTypeID TypeID{0x777f971a};

    enum uiLayoutBox_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(uiLayoutBox)

public:
    void OnResize() override;

// TODO: move to epi
protected:
    uiDirection m_Direction{uiDirection::TopToBottom};

public:
    uiDirection GetDirection() const { return m_Direction; }
    void SetDirection(uiDirection value) { m_Direction = value; }
};

EPI_NAMESPACE_END()
