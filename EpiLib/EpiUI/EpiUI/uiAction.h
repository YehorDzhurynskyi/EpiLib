#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiAction.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

enum class uiMouseAction
{
EPI_GENREGION_BEGIN(uiMouseAction)
    Release = 0,
    Click = 1,
    DClick = 2
EPI_GENREGION_END(uiMouseAction)
};

class uiAction : public Object
{
EPI_GENREGION_BEGIN(uiAction)

EPI_GENHIDDEN_uiAction()

public:
    constexpr static MetaTypeID TypeID{0x6e1e61ac};

    enum uiAction_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(uiAction)
};

EPI_NAMESPACE_END()
