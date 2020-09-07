#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/Layout/uiLayoutBox.hxx"
EPI_GENREGION_END(include)

#include "EpiUI/Layout/uiLayout.h"

EPI_NAMESPACE_BEGIN()

enum class uiDirection
{
EPI_GENREGION_BEGIN(uiDirection)
    LeftToRight = 0,
    RightToLeft = 1,
    TopToBottom = 2,
    BottomToTop = 3
EPI_GENREGION_END(uiDirection)
};

class uiLayoutBox : public uiLayout
{
EPI_GENREGION_BEGIN(uiLayoutBox)

EPI_GENHIDDEN_uiLayoutBox()

public:
    constexpr static epiMetaTypeID TypeID{0x777f971a};

    enum uiLayoutBox_PIDs
    {
        PID_Direction = 0xbcbb5310,
        PID_COUNT = 1
    };

protected:
    uiDirection m_Direction{uiDirection::TopToBottom};

EPI_GENREGION_END(uiLayoutBox)

public:
    void OnResize() override;
};

EPI_NAMESPACE_END()
