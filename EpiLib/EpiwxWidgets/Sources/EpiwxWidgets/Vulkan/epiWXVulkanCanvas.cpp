#include "EpiwxWidgets/Vulkan/epiWXVulkanCanvas.h"

#include "EpiGraphicsDriver/gfxDriver.h"
#include "EpiGraphicsDriverCommon/gfxDevice.h"
#include "EpiGraphicsDriverCommon/gfxWindow.h"
#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxQueueDescriptor.h"

#include <wx/app.h>

EPI_NAMESPACE_USING()

epiWXVulkanCanvas::epiWXVulkanCanvas(const epiWXVulkanCanvasCreateInfo& info,
                                     wxWindow* parent,
                                     wxWindowID id,
                                     const wxPoint& pos,
                                     const wxSize& size,
                                     long style,
                                     const wxString& name)
{
    Create(info, parent, id, pos, size, style, name);
}

epiBool epiWXVulkanCanvas::Create(const epiWXVulkanCanvasCreateInfo& info,
                                  wxWindow* parent,
                                  wxWindowID id,
                                  const wxPoint& pos,
                                  const wxSize& size,
                                  long style,
                                  const wxString& name)
{
    if (gfxDriver::GetInstance().GetBackend() == gfxDriverBackend::None)
    {
        epiLogError("Graphics driver backend isn't selected!");
        return false;
    }

    if (!gfxDriver::GetInstance().IsExtensionEnabled(gfxDriverExtension::Surface))
    {
        epiLogError("Graphics driver doesn't has Surface extension enabled!");
        return false;
    }

    if (!info.Device.IsExtensionEnabled(gfxPhysicalDeviceExtension::SwapChain))
    {
        epiLogError("Provided Device doesn't has SwapChain extension enabled!");
        return false;
    }

    if (parent == nullptr)
    {
        epiLogError("Can't create wxWindow without parent!");
        return false;
    }

    wxWindow::Create(parent, id, pos, size, style, name);

    gfxWindow window(GetHWND());
    std::optional<gfxSurface> surface = gfxDriver::GetInstance().CreateSurface(window);
    if (!surface.has_value())
    {
        epiLogError("Falied to create Surface!");
        return false;
    }

    // TODO: check whether device supports graphics queues
    if (!surface->IsCompatibleWith(info.PhysicalDevice, info.Format, info.PresentMode))
    {
        epiLogError("Surface isn't compatible with a provided PhysicalDevice={}!", info.PhysicalDevice.ToString());
        return false;
    }

    if (!surface->IsPresentSupportedFor(info.PhysicalDevice, info.QueueFamily))
    {
        epiLogError("Surface isn't compatible with a provided QueueFamily!");
        return false;
    }

    m_Surface = std::move(*surface);

    const gfxSurfaceCapabilities surfaceCapabilities = m_Surface.GetCapabilitiesFor(info.PhysicalDevice);

    // TODO: submit RenderPass info to ensure compatibility only
    gfxSwapChainCreateInfo swapChainCreateInfo{};
    swapChainCreateInfo.SetSurface(m_Surface);
    swapChainCreateInfo.SetSurfacePreTransformMask(surfaceCapabilities.GetCurrentTransform());
    swapChainCreateInfo.SetImageMinCount(surfaceCapabilities.RecommendedImageCount());
    swapChainCreateInfo.SetImageExtent(surfaceCapabilities.ClampExtent(epiSize2u{GetSize().x, GetSize().y}));
    swapChainCreateInfo.SetImageFormat(info.Format.GetFormat());
    swapChainCreateInfo.SetImageColorSpace(info.Format.GetColorSpace());
    swapChainCreateInfo.SetImageArrayLayers(1);
    swapChainCreateInfo.SetImageUsageMask(gfxImageUsage_COLOR_ATTACHMENT);
    swapChainCreateInfo.SetImageSharingMode(gfxSharingMode::Exclusive);
    swapChainCreateInfo.SetCompositeAlphaMask(gfxCompositeAlphaMask_Opaque);
    swapChainCreateInfo.SetPresentMode(info.PresentMode);
    swapChainCreateInfo.SetClipped(true);

    std::optional<gfxSwapChain> swapChain = info.Device.CreateSwapChain(swapChainCreateInfo);
    if (!swapChain.has_value())
    {
        epiLogError("Falied to create SwapChain!");
        return false;
    }

    m_SwapChain = std::move(*swapChain);

    return true;
}
