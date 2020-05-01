#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiLayoutVBox.hxx"
EPI_GENREGION_END(include)

#include "EpiUI/uiLayout.h"

EPI_NAMESPACE_BEGIN()

class uiLayoutVBox : public uiLayout
{
EPI_GENREGION_BEGIN(uiLayoutVBox)
public:
    EPI_GENHIDDEN_uiLayoutVBox()

    constexpr static MetaTypeID TypeID{0x9ba40183};

    enum uiLayoutVBox_PIDs
    {
        PID_Spacing = 0x661c65f8,
        PID_Stretches = 0x14819282,
        PID_COUNT = 2
    };

protected:
    epiFloat m_Spacing{0.0f};
    epiArray<epiFloat> m_Stretches;

EPI_GENREGION_END(uiLayoutVBox)
};

EPI_NAMESPACE_END()
