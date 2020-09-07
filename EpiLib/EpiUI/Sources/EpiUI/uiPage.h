#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiPage.hxx"
EPI_GENREGION_END(include)

#include "EpiUI/uiWidget.h"

EPI_NAMESPACE_BEGIN()

class uiContext;
class uiPage : public uiWidget
{
EPI_GENREGION_BEGIN(uiPage)

EPI_GENHIDDEN_uiPage()

public:
    constexpr static epiMetaTypeID TypeID{0xeb73eeef};

    enum uiPage_PIDs
    {
        PID_UIContext = 0x5892aacd,
        PID_COUNT = 1
    };

protected:
    uiContext* m_UIContext{nullptr};

EPI_GENREGION_END(uiPage)

public:
    void OnResize() override;

protected:
    epiVec2f GetMouseLocalUICoord_Internal() const override;
};

EPI_NAMESPACE_END()
