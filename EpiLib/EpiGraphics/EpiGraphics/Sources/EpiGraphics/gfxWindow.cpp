EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxWindow.h"
#include "EpiGraphics/gfxWindow.cxx"
EPI_GENREGION_END(include)

#ifdef EPI_PLATFORM_WINDOWS
#include <windows.h>
#endif // EPI_PLATFORM_WINDOWS

EPI_NAMESPACE_BEGIN()

gfxWindow::gfxWindow()
    : gfxWindow(EPI_PLATFORM_WINDOWS_ONLY(GetActiveWindow()))
{
}

#ifdef EPI_PLATFORM_WINDOWS
gfxWindow::gfxWindow(HWND hwnd)
    : m_HWND{hwnd}
{
}

HWND gfxWindow::GetHWND() const
{
    return m_HWND;
}
#endif // EPI_PLATFORM_WINDOWS

EPI_NAMESPACE_END()
