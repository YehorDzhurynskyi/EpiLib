#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxWindow.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_PLATFORM_WINDOWS_ONLY(struct HWND__);

EPI_NAMESPACE_BEGIN()

class gfxWindow : public Object
{
EPI_GENREGION_BEGIN(gfxWindow)

EPI_GENHIDDEN_gfxWindow()

public:
    constexpr static epiMetaTypeID TypeID{0x2a8292fb};

    enum gfxWindow_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxWindow)

public:
    gfxWindow();

#ifdef EPI_PLATFORM_WINDOWS
    explicit gfxWindow(HWND__* hwnd);
    HWND__* GetHWND() const;
#endif // EPI_PLATFORM_WINDOWS

protected:
    EPI_PLATFORM_WINDOWS_ONLY(HWND__* m_HWND);
};

EPI_NAMESPACE_END()
