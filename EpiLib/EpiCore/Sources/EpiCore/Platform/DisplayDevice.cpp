EPI_GENREGION_BEGIN(include)
#include "EpiCore/Platform/DisplayDevice.h"
#include "EpiCore/Platform/DisplayDevice.cxx"
EPI_GENREGION_END(include)

#include <Windows.h>
#include <ShellScalingApi.h>

#pragma comment(lib, "shcore.lib")

namespace
{

BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hDC, LPRECT rect, LPARAM param)
{
    UINT dpiX;
    UINT dpiY;

    MONITORINFOEX info;
    info.cbSize = sizeof(MONITORINFOEX);
    GetMonitorInfo(hMonitor, &info);

    if (info.dwFlags & MONITORINFOF_PRIMARY)
    {
        if (S_OK != GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY))
        {
            epiAssert(false, "GetDpiForMonitor Failed!");
        }

        epiVec2u* outDPI = (epiVec2u*)param;
        outDPI->x = dpiX;
        outDPI->y = dpiY;

        return FALSE;
    }

    return TRUE;
}

}

EPI_NAMESPACE_BEGIN()

epiVec2u DisplayDevice::DPI()
{
    epiVec2u dpi;

    EnumDisplayMonitors(NULL, NULL, &MonitorEnumProc, (LPARAM)&dpi);
    return dpi;
}

void DisplayDevice::SetDPIAwareness(DPIAwareness awareness)
{
    switch (awareness)
    {
    case DPIAwareness::UnAware: SetProcessDpiAwareness(PROCESS_DPI_UNAWARE); break;
    case DPIAwareness::SystemAware: SetProcessDpiAwareness(PROCESS_SYSTEM_DPI_AWARE); break;
    case DPIAwareness::PerMonitorAware: SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE); break;
    }
}

EPI_NAMESPACE_END()