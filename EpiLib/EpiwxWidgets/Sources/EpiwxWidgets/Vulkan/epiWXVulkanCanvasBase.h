#pragma once

#include <wx/window.h>

class epiWXVulkanCanvasBase : public wxWindow
{
public:
    epiWXVulkanCanvasBase() = default;
    epiWXVulkanCanvasBase(const epiWXVulkanCanvasBase&) = delete;
    epiWXVulkanCanvasBase(epiWXVulkanCanvasBase&&) = delete;
    epiWXVulkanCanvasBase& operator=(const epiWXVulkanCanvasBase&) = delete;
    epiWXVulkanCanvasBase& operator=(epiWXVulkanCanvasBase&&) = delete;
    virtual ~epiWXVulkanCanvasBase() = default;

    virtual bool SwapBuffers() = 0;
};
