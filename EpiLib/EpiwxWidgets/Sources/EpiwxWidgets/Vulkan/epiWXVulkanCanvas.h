#pragma once

#include "EpiwxWidgets/Vulkan/epiWXVulkanCanvasBase.h"

class epiWXVulkanCanvas : public epiWXVulkanCanvasBase
{
private:
    wxDECLARE_EVENT_TABLE();
    wxDECLARE_CLASS(epiWXVulkanCanvas);

public:
    explicit epiWXVulkanCanvas(wxWindow* parent,
                               wxWindowID id = wxID_ANY,
                               const int* attribList = NULL,
                               const wxPoint& pos = wxDefaultPosition,
                               const wxSize& size = wxDefaultSize,
                               long style = 0,
                               const wxString& name = wxASCII_STR("epiWXVulkanCanvas"),
                               const wxPalette& palette = wxNullPalette);
    ~epiWXVulkanCanvas() override;

    bool Create(wxWindow* parent,
                wxWindowID id = wxID_ANY,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0,
                const wxString& name = wxASCII_STR("epiWXVulkanCanvas"),
                const wxPalette& palette = wxNullPalette);

    bool SwapBuffers() override;
};
